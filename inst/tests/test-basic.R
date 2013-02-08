context("basic sanity checks.")

test_that("repositories can be loaded", {
  expect_that(new(guitar::Repository, "/Users/cscheid/code/facet/.git"), is_a("Rcpp_Repository"))
})

test_that("repositories have indices", {
  r <- new(guitar::Repository, "/Users/cscheid/code/facet/.git")
  expect_that(r$index(), is_a("Rcpp_Index"))
  print(r$index()$entrycount())
})
