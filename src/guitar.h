#pragma once

#include <RcppCommon.h>
#include <Rcpp.h>
#include <git2.h>
#include <boost/shared_ptr.hpp>

/******************************************************************************/

// the Rcpp::internal::make_new_object technique I use below comes from here:
// http://lists.r-forge.r-project.org/pipermail/rcpp-devel/2012-September/004265.html
template <typename SelfType, typename CGitType>
struct CPPWrapperObjectTraits {
    typedef SelfType Self;
    
    static const CGitType *from_sexp(SEXP s) {
        Rcpp::Function x = Rcpp::Environment::namespace_env("guitar")[".extractPointer"];
        Rcpp::XPtr<Self> obj_ptr(x(s));
        const CGitType *result = static_cast<const CGitType*>(obj_ptr->unwrap());
        return result;
    };

    static Rcpp::Reference create(CGitType *obj) {
        return Rcpp::internal::make_new_object(new Self(obj));
    };

    static Rcpp::Reference create(const CGitType *obj) {
        return Rcpp::internal::make_new_object(new Self(obj));
    };
};

SEXP object_to_sexp(git_object *obj);

// with namespace instead of struct and static methods, I can use
// the functions inside RCPP_MODULEs
namespace Signature {
    SEXP create(const git_signature *sig);
    SEXP now(std::string name, std::string email);
};
