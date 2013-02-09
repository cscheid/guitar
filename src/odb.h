#pragma once

#include <RcppCommon.h>
#include <Rcpp.h>
#include <boost/shared_ptr.hpp>
#include "oid.h"

/******************************************************************************/

class ODB
{
public:
    explicit ODB(git_odb *odb);

    bool exists(Rcpp::XPtr<OID> oid);
    void foreach(Rcpp::Function fcall);
    Rcpp::List list();

protected:
    boost::shared_ptr<git_odb> odb;
};
