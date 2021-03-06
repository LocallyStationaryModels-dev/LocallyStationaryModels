// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppEigen.h>
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// find_anchorpoints
Rcpp::List find_anchorpoints(const Eigen::MatrixXd& data, const size_t& n_pieces);
RcppExport SEXP _LocallyStationaryModels_find_anchorpoints(SEXP dataSEXP, SEXP n_piecesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type data(dataSEXP);
    Rcpp::traits::input_parameter< const size_t& >::type n_pieces(n_piecesSEXP);
    rcpp_result_gen = Rcpp::wrap(find_anchorpoints(data, n_pieces));
    return rcpp_result_gen;
END_RCPP
}
// variogramlsm
Rcpp::List variogramlsm(const Eigen::VectorXd& z, const Eigen::MatrixXd& data, const Eigen::MatrixXd& anchorpoints, const double& epsilon, const size_t& n_angles, const size_t& n_intervals, const std::string& kernel_id, const bool print, const int& n_threads);
RcppExport SEXP _LocallyStationaryModels_variogramlsm(SEXP zSEXP, SEXP dataSEXP, SEXP anchorpointsSEXP, SEXP epsilonSEXP, SEXP n_anglesSEXP, SEXP n_intervalsSEXP, SEXP kernel_idSEXP, SEXP printSEXP, SEXP n_threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Eigen::VectorXd& >::type z(zSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type data(dataSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type anchorpoints(anchorpointsSEXP);
    Rcpp::traits::input_parameter< const double& >::type epsilon(epsilonSEXP);
    Rcpp::traits::input_parameter< const size_t& >::type n_angles(n_anglesSEXP);
    Rcpp::traits::input_parameter< const size_t& >::type n_intervals(n_intervalsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kernel_id(kernel_idSEXP);
    Rcpp::traits::input_parameter< const bool >::type print(printSEXP);
    Rcpp::traits::input_parameter< const int& >::type n_threads(n_threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(variogramlsm(z, data, anchorpoints, epsilon, n_angles, n_intervals, kernel_id, print, n_threads));
    return rcpp_result_gen;
END_RCPP
}
// findsolutionslsm
Rcpp::List findsolutionslsm(const Eigen::MatrixXd& anchorpoints, const Eigen::MatrixXd& empiricvariogram, const Eigen::MatrixXd& squaredweights, const Eigen::VectorXd& mean_x, const Eigen::VectorXd& mean_y, std::string& variogram_id, const std::string& kernel_id, const Eigen::VectorXd& parameters, const Eigen::VectorXd& lowerbound, const Eigen::VectorXd& upperbound, const double& epsilon, const double& lowerdelta, const double& upperdelta, const bool print, const int& n_threads);
RcppExport SEXP _LocallyStationaryModels_findsolutionslsm(SEXP anchorpointsSEXP, SEXP empiricvariogramSEXP, SEXP squaredweightsSEXP, SEXP mean_xSEXP, SEXP mean_ySEXP, SEXP variogram_idSEXP, SEXP kernel_idSEXP, SEXP parametersSEXP, SEXP lowerboundSEXP, SEXP upperboundSEXP, SEXP epsilonSEXP, SEXP lowerdeltaSEXP, SEXP upperdeltaSEXP, SEXP printSEXP, SEXP n_threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type anchorpoints(anchorpointsSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type empiricvariogram(empiricvariogramSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type squaredweights(squaredweightsSEXP);
    Rcpp::traits::input_parameter< const Eigen::VectorXd& >::type mean_x(mean_xSEXP);
    Rcpp::traits::input_parameter< const Eigen::VectorXd& >::type mean_y(mean_ySEXP);
    Rcpp::traits::input_parameter< std::string& >::type variogram_id(variogram_idSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kernel_id(kernel_idSEXP);
    Rcpp::traits::input_parameter< const Eigen::VectorXd& >::type parameters(parametersSEXP);
    Rcpp::traits::input_parameter< const Eigen::VectorXd& >::type lowerbound(lowerboundSEXP);
    Rcpp::traits::input_parameter< const Eigen::VectorXd& >::type upperbound(upperboundSEXP);
    Rcpp::traits::input_parameter< const double& >::type epsilon(epsilonSEXP);
    Rcpp::traits::input_parameter< const double& >::type lowerdelta(lowerdeltaSEXP);
    Rcpp::traits::input_parameter< const double& >::type upperdelta(upperdeltaSEXP);
    Rcpp::traits::input_parameter< const bool >::type print(printSEXP);
    Rcpp::traits::input_parameter< const int& >::type n_threads(n_threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(findsolutionslsm(anchorpoints, empiricvariogram, squaredweights, mean_x, mean_y, variogram_id, kernel_id, parameters, lowerbound, upperbound, epsilon, lowerdelta, upperdelta, print, n_threads));
    return rcpp_result_gen;
END_RCPP
}
// predikt
Rcpp::List predikt(const Eigen::VectorXd& z, const Eigen::MatrixXd& data, const Eigen::MatrixXd& anchorpoints, const double& epsilon, const double& delta, const Eigen::MatrixXd& solutions, const Eigen::MatrixXd& positions, const std::string& variogram_id, const std::string& kernel_id, const bool print, const int& n_threads);
RcppExport SEXP _LocallyStationaryModels_predikt(SEXP zSEXP, SEXP dataSEXP, SEXP anchorpointsSEXP, SEXP epsilonSEXP, SEXP deltaSEXP, SEXP solutionsSEXP, SEXP positionsSEXP, SEXP variogram_idSEXP, SEXP kernel_idSEXP, SEXP printSEXP, SEXP n_threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Eigen::VectorXd& >::type z(zSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type data(dataSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type anchorpoints(anchorpointsSEXP);
    Rcpp::traits::input_parameter< const double& >::type epsilon(epsilonSEXP);
    Rcpp::traits::input_parameter< const double& >::type delta(deltaSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type solutions(solutionsSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type positions(positionsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type variogram_id(variogram_idSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kernel_id(kernel_idSEXP);
    Rcpp::traits::input_parameter< const bool >::type print(printSEXP);
    Rcpp::traits::input_parameter< const int& >::type n_threads(n_threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(predikt(z, data, anchorpoints, epsilon, delta, solutions, positions, variogram_id, kernel_id, print, n_threads));
    return rcpp_result_gen;
END_RCPP
}
// smoothing
Rcpp::List smoothing(const Eigen::MatrixXd solutions, const Eigen::MatrixXd& anchorpoints, const double& delta, const Eigen::MatrixXd& positions, const std::string& kernel_id, const int& n_threads);
RcppExport SEXP _LocallyStationaryModels_smoothing(SEXP solutionsSEXP, SEXP anchorpointsSEXP, SEXP deltaSEXP, SEXP positionsSEXP, SEXP kernel_idSEXP, SEXP n_threadsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const Eigen::MatrixXd >::type solutions(solutionsSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type anchorpoints(anchorpointsSEXP);
    Rcpp::traits::input_parameter< const double& >::type delta(deltaSEXP);
    Rcpp::traits::input_parameter< const Eigen::MatrixXd& >::type positions(positionsSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type kernel_id(kernel_idSEXP);
    Rcpp::traits::input_parameter< const int& >::type n_threads(n_threadsSEXP);
    rcpp_result_gen = Rcpp::wrap(smoothing(solutions, anchorpoints, delta, positions, kernel_id, n_threads));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_LocallyStationaryModels_find_anchorpoints", (DL_FUNC) &_LocallyStationaryModels_find_anchorpoints, 2},
    {"_LocallyStationaryModels_variogramlsm", (DL_FUNC) &_LocallyStationaryModels_variogramlsm, 9},
    {"_LocallyStationaryModels_findsolutionslsm", (DL_FUNC) &_LocallyStationaryModels_findsolutionslsm, 15},
    {"_LocallyStationaryModels_predikt", (DL_FUNC) &_LocallyStationaryModels_predikt, 11},
    {"_LocallyStationaryModels_smoothing", (DL_FUNC) &_LocallyStationaryModels_smoothing, 6},
    {NULL, NULL, 0}
};

RcppExport void R_init_LocallyStationaryModels(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
