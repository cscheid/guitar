.onLoad <- function(libname, pkgname) {
  loadRcppModules();
  if (!.Call("load_library", PACKAGE="guitar")) {
    cat("Could not successfully load shared library; this is not going to work.\n");
  }
}

# I need this for now because I know of no other way to access the
# .pointer slot from Rcpp.
.extractPointer <- function(ref) {
  ref$.pointer
}

################################################################################
# types.h

GIT_OBJ_ANY = -2 #		/**< Object can be any of the following */
GIT_OBJ_BAD = -1 #		/**< Object is invalid. */
GIT_OBJ_COMMIT = 1 #		/**< A commit object. */
GIT_OBJ_TREE = 2 #		/**< A tree (directory listing) object. */
GIT_OBJ_BLOB = 3 #		/**< A file revision object. */
GIT_OBJ_TAG = 4 #		/**< An annotated tag object. */
GIT_OBJ_OFS_DELTA = 6 # /**< A delta, base is given by an offset. */
GIT_OBJ_REF_DELTA = 7 # /**< A delta, base is given by object id. */

GIT_REF_INVALID = 0 # /** Invalid reference */
GIT_REF_OID = 1 # /** A reference which points at an object id */
GIT_REF_SYMBOLIC = 2 # /** A reference which points at another reference */
GIT_REF_PACKED = 4 #
GIT_REF_HAS_PEEL = 8 #
GIT_REF_LISTALL = 15 # GIT_REF_OID|GIT_REF_SYMBOLIC|GIT_REF_PACKED,

GIT_BRANCH_LOCAL = 1 #
GIT_BRANCH_REMOTE = 2 #

GIT_FILEMODE_NEW = 0 #					= 0000000 #
GIT_FILEMODE_TREE = 16384 #				= 0040000 #
GIT_FILEMODE_BLOB = 33188 #				= 0100644 #
GIT_FILEMODE_BLOB_EXECUTABLE = 33261 #		= 0100755 #
GIT_FILEMODE_LINK = 40960 #					= 0120000 #
GIT_FILEMODE_COMMIT = 57344 #					= 0160000 #

