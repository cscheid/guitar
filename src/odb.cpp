#include "odb.h"
#include "entry_points.h"

/******************************************************************************/

ODB::ODB(git_odb *_odb)
{
    odb = boost::shared_ptr<git_odb>(_odb, _git_odb_free);
}

bool ODB::exists(Rcpp::XPtr<OID> oid)
{
    const OID *oidp = static_cast<const OID*>(oid);
    const git_oid *oidp2 = static_cast<const git_oid*>(*oidp);
    return _git_odb_exists(odb.get(), oidp2);
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

RCPP_MODULE(guitar_odb) {
    using namespace Rcpp;
    class_<ODB>("ODB")
        .method("exists", &ODB::exists)
        .method("foreach", &ODB::foreach)
        .method("list", &ODB::list)
        ;
}
