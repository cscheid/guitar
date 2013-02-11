#include "time.h"

/******************************************************************************/

SEXP Time::create(const git_time *t)
{
    // FIXME check whether this cast is safe
    return Rcpp::List::create(Rcpp::Named("time") = (long)t->time,
                              Rcpp::Named("offset") = t->offset);
}

git_time Time::from_sexp(SEXP sexp)
{
    git_time result;
    Rcpp::List l(sexp);
    result.time = l["time"];
    result.offset = l["offset"];
    return result;
}
