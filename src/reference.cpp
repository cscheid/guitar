#include "reference.h"
#include "entry_points.h"

using namespace Rcpp;

GitReference::GitReference(git_reference *_ref)
{
    ref = boost::shared_ptr<git_reference>(_ref, _git_reference_free);
}

RCPP_MODULE(guitar_reference) {
    class_<GitReference>("Reference")
        ;
}
