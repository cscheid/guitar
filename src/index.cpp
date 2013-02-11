#include "index.h"
#include "entry_points.h"
#include "tree.h"
#include "oid.h"

using namespace Rcpp;

Index::Index(git_index *_ix)
{
    ix = boost::shared_ptr<git_index>(_ix, _git_index_free);
}

SEXP Index::read()
{
    BEGIN_RCPP
    int result = _git_index_read(ix.get());
    if (result) {
        throw Rcpp::exception("Index::read error");
    }
    return R_NilValue;
    END_RCPP
}

SEXP Index::write()
{
    BEGIN_RCPP
    int result = _git_index_write(ix.get());
    if (result) {
        throw Rcpp::exception("Index::write error");
    }
    return R_NilValue;
    END_RCPP
}

void Index::read_tree(SEXP _tree)
{
    const git_tree *tree = Tree::from_sexp(_tree);
    int err = _git_index_read_tree(ix.get(), tree);
    if (err)
        throw Rcpp::exception("read_tree error");
}

Rcpp::Reference Index::write_tree()
{
    git_oid result;
    int err = _git_index_write_tree(&result, ix.get());
    if (err)
        throw Rcpp::exception("write_tree error");
    return OID::create(&result);
}

size_t Index::entrycount()
{
    return _git_index_entrycount(ix.get());
}

void Index::clear()
{
    _git_index_clear(ix.get());
}

void Index::add_by_path(std::string path)
{
    int err = _git_index_add_bypath(ix.get(), path.c_str());
    if (err)
        throw Rcpp::exception("add_by_path failed");
}

void Index::remove_by_path(std::string path)
{
    int err = _git_index_remove_bypath(ix.get(), path.c_str());
    if (err)
        throw Rcpp::exception("remove_by_path failed");
}

void Index::remove_directory(std::string path, int stage)
{
    int err = _git_index_remove_directory(ix.get(), path.c_str(), stage);
    if (err)
        throw Rcpp::exception("remove_directory failed");
}

RCPP_MODULE(guitar_index) {
    class_<Index>("Index")
        .method("read", &Index::read)
        .method("write", &Index::write)
        .method("write_tree", &Index::write_tree)
        .method("entrycount", &Index::entrycount)
        .method("clear", &Index::clear)
        .method("add_by_path", &Index::add_by_path)
        .method("remove_by_path", &Index::remove_by_path)
        .method("remove_directory", &Index::remove_directory)
        .method("read_tree", &Index::read_tree)
        ;
}
