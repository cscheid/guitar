#include "odb.h"
#include "entry_points.h"
#include "odb_object.h"
#include <cstdio>

/******************************************************************************/

ODB::ODB(git_odb *_odb)
{
    odb = boost::shared_ptr<git_odb>(_odb, _git_odb_free);
}

bool ODB::exists(SEXP s)
{
    return _git_odb_exists(odb.get(), OID::from_sexp(s));
}

// FIXME: add early termination by checking the result of callback.
static int foreach_cb(const git_oid *id, void *payload)
{
    Rcpp::Function *f = (Rcpp::Function *)payload;
    Rcpp::Reference ref = OID::create(id);
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
    Rcpp::Reference ref = OID::create(id);
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
    class_<ODB>("ODB", "ODB is the git object database")
        .method("exists", &ODB::exists, "given an OID, returns true if object with that OID is present")
        .method("foreach", &ODB::foreach, "traverses list of OIDs, calls given function with each OID")
        .method("list", &ODB::list, "returns list of OIDs in the ODB")
        .method("read", &ODB::read, "returns the ODBObject with the given OID")
        ;
}
