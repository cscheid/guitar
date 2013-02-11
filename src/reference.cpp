#include "reference.h"
#include "entry_points.h"

using namespace Rcpp;

GitReference::GitReference(git_reference *_ref)
{
    ref = boost::shared_ptr<git_reference>(_ref, git_reference_free);
}

bool GitReference::has_log()
{
    return git_reference_has_log(ref.get());
}

RCPP_MODULE(guitar_reference) {
    class_<GitReference>("Reference")
        .method("has_log", &GitReference::has_log)
        ;
}
