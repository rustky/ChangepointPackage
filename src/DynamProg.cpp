#include "DynamProg.h"
#include <stdio.h>
#include "loss.h"
#include <RcppArmadillo.h>
using namespace Rcpp;
using namespace arma;
// [Rcpp::depends(RcppArmadillo)]
//'
//'
//' @export
int DynamProg(
    const double *data_ptr,
    const int Kmax,
    const int N_data,
    double *changepoint_ptr
){
  if(Kmax > N_data){
    return ERROR_TOO_MANY_SEGMENTS;
  }
  arma::mat loss_mat(N_data, Kmax, fill::zeros);
  arma::mat last_mean_mat(N_data, Kmax, fill::zeros);
  arma::mat last_change(N_data, Kmax, fill::zeros);
  arma::vec data_vec(data_ptr, N_data);
  arma::vec cum_vec = arma::cumsum(data_vec);
  arma::vec cum_n = arma::linspace<vec>(1,N_data,N_data);
  arma::vec changepoints(Kmax, fill::ones);
  loss_mat.col(0) = loss(cum_vec, cum_n);
  last_mean_mat.col(0) = cum_vec/cum_n;
  for(int N_segs = 1; N_segs < Kmax; N_segs++){
    for(int up_to = N_segs; up_to < N_data; up_to++){
      int size = up_to - N_segs;
      if(size == 0){
        size = 1;
      }
      arma::vec possible_last_end(size,fill::zeros);
      for(int fill = 0; fill < size; fill++){
        possible_last_end(fill) = fill;
      }
      arma::vec prev_loss(size,fill::zeros);
      arma::vec sum_last_segs(size, fill::zeros);
      for(int ends = 0; ends < size ; ends++){
        prev_loss(ends) = loss_mat(ends,N_segs-1);
        sum_last_segs(ends) = cum_vec(up_to) -
          cum_vec(ends);
      }
      arma::vec N_last_segs = up_to - possible_last_end;
      arma::vec last_loss = loss(sum_last_segs, N_last_segs);
      arma::vec total_loss = prev_loss + last_loss;
      uword best_idx = total_loss.index_min();
      arma::vec avg_vec = (sum_last_segs/N_segs);
      last_mean_mat(up_to, N_segs) = avg_vec(best_idx);
      last_change(up_to, N_segs) = possible_last_end(best_idx);
      // last_change.brief_print("last_change:");
      loss_mat(up_to, N_segs) = total_loss(best_idx);
    }
  int seg_end = N_data - 1;
  for(int seg_i = N_segs; seg_i > 0; seg_i--){
    int prev_end = last_change(seg_end, seg_i);
    if(seg_i == 0){
      changepoints(seg_i) = seg_i;
    }
    else{
      changepoints(seg_i) = prev_end + 2;
    }
    seg_end = prev_end;
  }
  }
  changepoints.print();
  for(int points = 0; points < Kmax; points++){
    changepoint_ptr[points] = changepoints(points);
  }
  return 0;
}
