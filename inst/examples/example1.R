library(guitar)

r <- new(guitar::Repository, "/Users/cscheid/code/facet/.git")
o <- r$odb()
l <- o$list()

for (oid in l) {
  obj <- r$object_lookup(oid, guitar::GIT_OBJ_ANY)
  if (!is.null(obj)) {
    if (obj$type() == guitar::GIT_OBJ_COMMIT) {
      cat(sprintf("Commit %s by %s\n", obj$id()$fmt(), obj$author()$name))
    }
  }
}
