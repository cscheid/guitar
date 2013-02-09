#include "oid.h"
#include "entry_points.h"

OID::OID()
{
    _git_oid_fromstr(&oid, GIT_OID_HEX_ZERO);
}

OID::OID(const git_oid *other_oid)
{
    oid = *other_oid;
}

OID::OID(std::string str)
{
    if (str.size() < 40) {
        throw Rcpp::exception("string too small for OID constructor");
    }
    int result = _git_oid_fromstr(&oid, str.c_str());
    if (result)
        throw Rcpp::exception("bad string for OID constructor");
}

std::string OID::fmt()
{
    std::string out(41,' ');
    out[40] = '\0';
    _git_oid_fmt((char*) &out[0], &oid);
    return out;
}

const git_oid *OID::from_sexp(SEXP s)
{
    Rcpp::Function x = Rcpp::Environment::namespace_env("guitar")[".extractPointer"];
    Rcpp::XPtr<OID> oid_ptr(x(s));
    const git_oid *oidp2 = static_cast<const git_oid*>(*oid_ptr);
    return oidp2;
}

Rcpp::Reference OID::create(const git_oid *oid)
{
    return Rcpp::internal::make_new_object(new OID(oid));
}

RCPP_MODULE(guitar_oid) {
    using namespace Rcpp;
    class_<OID>("OID")
        .constructor<std::string>()
        .method("fmt", &OID::fmt)
        ;
}
