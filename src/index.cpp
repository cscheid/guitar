#include "index.h"
#include "entry_points.h"
#include "tree.h"
#include "oid.h"

using namespace Rcpp;

Index::Index(git_index *_ix)
{
    ix = boost::shared_ptr<git_index>(_ix, git_index_free);
}

SEXP Index::read()
{
    BEGIN_RCPP
    int result = git_index_read(ix.get());
    if (result) {
        throw Rcpp::exception("Index::read error");
    }
    return R_NilValue;
    END_RCPP
}

SEXP Index::write()
{
    BEGIN_RCPP
    int result = git_index_write(ix.get());
    if (result) {
        throw Rcpp::exception("Index::write error");
    }
    return R_NilValue;
    END_RCPP
}

void Index::read_tree(SEXP _tree)
{
    const git_tree *tree = Tree::from_sexp(_tree);
    int err = git_index_read_tree(ix.get(), tree);
    if (err)
        throw Rcpp::exception("read_tree error");
}

Rcpp::Reference Index::write_tree()
{
    git_oid result;
    int err = git_index_write_tree(&result, ix.get());
    if (err)
        throw Rcpp::exception("write_tree error");
    return OID::create(&result);
}

size_t Index::entrycount()
{
    return git_index_entrycount(ix.get());
}

void Index::clear()
{
    git_index_clear(ix.get());
}

void Index::add_by_path(std::string path)
{
    int err = git_index_add_bypath(ix.get(), path.c_str());
    if (err)
        throw Rcpp::exception("add_by_path failed");
}

void Index::remove_by_path(std::string path)
{
    int err = git_index_remove_bypath(ix.get(), path.c_str());
    if (err)
        throw Rcpp::exception("remove_by_path failed");
}

void Index::remove_directory(std::string path, int stage)
{
    int err = git_index_remove_directory(ix.get(), path.c_str(), stage);
    if (err)
        throw Rcpp::exception("remove_directory failed");
}

namespace IndexEntry {
    Rcpp::List index_time(const git_index_time *time) {
        return Rcpp::List::create(Rcpp::Named("seconds") = (long) time->seconds,
                                  Rcpp::Named("nanoseconds") = time->nanoseconds);
    }
    Rcpp::List create(const git_index_entry *entry) {
        SEXP oid = OID::create(&entry->oid);
        return Rcpp::List::create(Rcpp::Named("ctime") = index_time(&entry->ctime),
                                  Rcpp::Named("mtime") = index_time(&entry->mtime),
                                  Rcpp::Named("dev") = entry->dev,
                                  Rcpp::Named("ino") = entry->ino,
                                  Rcpp::Named("mode") = entry->mode,
                                  Rcpp::Named("uid") = entry->uid,
                                  Rcpp::Named("gid") = entry->gid,
                                  Rcpp::Named("file_size") = (long) entry->file_size,
                                  Rcpp::Named("oid") = oid,
                                  Rcpp::Named("flags") = entry->flags,
                                  Rcpp::Named("flags_extended") = entry->flags_extended,
                                  Rcpp::Named("path") = std::string(entry->path));
    }
};

Rcpp::List Index::get_by_index(size_t n) {
    const git_index_entry *result = git_index_get_byindex(ix.get(), n);
    if (result == NULL)
        throw Rcpp::exception("get_by_index failed");
    return IndexEntry::create(result);
}

Rcpp::List Index::get_by_path(std::string path, int stage) {
    const git_index_entry *result = git_index_get_bypath(ix.get(), path.c_str(), stage);
    if (result == NULL)
        throw Rcpp::exception("get_by_path failed");
    return IndexEntry::create(result);
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
        .method("get_by_index", &Index::get_by_index)
        .method("get_by_path", &Index::get_by_path)
        ;
}
