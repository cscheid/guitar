#include "index.h"
#include "entry_points.h"

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

size_t Index::entrycount()
{
    return _git_index_entrycount(ix.get());
}

void Index::clear()
{
    _git_index_clear(ix.get());
}

RCPP_MODULE(guitar_index) {
    class_<Index>("Index")
        .method("read", &Index::read)
        .method("write", &Index::write)
        .method("entrycount", &Index::entrycount)
        .method("clear", &Index::clear)
        ;
}
