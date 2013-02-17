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

SEXP GitReference::peel(unsigned int otype)
{
    BEGIN_RCPP
    git_object *result;
    int err = git_reference_peel(&result, ref.get(), (git_otype) otype);
    if (err)
        throw Rcpp::exception("git_reference_peel failed");
    return object_to_sexp(result);
    END_RCPP
}

RCPP_MODULE(guitar_reference) {
    class_<GitReference>("Reference")
        .method("has_log", &GitReference::has_log)
        .method("peel", &GitReference::peel)
        ;
}
