#pragma once

#include <RcppCommon.h>
#include <Rcpp.h>
#include <git2.h>
#include "oid.h"

/******************************************************************************/

class OID
{
public:
    OID();
    explicit OID(std::string str);

    std::string fmt();

    operator git_oid *(){ return &oid; }

protected:
    git_oid oid;
};
