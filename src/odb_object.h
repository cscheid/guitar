#pragma once

#include <RcppCommon.h>
#include <Rcpp.h>
#include <boost/shared_ptr.hpp>
#include <git2.h>

/******************************************************************************/

class ODBObject
{
public:
    explicit ODBObject(git_odb_object *_obj);

    Rcpp::RawVector data();

protected:
    boost::shared_ptr<git_odb_object> obj;
};
