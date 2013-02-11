#include "oid.h"
#include "entry_points.h"

OID::OID()
{
    git_oid_fromstr(&oid, GIT_OID_HEX_ZERO);
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
    int result = git_oid_fromstr(&oid, str.c_str());
    if (result)
        throw Rcpp::exception("bad string for OID constructor");
}

std::string OID::fmt()
{
    std::string out(41,' ');
    out[40] = '\0';
    git_oid_fmt((char*) &out[0], &oid);
    return out;
}

RCPP_MODULE(guitar_oid) {
    using namespace Rcpp;
    class_<OID>("OID")
        .constructor<std::string>()
        .method("fmt", &OID::fmt)
        ;
}
