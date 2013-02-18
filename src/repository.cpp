#include "repository.h"
#include "entry_points.h"
#include "index.h"
#include "reference.h"
#include "oid.h"
#include "odb.h"
#include "tree.h"
#include "commit.h"
#include <iostream>

using namespace std;

/******************************************************************************/
Repository::Repository(git_repository *_repo)
{
    repo = boost::shared_ptr<git_repository>(_repo, git_repository_free);
}

Repository::Repository(std::string path)
{
    git_repository *_repo;
    int err = git_repository_open(&_repo, path.c_str());
    if (err)
        throw Rcpp::exception("Repository not found");
    
    repo = boost::shared_ptr<git_repository>(_repo, git_repository_free);
}

Rcpp::Reference Repository::hash_file(std::string path, int type)
{
    git_oid out;
    int err = git_repository_hashfile(&out, repo.get(), path.c_str(), (git_otype) type, path.c_str());
    if (err)
        throw Rcpp::exception("hash_file failed");
    return OID::create(&out);
}

Rcpp::Reference Repository::head()
{
    git_reference *ref;
    git_repository_head(&ref, repo.get());
    return Rcpp::internal::make_new_object(new GitReference(ref));
};

bool Repository::head_detached()
{
    return git_repository_head_detached(repo.get());
}

bool Repository::head_orphan()
{
    return git_repository_head_orphan(repo.get());
}

Rcpp::Reference Repository::index()
{
    git_index *ix;
    git_repository_index(&ix, repo.get());
    return Rcpp::internal::make_new_object(new Index(ix));
};

bool Repository::is_bare()
{
    return git_repository_is_bare(repo.get());
};

bool Repository::is_empty()
{
    return git_repository_is_empty(repo.get());
};

Rcpp::Reference Repository::odb()
{
    BEGIN_RCPP
    git_odb *odb;
    int result = git_repository_odb(&odb, repo.get());
    if (result)
        throw Rcpp::exception("Repository::odb error");
    return Rcpp::internal::make_new_object(new ODB(odb));
    END_RCPP
}

std::string Repository::path()
{
    return std::string(git_repository_path(repo.get()));
}

void Repository::set_head(std::string refname)
{
    int err = git_repository_set_head(repo.get(), refname.c_str());
    if (err)
        throw Rcpp::exception("set_head failed");
}

void Repository::set_head_detached(SEXP _oid)
{
    const git_oid *oid = OID::from_sexp(_oid);
    int err = git_repository_set_head_detached(repo.get(), oid);
    if (err)
        throw Rcpp::exception("set_head detached failed");
}

int Repository::state()
{
    return git_repository_state(repo.get());
}

std::string Repository::workdir()
{
    const char *r = git_repository_workdir(repo.get());
    return r ? std::string(r) : std::string("");
};

Rcpp::Reference Repository::reference_lookup(std::string name)
{
    BEGIN_RCPP
    git_reference *ref;
    int result = git_reference_lookup(&ref, repo.get(), name.c_str());
    if (result)
        throw Rcpp::exception("Repository::lookup error");
    return Rcpp::internal::make_new_object(new GitReference(ref));
    END_RCPP
}

Rcpp::Reference Repository::name_to_id(std::string name)
{
    BEGIN_RCPP
    OID *oid = new OID;
    int result = git_reference_name_to_id((*oid), repo.get(), name.c_str());
    if (result) {
        delete oid;
        throw Rcpp::exception("Repository::lookup error");
    }
    return Rcpp::internal::make_new_object(oid);
    END_RCPP
}

SEXP Repository::reference_list(unsigned int flags)
{
    BEGIN_RCPP
    git_strarray result;
    int err = git_reference_list(&result, repo.get(), flags);
    if (err) {
        git_strarray_free(&result);
        throw Rcpp::exception("Repository::reference_list error");
    }
    Rcpp::StringVector rresult(result.count);
    for (int i=0; i<result.count; ++i) {
        rresult[i] = std::string(result.strings[i]);
    }
    git_strarray_free(&result);
    return rresult;
    END_RCPP
}

SEXP Repository::object_lookup(SEXP soid, int otype)
{
    BEGIN_RCPP
    const git_oid *oid = OID::from_sexp(soid);
    git_otype type = (git_otype) otype;
    git_object *obj;
    int err = git_object_lookup(&obj, repo.get(), oid, type);
    if (err) {
        throw Rcpp::exception("git_object_lookup failed");
    }
    return object_to_sexp(obj);
    
    END_RCPP
}

void Repository::create_commit(std::string update_ref,
                               SEXP author_s,
                               SEXP committer_s,
                               std::string message_encoding,
                               std::string message,
                               SEXP tree,
                               SEXP parents)
{
    Rcpp::List parents_l(Rcpp::as<Rcpp::List>(parents));
    std::vector<const git_commit *> parents_v(parents_l.size());

    for (size_t i=0; i<parents_l.size(); ++i) {
        parents_v[i] = Commit::from_sexp(parents_l[i]);
    }

    git_oid result_oid;
    git_signature *author = Signature::from_sexp(author_s);
    git_signature *committer = Signature::from_sexp(committer_s);

    int err = git_commit_create(&result_oid,
                                repo.get(),
                                update_ref.c_str(),
                                author, committer,
                                message_encoding.c_str(), message.c_str(),
                                Tree::from_sexp(tree),
                                parents_v.size(),
                                &parents_v[0]);
    git_signature_free(author);
    git_signature_free(committer);
    if (err)
        throw Rcpp::exception("git_create_commit failed");
}

Rcpp::Reference repository_init(std::string path, bool is_bare)
{
    BEGIN_RCPP
    git_repository *_repo = NULL;
    int err = git_repository_init(&_repo, path.c_str(), (unsigned) is_bare);
    if (err)
        throw Rcpp::exception("git_repository_init failed");
    if (_repo == NULL)
        throw Rcpp::exception("repository could not be created");
    return Repository::create(_repo);
    END_RCPP
}

RCPP_MODULE(guitar_repository) {
    using namespace Rcpp;
    class_<Repository>("Repository")
        .constructor<std::string>()
        .method("hash_file", &Repository::hash_file)
        .method("head", &Repository::head)
        .method("head_detached", &Repository::head_detached)
        .method("head_orphan", &Repository::head_orphan)
        .method("index", &Repository::index)
        .method("is_bare", &Repository::is_bare)
        .method("is_empty", &Repository::is_empty)
        .method("odb", &Repository::odb)
        .method("path", &Repository::path)
        .method("set_head", &Repository::set_head)
        .method("set_head_detached", &Repository::set_head_detached)
        .method("state", &Repository::state)
        .method("workdir", &Repository::workdir)
        .method("reference_lookup", &Repository::reference_lookup)
        .method("object_lookup", &Repository::object_lookup)
        .method("name_to_id", &Repository::name_to_id)
        .method("reference_list", &Repository::reference_list)
        .method("create_commit", &Repository::create_commit)
        ;
    function("repository_init", &repository_init);
};
