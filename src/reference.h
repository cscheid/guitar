#pragma once

#include <RcppCommon.h>
#include <Rcpp.h>
#include <git2.h>
#include <boost/shared_ptr.hpp>

class GitReference
{
public:
    explicit GitReference(git_reference *_ref); 
    bool has_log();

protected:
    boost::shared_ptr<git_reference> ref;
};

