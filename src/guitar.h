#pragma once

#include <RcppCommon.h>
#include <Rcpp.h>

// the Rcpp::internal::make_new_object technique I use throughout this library comes from here:
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

    static Rcpp::Reference create(const CGitType *obj) {
        return Rcpp::internal::make_new_object(new Self(obj));
    };
};
