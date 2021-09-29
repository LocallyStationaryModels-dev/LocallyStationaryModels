// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// fullmodel
Rcpp::List fullmodel(const Eigen::VectorXd& y, const Eigen::MatrixXd& d, const Eigen::MatrixXd& anchorpoints, const double& epsilon, const unsigned int& n_angles, const unsigned int& n_intervals);
RcppExport SEXP _LocallyStationaryModels_fullmodel(SEXP ySEXP, SEXP dSEXP, SEXP anchorpointsSEXP, SEXP epsilonSEXP, SEXP n_anglesSEXP, SEXP n_intervalsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Eigen::VectorXd& >::type y(ySEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type d(dSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type anchorpoints(anchorpointsSEXP);
    Rcpp::traits::input_parameter< const double& >::type epsilon(epsilonSEXP);
    Rcpp::traits::input_parameter< const unsigned int& >::type n_angles(n_anglesSEXP);
    Rcpp::traits::input_parameter< const unsigned int& >::type n_intervals(n_intervalsSEXP);
    rcpp_result_gen = Rcpp::wrap(fullmodel(y, d, anchorpoints, epsilon, n_angles, n_intervals));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_LocallyStationaryModels_fullmodel", (DL_FUNC) &_LocallyStationaryModels_fullmodel, 6},
    {NULL, NULL, 0}
};

RcppExport void R_init_LocallyStationaryModels(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
