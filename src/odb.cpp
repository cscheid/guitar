#include "odb.h"
#include "entry_points.h"

/******************************************************************************/

ODB::ODB(git_odb *_odb)
{
    odb = boost::shared_ptr<git_odb>(_odb, _git_odb_free);
}

RCPP_MODULE(guitar_odb) {
    using namespace Rcpp;
    class_<ODB>("ODB")
        ;
}
