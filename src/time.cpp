#include "time.h"
#include <iostream>

using namespace std;

/******************************************************************************/

SEXP Time::create(const git_time *t)
{
    // FIXME check whether this cast is safe
    cerr << t->time << " " << ((long)t->time) << endl;
    return Rcpp::List::create(Rcpp::Named("time") = (long)t->time,
                              Rcpp::Named("offset") = t->offset);
}

git_time Time::from_sexp(SEXP sexp)
{
    git_time result;
    Rcpp::List l(sexp);
    cerr << "from_sexp: " << Rcpp::as<int>(l["offset"]) << " - " << Rcpp::as<long>(l["time"]) << endl;
    result.time = Rcpp::as<long>(l["time"]);
    result.offset = Rcpp::as<int>(l["offset"]);
    cerr << result.time << " - " << result.offset << endl;
    return result;
}
