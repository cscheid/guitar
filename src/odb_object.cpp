#include "odb_object.h"
#include "entry_points.h"
#include <algorithm>

/******************************************************************************/

ODBObject::ODBObject(git_odb_object *_obj)
{
    obj = boost::shared_ptr<git_odb_object>(_obj, _git_odb_object_free);
}

Rcpp::RawVector ODBObject::data()
{
    BEGIN_RCPP
    size_t sz = _git_odb_object_size(obj.get());
    const void *ptr = _git_odb_object_data(obj.get());
    const char *b = (const char *)ptr;
    const char *e = b + sz;
    Rcpp::RawVector result(sz);
    std::copy(b, e, result.begin());
    return result;
    END_RCPP
}

RCPP_MODULE(guitar_odb_object) {
    using namespace Rcpp;
    class_<ODBObject>("ODBObject")
        .method("data", &ODBObject::data)
        ;
}
