library(ChangepointPackage)
library(testthat)
library(jointseg)
context("Changepoint Detection")

test_that("Optimal Segmentation produces a resonable result",{
  data(neuroblastoma, package="neuroblastoma")
  library(data.table)
  nb.dt <- data.table(neuroblastoma$profiles)
  data.dt <- nb.dt[profile.id=="1" & chromosome=="1"]
  data.vec <- data.dt[["logratio"]]
  Kmax <- 5
  mine.change <- ChangepointPackage::DynamProg_interface(data.vec,5)
  Fpsn.fit <- jointseg::Fpsn(data.vec,Kmax)
  Fpsn.end <- Fpsn.fit$t.est[Kmax, 1:Kmax]
  Fpsn.start <- c(1, Fpsn.end[-length(Fpsn.end)]+1)
  expect_equal(Fpsn.start, mine.change)
})

