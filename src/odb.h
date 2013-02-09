#pragma once

#include "guitar.h"
#include <boost/shared_ptr.hpp>
#include "oid.h"

/******************************************************************************/

class ODB
{
public:
    explicit ODB(git_odb *odb);

    // bool exists(Rcpp::XPtr<OID> oid);
    bool exists(SEXP s);
    void foreach(Rcpp::Function fcall);
    Rcpp::List list();
    Rcpp::Reference read(SEXP s);

protected:
    boost::shared_ptr<git_odb> odb;
};
