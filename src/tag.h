#pragma once

#include "guitar.h"

/******************************************************************************/

class Tag: public CPPWrapperObjectTraits<Tag, git_tag>
{
public:
    explicit Tag(git_tag *_tag);

    Rcpp::Reference id();
    std::string message();
    std::string name();
    SEXP peel();
    SEXP tagger();
    SEXP target();
    Rcpp::Reference target_id();
    int target_type();

protected:
    boost::shared_ptr<git_tag> tag;
};
