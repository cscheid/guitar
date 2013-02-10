#pragma once

#include "guitar.h"
#include <boost/shared_ptr.hpp>

/******************************************************************************/

class ODBObject: public CPPWrapperObjectTraits<ODBObject, git_odb_object>
{
public:
    explicit ODBObject(git_odb_object *_obj);

    size_t size();
    Rcpp::RawVector data();
    unsigned int type();
    Rcpp::Reference id();

    git_odb_object *unwrap() { return obj.get(); }

protected:
    boost::shared_ptr<git_odb_object> obj;
};
