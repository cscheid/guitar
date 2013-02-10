#include "guitar.h"
#include "entry_points.h"
#include "commit.h"
#include "tree.h"
#include "blob.h"

using namespace Rcpp;

SEXP object_to_sexp(git_object *obj)
{
    git_otype result_type = _git_object_type(obj);
    
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
    default:
        return R_NilValue;
    // case GIT_OBJ_TAG:
    //     return R_NilValue;
    //     break;
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
