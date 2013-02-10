#pragma once

#include "guitar.h"

/******************************************************************************/

class Blob: public CPPWrapperObjectTraits<Blob, git_blob>
{
public:
    explicit Blob(git_blob *_blob);

    Rcpp::Reference id();
    bool is_binary();
    size_t size();
    Rcpp::RawVector data();
    
protected:
    boost::shared_ptr<git_blob> blob;
};
