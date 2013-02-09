#pragma once

#include "guitar.h"
#include <boost/shared_ptr.hpp>

class GitReference: public CPPWrapperObjectTraits<GitReference, git_reference>
{
public:
    explicit GitReference(git_reference *_ref); 
    bool has_log();

protected:
    boost::shared_ptr<git_reference> ref;
};

