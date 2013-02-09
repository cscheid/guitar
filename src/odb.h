#pragma once

#include "guitar.h"
#include <boost/shared_ptr.hpp>
#include "oid.h"

/******************************************************************************/

class ODB
{
public:
    explicit ODB(git_odb *odb);

    // expects an OID, returns true if object with that OID is in the ODB.
    bool exists(SEXP oid);

    // traverses the list of OIDs, calls this function with each OID.
    void foreach(Rcpp::Function fcall);

    // returns a list of OIDs
    Rcpp::List list();

    // returns the ODBObject with the given OID 
    Rcpp::Reference read(SEXP oid);

protected:
    boost::shared_ptr<git_odb> odb;
};
