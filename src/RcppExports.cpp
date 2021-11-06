// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// DynamProg_interface
NumericVector DynamProg_interface(NumericVector data_vec, int Kmax);
RcppExport SEXP _ChangepointPackage_DynamProg_interface(SEXP data_vecSEXP, SEXP KmaxSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector >::type data_vec(data_vecSEXP);
    Rcpp::traits::input_parameter< int >::type Kmax(KmaxSEXP);
    rcpp_result_gen = Rcpp::wrap(DynamProg_interface(data_vec, Kmax));
    return rcpp_result_gen;
END_RCPP
}
// loss
arma::vec loss(arma::vec sum_vec, arma::vec N_vec);
RcppExport SEXP _ChangepointPackage_loss(SEXP sum_vecSEXP, SEXP N_vecSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< arma::vec >::type sum_vec(sum_vecSEXP);
    Rcpp::traits::input_parameter< arma::vec >::type N_vec(N_vecSEXP);
    rcpp_result_gen = Rcpp::wrap(loss(sum_vec, N_vec));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_ChangepointPackage_DynamProg_interface", (DL_FUNC) &_ChangepointPackage_DynamProg_interface, 2},
    {"_ChangepointPackage_loss", (DL_FUNC) &_ChangepointPackage_loss, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_ChangepointPackage(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
