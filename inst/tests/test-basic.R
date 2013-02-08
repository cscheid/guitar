context("basic sanity checks.")

## repo.path <- paste(getwd(), "/../.git", sep="")
repo.path <- "/Users/cscheid/code/guitar/.git"

test_that("repositories can be loaded", {
  
  expect_that(new(guitar::Repository, repo.path), is_a("Rcpp_Repository"))
})

test_that("repositories have indices", {
  r <- new(guitar::Repository, repo.path)
  expect_that(r$index(), is_a("Rcpp_Index"))
})

test_that("references can be found by name", {
  repo <- new(guitar::Repository, repo.path)
  ref <- repo$reference_lookup("refs/heads/master")
  expect_that(ref, is_a("Rcpp_Reference"))
})
