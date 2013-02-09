#include "odb.h"
#include "entry_points.h"
#include "odb_object.h"
#include <cstdio>

/******************************************************************************/

// The code below ICEs g++ on OS X 10.8.2.
//
// // ptr extracts the .pointer fiels from the c++-derived class
// template <typename T> 
//     inline Rcpp::XPtr<T> ptr(SEXP s)
// {
//     Rcpp::Function extractor = Rcpp::Environment::namespace_env("guitar")[".extractPointer"];
//     SEXP s2 = extractor(s);
//     return Rcpp::XPtr<T>(s2);
// }

ODB::ODB(git_odb *_odb)
{
    odb = boost::shared_ptr<git_odb>(_odb, _git_odb_free);
}

bool ODB::exists(SEXP s)
{
    return _git_odb_exists(odb.get(), OID::from_sexp(s));
}

static int foreach_cb(const git_oid *id, void *payload)
{
    Rcpp::Function *f = (Rcpp::Function *)payload;
    Rcpp::Reference ref = Rcpp::internal::make_new_object(new OID(id));
    (*f)(ref);
    return 0;
}

void ODB::foreach(Rcpp::Function fcall)
{
    _git_odb_foreach(odb.get(), &foreach_cb, &fcall);
}

static int list_cb(const git_oid *id, void *payload)
{
    Rcpp::List *l = (Rcpp::List *)payload;
    Rcpp::Reference ref = Rcpp::internal::make_new_object(new OID(id));
    l->push_back(ref);
    return 0;
}

Rcpp::List ODB::list()
{
    Rcpp::List v;
    _git_odb_foreach(odb.get(), &list_cb, &v);
    return v;
}

Rcpp::Reference ODB::read(SEXP s)
{
    git_odb_object *result;
    _git_odb_read(&result, odb.get(), OID::from_sexp(s));
    return Rcpp::internal::make_new_object(new ODBObject(result));
}

RCPP_MODULE(guitar_odb) {
    using namespace Rcpp;
    class_<ODB>("ODB")
        .method("exists", &ODB::exists)
        .method("foreach", &ODB::foreach)
        .method("list", &ODB::list)
        .method("read", &ODB::read)
        ;
}
