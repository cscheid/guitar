#include "odb_object.h"
#include "entry_points.h"
#include <algorithm>
#include "oid.h"

/******************************************************************************/

ODBObject::ODBObject(git_odb_object *_obj)
{
    obj = boost::shared_ptr<git_odb_object>(_obj, _git_odb_object_free);
}

size_t ODBObject::size()
{
    return _git_odb_object_size(obj.get());
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

unsigned int ODBObject::type()
{
    return _git_odb_object_type(obj.get());
}

Rcpp::Reference ODBObject::id()
{
    return OID::create(_git_odb_object_id(obj.get()));
}

RCPP_MODULE(guitar_odb_object) {
    using namespace Rcpp;
    class_<ODBObject>("ODBObject")
        .method("data", &ODBObject::data)
        .method("type", &ODBObject::type)
        .method("id", &ODBObject::id)
        ;
}
