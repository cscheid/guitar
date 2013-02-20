library(stringr)

context("basic sanity checks.")

existing.repo.path = paste(tempdir(), "/repo1", sep="")
new.repo.path = paste(tempdir(), "/repo2", sep="")

setup.tests <- function ()
{
  system(str_c("tar xzf ", system.file(package="guitar"),
               "/data/test-repos/repo1.tar.gz", " -C ", tempdir()))
}

teardown.tests <- function ()
{
  system(str_c("rm -rf ", existing.repo.path))
  system(str_c("rm -rf ", new.repo.path))
}

reset.tests <- function()
{
  teardown.tests();
  setup.tests();
}

################################################################################

setup.tests()

test_that("repositories can be loaded", {
  expect_that(new(guitar::Repository, existing.repo.path), is_a("Rcpp_Repository"))
})

test_that("bad repositories throw", {
  expect_that(new(guitar::Repository, "this should never work"), throws_error("Error : Repository not found"))
})

test_that("repositories have indices", {
  r <- new(guitar::Repository, existing.repo.path)
  expect_that(r$index(), is_a("Rcpp_Index"))
})

test_that("repositories have ODBs", {
  r <- new(guitar::Repository, existing.repo.path)
  expect_that(r$odb(), is_a("Rcpp_ODB"))
})

test_that("references can be found by name", {
  repo <- new(guitar::Repository, existing.repo.path)
  ref <- repo$reference_lookup("refs/heads/master")
  expect_that(ref, is_a("Rcpp_Reference"))
  oid <- repo$name_to_id("refs/heads/master")
  expect_that(oid, is_a("Rcpp_OID"))
  expect_that(oid$fmt(), is_a("character"));
})

test_that("repositories have ODBs which can be listed", {
  r <- new(guitar::Repository, existing.repo.path)
  o <- r$odb()
  expect_that(o, is_a("Rcpp_ODB"))
  l <- o$list()
  expect_that(o$exists(l[[1]]), equals(TRUE))
})

test_that("ODBs have OIDs which can be looked up", {
  r <- new(guitar::Repository, existing.repo.path)
  o <- r$odb()
  expect_that(o, is_a("Rcpp_ODB"))
  l <- o$list()
  for (oid in sample(l, 10, replace=TRUE)) {
    obj <- r$object_lookup(oid, guitar::GIT_OBJ_ANY)
    expect_that(obj, is_a(c("Rcpp_Tree", "Rcpp_Commit", "Rcpp_Blob", "Rcpp_Tag")))
  }
})

test_that("Objects can be added to the index", {
  r <- new(guitar::Repository, existing.repo.path)
  index <- r$index()
  p <- str_c(existing.repo.path, "/file3")
  cat("some content", file=p, append=TRUE)
  cat("some more content", file=p, append=TRUE)
  index$add_by_path("file3")
  index$write() # write() is needed to write index to disk
})

test_that("Commit can be created", {
  reset.tests(); # delete repo so we can re-add things to index
  r <- new(guitar::Repository, existing.repo.path)
  index <- r$index()
  p <- str_c(existing.repo.path, "/file3")
  cat("some content", file=p, append=TRUE)
  cat("some more content", file=p, append=TRUE)
  index$add_by_path("file3")
  index$write() # write() is needed to write index to disk
  oid <- index$write_tree()
  tree <- r$object_lookup(oid, GIT_OBJ_TREE)
  expect_that(tree, is_a("Rcpp_Tree"))
  sig <- make_signature("Carlos Scheidegger",
                        "cscheid@research.att.com")
  r$create_commit("HEAD", sig, sig,
                  "UTF-8", "This is a message.\n",
                  tree, list(r$head()$peel(GIT_OBJ_COMMIT)))
})

test_that("Repositories can be created and and committed to", {
  # FALSE because it's not a bare repo
  r <- repository_init(new.repo.path, FALSE);
  index <- r$index()
  p <- str_c(new.repo.path, "/file1")
  cat("some stuff", file=p)
  index$add_by_path("file1")
  index$write()
  oid <- index$write_tree()
  tree <- r$object_lookup(oid, GIT_OBJ_TREE)
  expect_that(tree, is_a("Rcpp_Tree"))
  sig <- make_signature("Carlos Scheidegger", "cscheid@research.att.com")
  r$create_commit("HEAD", sig, sig, "UTF-8", "First commit.\n",
                  tree, list());
})

test_that("add_file_to_head convenience function works", {
  r <- repository_init(new.repo.path, FALSE);
  local.path <- str_c(tempdir(), "/stuff")
  cat("blergh", file=local.path)
  add_file_to_head(r, local.path, "dest")
  index_entry <- r$index()$get_by_path("dest", 0)
  expect_that(is.null(index_entry), is_false())
})

test_that("remove_file_from_head function works", {
  reset.tests(); # delete repo so we can re-add things to index
  r <- new(guitar::Repository, existing.repo.path)
  remove_file_from_head(r, "file1")
  expect_that(r$index()$get_by_path("file1", 0), throws_error())
})

test_that("commits expose trees and tree_ids", {
  r <- new(guitar::Repository, existing.repo.path)
  c <- r$head()$peel(GIT_OBJ_COMMIT)
  expect_that(c$tree(), is_a("Rcpp_Tree"));
  expect_that(c$tree_id(), is_a("Rcpp_OID"));
})

teardown.tests()
