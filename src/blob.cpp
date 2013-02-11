#include "blob.h"
#include "entry_points.h"
#include "oid.h"

/******************************************************************************/

static void _git_blob_free(git_blob *blob)
{
    git_object_free((git_object*) blob);
}

Blob::Blob(git_blob *_blob)
{
    blob = boost::shared_ptr<git_blob>(_blob, _git_blob_free);
}

Rcpp::Reference Blob::id()
{
    return OID::create(git_object_id((git_object *)blob.get()));
}

bool Blob::is_binary()
{
    return git_blob_is_binary(blob.get());
}

size_t Blob::size()
{
    return git_blob_rawsize(blob.get());
}

Rcpp::RawVector Blob::data()
{
    BEGIN_RCPP
    size_t sz = git_blob_rawsize(blob.get());
    const void *ptr = git_blob_rawcontent(blob.get());
    const char *b = (const char *)ptr;
    const char *e = b + sz;
    Rcpp::RawVector result(sz);
    std::copy(b, e, result.begin());
    return result;
    END_RCPP
}

RCPP_MODULE(guitar_blob) {
    using namespace Rcpp;
    class_<Blob>("Blob")
        .method("id", &Blob::id)
        .method("is_binary", &Blob::is_binary)
        .method("size", &Blob::size)
        .method("data", &Blob::data)
        ;
}
