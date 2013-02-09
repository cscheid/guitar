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
    explicit OID(const git_oid *other_oid);

    std::string fmt();

    operator git_oid *() { return &oid; }
    operator const git_oid *() const { return &oid; }

protected:
    git_oid oid;
};
