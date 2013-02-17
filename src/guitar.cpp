#include "guitar.h"
#include "entry_points.h"
#include "commit.h"
#include "tree.h"
#include "blob.h"
#include "time.h"
#include "tag.h"
#include <iostream>

using namespace Rcpp;
using namespace std;

SEXP object_to_sexp(git_object *obj)
{
    git_otype result_type = git_object_type(obj);
    
    switch (result_type) {
    case GIT_OBJ_COMMIT: {
        git_commit *commit = (git_commit *)obj;
        return Commit::create(commit);
    } break;
    case GIT_OBJ_TREE: {
        git_tree *tree = (git_tree *)obj;
        return Tree::create(tree);
    } break;
    case GIT_OBJ_BLOB: {
        git_blob *blob = (git_blob *)obj;
        return Blob::create(blob);
    } break;
    case GIT_OBJ_TAG: {
        git_tag *tag = (git_tag *)obj;
        return Tag::create(tag);
    } break;
    default:
        return R_NilValue;
    // case GIT_OBJ_OFS_DELTA:
    //     return R_NilValue;
    //     break;
    // case GIT_OBJ_REF_DELTA:
    //     return R_NilValue;
    //     break;
    // default:
    //     throw Rcpp::exception("Bad object type");
    }
}

SEXP Signature::create(const git_signature *signature)
{
    return Rcpp::List::create(Rcpp::Named("name") = std::string(signature->name),
                              Rcpp::Named("email") = std::string(signature->email),
                              Rcpp::Named("time") = Time::create(&signature->when));
}

git_signature *Signature::from_sexp(SEXP sexp)
{
    git_signature *result;
    Rcpp::List l(Rcpp::as<Rcpp::List>(sexp));
    git_time t = Time::from_sexp(l["time"]);
    git_signature_new
        (&result, 
         Rcpp::as<std::string>(l["name"]).c_str(),
         Rcpp::as<std::string>(l["email"]).c_str(),
         t.time, t.offset);
    return result;
}

SEXP Signature::now(std::string name, std::string email)
{
    git_signature *_result;
    git_signature_now(&_result, name.c_str(), email.c_str());
    cerr << _result->when.time << " " << _result->when.offset << endl;
    SEXP result = Signature::create(_result);
    git_signature_free(_result);
    return result;
}

RCPP_MODULE(guitar)
{
    function("make_signature", &Signature::now);
}
