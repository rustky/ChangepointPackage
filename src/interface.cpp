#include <R.h>
#include <R_ext/Rdynload.h>
#include <stdlib.h>
#include <Rcpp.h>
#include "DynamProg.h"
using namespace Rcpp;
//' Optimal Segmentation
//' @param data_vec numeric data vector of response variables[1 x n]
//' @param Kmax int desired number of segments
//' @importFrom Rcpp evalCpp
//' @useDynlib ChangepointPackage
//' @returns Output list including the changepoint locations and the cluster assignment vector [1 x n]
//' @export
// [[Rcpp::export]]
NumericVector DynamProg_interface(NumericVector data_vec,
                               int Kmax) {
  double *data_ptr = &data_vec[0];
  int N_data = data_vec.length();
  NumericVector changepoint_vec(Kmax);
  double *changepoint_ptr = &changepoint_vec[0];
  int status = DynamProg(data_ptr, Kmax, N_data, changepoint_ptr);
  if(status == ERROR_TOO_MANY_SEGMENTS){
    Rcpp::stop("Kmax must be less than N data!");
  }
  return changepoint_vec;
}
