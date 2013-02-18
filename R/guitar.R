.onLoad <- function(libname, pkgname) {
  # in order to work around Rcpp's overly strict requirements on who
  # can call loadRcppModules, we reproduce the necessary functionality
  # here.
  
  ## loadRcppModules();
  ns <- asNamespace(pkgname);
  description <- packageDescription(pkgname, libname)
  modules <- strsplit(description[["RcppModules"]], "[[:space:]]*,[[:space:]]*")[[1L]]
  for (m in modules) {
    mod <- Rcpp::Module(m, pkgname, mustStart = TRUE)
    populate(mod, ns)
    assign(Rcpp:::.moduleMetaName(m), mod, envir = ns)
  }
}

# I need this for now because I know of no other way to access the
# .pointer slot from Rcpp.
.extractPointer <- function(ref) {
  ref$.pointer
}

# convenience method to add and commit a single file to the repository HEAD
# only works for non-bare repositories
add_file_to_head <- function(repository, local.path, path.in.repository,
                             user=Sys.getenv("USER"),
                             email=Sys.getenv("EMAIL"),
                             commit_message="")
{
  if (repository$is_bare())
    stop("Only for non-bare repos")
  repo.path <- repository$workdir()
  destination.path <- str_c(repo.path, path.in.repository)
  file.copy(local.path, destination.path, overwrite=TRUE)
  index <- repository$index()
  index$add_by_path(path.in.repository)
  index$write()
  oid <- index$write_tree()
  tree <- repository$object_lookup(oid, GIT_OBJ_TREE)
  email <- if (email == "") "Unknown" else email
  sig <- make_signature(user, email)
  parents <- (if (repository$is_empty()) list()
              else list(repository$head()$peel(GIT_OBJ_COMMIT)))
  repository$create_commit("HEAD", sig, sig, "UTF-8", commit_message,
                           tree, parents);
}

remove_file_from_head <- function(repository, path.in.repository,
                                  user=Sys.getenv("USER"),
                                  email=Sys.getenv("EMAIL"),
                                  commit_message="")
{
  if (repository$is_bare())
    stop("Only for non-bare repos")
  index <- repository$index()
  index$remove_by_path(path.in.repository)
  index$write()
  oid <- index$write_tree()
  tree <- repository$object_lookup(oid, GIT_OBJ_TREE)
  email <- if (email == "") "Unknown" else email
  sig <- make_signature(user, email)
  parents <- (if (repository$is_empty()) list()
              else list(repository$head()$peel(GIT_OBJ_COMMIT)))
  repository$create_commit("HEAD", sig, sig, "UTF-8", commit_message,
                           tree, parents);
  unlink(str_c(repository$workdir(),"/",path.in.repository))
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

