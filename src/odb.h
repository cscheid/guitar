#pragma once

#include <RcppCommon.h>
#include <Rcpp.h>
#include "reference.h"

/******************************************************************************/

class ODB
{
public:
    explicit ODB(git_odb *odb);

protected:
    boost::shared_ptr<git_odb> odb;
};
