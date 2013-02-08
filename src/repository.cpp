#include "repository.h"
#include "entry_points.h"
#include "index.h"
#include "reference.h"
#include "oid.h"

/******************************************************************************/

Repository::Repository(std::string path)
{
    git_repository *_repo;
    int err = _git_repository_open(&_repo, path.c_str());
    if (err)
        throw Rcpp::exception("Repository not found");
    
    repo = boost::shared_ptr<git_repository>(_repo, _git_repository_free);
}

Rcpp::Reference Repository::head() {
    git_reference *ref;
    _git_repository_head(&ref, repo.get());
    return Rcpp::internal::make_new_object(new GitReference(ref));
};

Rcpp::Reference Repository::index() {
    git_index *ix;
    _git_repository_index(&ix, repo.get());
    return Rcpp::internal::make_new_object(new Index(ix));
};

bool Repository::is_bare()
{
    return _git_repository_is_bare(repo.get());
};

std::string Repository::workdir()
{
    const char *r = _git_repository_workdir(repo.get());
    return r ? std::string(r) : std::string("");
};

Rcpp::Reference Repository::reference_lookup(std::string name) {
    BEGIN_RCPP
    git_reference *ref;
    int result = _git_reference_lookup(&ref, repo.get(), name.c_str());
    if (result)
        throw Rcpp::exception("Repository::lookup error");
    return Rcpp::internal::make_new_object(new GitReference(ref));
    END_RCPP
}

Rcpp::Reference Repository::name_to_id(std::string name) {
    BEGIN_RCPP
    OID *oid = new OID;
    int result = _git_reference_name_to_id((*oid), repo.get(), name.c_str());
    if (result) {
        delete oid;
        throw Rcpp::exception("Repository::lookup error");
    }
    return Rcpp::internal::make_new_object(oid);
    END_RCPP
}

SEXP Repository::reference_list(unsigned int flags) {
    BEGIN_RCPP
    git_strarray result;
    int err = _git_reference_list(&result, repo.get(), flags);
    if (err) {
        _git_strarray_free(&result);
        throw Rcpp::exception("Repository::reference_list error");
    }
    Rcpp::StringVector rresult(result.count);
    for (int i=0; i<result.count; ++i) {
        rresult[i] = std::string(result.strings[i]);
    }
    _git_strarray_free(&result);
    return rresult;
    END_RCPP
}

RCPP_MODULE(guitar_repository) {
    using namespace Rcpp;
    class_<Repository>("Repository")
        .constructor<std::string>()
        .method("head", &Repository::head)
        .method("index", &Repository::index)
        .method("is_bare", &Repository::is_bare)
        .method("workdir", &Repository::workdir)
        .method("reference_lookup", &Repository::reference_lookup)
        .method("name_to_id", &Repository::name_to_id)
        .method("reference_list", &Repository::reference_list)
        ;
};
