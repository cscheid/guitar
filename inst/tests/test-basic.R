context("basic sanity checks.")

test_that("repositories can be loaded", {
  expect_that(new(guitar::Repository, "/Users/cscheid/code/facet/.git"), is_a("Rcpp_Repository"));
})
