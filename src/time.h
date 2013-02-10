#pragma once

#include "guitar.h"

/******************************************************************************/

class Time
{
public:
    static SEXP create(const git_time *t);
    git_time from_sexp(SEXP sexp);
};
