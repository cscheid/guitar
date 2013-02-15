context("basic sanity checks.")

repo.path = paste(tempdir(), "/repo1", sep="")

setup.tests <- function ()
{
  system(paste("tar xzf ", system.file(package="guitar"), "/data/test-repos/repo1.tar.gz", " -C ", tempdir(), sep=""))
}

setup.tests()

test_that("repositories can be loaded", {
  expect_that(new(guitar::Repository, repo.path), is_a("Rcpp_Repository"))
})

test_that("bad repositories throw", {
  expect_that(new(guitar::Repository, "this should never work"), throws_error("Error : Repository not found"))
})

test_that("repositories have indices", {
  r <- new(guitar::Repository, repo.path)
  expect_that(r$index(), is_a("Rcpp_Index"))
})

test_that("repositories have ODBs", {
  r <- new(guitar::Repository, repo.path)
  expect_that(r$odb(), is_a("Rcpp_ODB"))
})

test_that("references can be found by name", {
  repo <- new(guitar::Repository, repo.path)
  ref <- repo$reference_lookup("refs/heads/master")
  expect_that(ref, is_a("Rcpp_Reference"))
  oid <- repo$name_to_id("refs/heads/master")
  expect_that(oid, is_a("Rcpp_OID"))
  expect_that(oid$fmt(), is_a("character"));
})

test_that("repositories have ODBs which can be listed", {
  r <- new(guitar::Repository, repo.path)
  o <- r$odb()
  expect_that(o, is_a("Rcpp_ODB"))
  l <- o$list()
  expect_that(o$exists(l[[1]]), equals(TRUE))
})

test_that("ODBs have OIDs which can be looked up", {
  r <- new(guitar::Repository, repo.path)
  o <- r$odb()
  expect_that(o, is_a("Rcpp_ODB"))
  l <- o$list()
  for (oid in sample(l, 10, replace=TRUE)) {
    obj <- r$object_lookup(oid, guitar::GIT_OBJ_ANY)
    expect_that(obj, is_a(c("Rcpp_Tree", "Rcpp_Commit", "Rcpp_Blob", "Rcpp_Tag")))
  }
})

