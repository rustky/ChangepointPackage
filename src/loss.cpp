#include <stdio.h>
#include "loss.h"
#include <RcppArmadillo.h>
using namespace std;
using namespace arma;
//' Compute Square Loss
//' @param sum_vec vector of cumulatively summed input data values [1 x N]
//' @param N_vec vector from 1 to N [1 x N]
//' @useDynlib ChangepointPackage
//' @returns vector loss values [1 x N]
//' @export
// [Rcpp::depends(RcppArmadillo)]

arma::vec loss(
    arma::vec sum_vec,
    arma::vec N_vec
){
  vec augmented_sum_vec = -square(sum_vec);
  arma::vec loss_vec = augmented_sum_vec/N_vec;
  return loss_vec;
}
