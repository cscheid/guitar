#include "tree.h"
#include "entry_points.h"
#include "oid.h"
#include "repository.h"

/******************************************************************************/
// Tree

static void _git_tree_free(git_tree *tree)
{
    git_object_free((git_object *)tree);
}

Tree::Tree(git_tree *_tree)
{
    tree = boost::shared_ptr<git_tree>(_tree, _git_tree_free);
}

Rcpp::Reference Tree::id()
{
    const git_oid *result = git_tree_id(tree.get());
    return OID::create(result);
}

size_t Tree::entry_count()
{
    return git_tree_entrycount(tree.get());
}

static int walk_cb(const char *root, const git_tree_entry *entry, void *payload)
{
    Rcpp::Function *f = (Rcpp::Function *)payload;
    int r = Rcpp::as<int>((*f)(std::string(root)));
    return r;
}

int Tree::walk_pre(Rcpp::Function fcall)
{
    git_tree_walk(tree.get(), GIT_TREEWALK_PRE, &walk_cb, &fcall);
}

int Tree::walk_post(Rcpp::Function fcall)
{
    git_tree_walk(tree.get(), GIT_TREEWALK_POST, &walk_cb, &fcall);
}

Rcpp::Reference Tree::entry_by_index(size_t idx)
{
    BEGIN_RCPP
        const git_tree_entry *entry = git_tree_entry_byindex(tree.get(), idx);
    if (entry == NULL)
        throw Rcpp::exception("entry not found");
    git_tree_entry *dup = git_tree_entry_dup(entry);
    return TreeEntry::create(dup);
    END_RCPP
}

Rcpp::Reference Tree::entry_by_name(std::string name)
{
    BEGIN_RCPP
    const git_tree_entry *entry = git_tree_entry_byname(tree.get(), name.c_str());
    if (entry == NULL)
        throw Rcpp::exception("entry not found");
    git_tree_entry *dup = git_tree_entry_dup(entry);
    return TreeEntry::create(dup);
    END_RCPP
}

Rcpp::Reference Tree::entry_by_path(std::string name)
{
    BEGIN_RCPP
    git_tree_entry *entry;
    int err = git_tree_entry_bypath(&entry, tree.get(), name.c_str());
    if (err)
        throw Rcpp::exception("entry not found");
    return TreeEntry::create(entry);
    END_RCPP
}

Rcpp::Reference Tree::entry_by_oid(SEXP oid)
{
    BEGIN_RCPP
    const git_tree_entry *entry = git_tree_entry_byoid(tree.get(), OID::from_sexp(oid));
    if (entry == NULL)
        throw Rcpp::exception("entry not found");
    git_tree_entry *dup = git_tree_entry_dup(entry);
    return TreeEntry::create(dup);
    END_RCPP
}

/******************************************************************************/
// TreeEntry

TreeEntry::TreeEntry(git_tree_entry *_entry)
{
    tree_entry = boost::shared_ptr<git_tree_entry>(_entry, git_tree_entry_free);
}

int TreeEntry::file_mode()
{
    return git_tree_entry_filemode(tree_entry.get());
}

Rcpp::Reference TreeEntry::id()
{
    return OID::create(git_tree_entry_id(tree_entry.get()));
}

std::string TreeEntry::name()
{
    return std::string(git_tree_entry_name(tree_entry.get()));
}

SEXP TreeEntry::object(SEXP _repo)
{
    BEGIN_RCPP
    git_repository *repo = (git_repository*)Repository::from_sexp(_repo);
    git_object *result;
    int err = git_tree_entry_to_object(&result, repo, tree_entry.get());
    if (err)
        throw Rcpp::exception("object lookup failed");
    return object_to_sexp(result);
    END_RCPP
}

int TreeEntry::type()
{
    return git_tree_entry_type(tree_entry.get());
}

RCPP_MODULE(guitar_tree) {
    using namespace Rcpp;
    class_<Tree>("Tree")
        .method("id", &Tree::id)
        .method("entry_count", &Tree::entry_count)
        .method("walk_pre", &Tree::walk_pre)
        .method("walk_post", &Tree::walk_post)
        .method("entry_by_index", &Tree::entry_by_index)
        .method("entry_by_name", &Tree::entry_by_name)
        .method("entry_by_oid", &Tree::entry_by_oid)
        .method("entry_by_path", &Tree::entry_by_path)
        ;
    class_<TreeEntry>("TreeEntry")
        .method("file_mode", &TreeEntry::file_mode)
        .method("id", &TreeEntry::id)
        .method("name", &TreeEntry::name)
        .method("object", &TreeEntry::object)
        .method("type", &TreeEntry::type)
        ;
}
