#pragma once

#include "guitar.h"

/******************************************************************************/

struct Time
{
public:
    static SEXP create(const git_time *t);
    static git_time from_sexp(SEXP sexp);
};
