// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-

// Copyright (C) Luca Crippa <luca7.crippa@mail.polimi.it>
// Copyright (C) Giacomo De Carlo <giacomo.decarlo@mail.polimi.it>

#include <RcppEigen.h>
#include <chrono>

#include "anchor.hpp"
#include "kriging.hpp"
#include "samplevar.hpp"
#include "smooth.hpp"
#include "variogramfit.hpp"

using namespace LocallyStationaryModels;
using namespace LocallyStationaryModels::cd;
using namespace std::chrono;

// [[Rcpp::depends(RcppEigen)]]

/**
 * \brief finds the anchor points given the position of the points in the initial dataset
 * \param data a matrix with the coordinates of the points in the original dataset
 * \param n_pieces the number of cells per row and column in the grid of the anchor points
 */
// [[Rcpp::export]]
Rcpp::List find_anchorpoints(const Eigen::MatrixXd& data, const size_t& n_pieces)
{
    auto start = high_resolution_clock::now();

    matrixptr dd = std::make_shared<matrix>(data);

    Anchor a(dd, n_pieces);

    cd::matrix anchorpos = a.find_anchorpoints();

    return Rcpp::List::create(Rcpp::Named("anchorpoints") = anchorpos, Rcpp::Named("center_x") = a.get_origin().first,
        Rcpp::Named("center_y") = a.get_origin().second, Rcpp::Named("width") = a.get_tiles_dimensions().first,
        Rcpp::Named("height") = a.get_tiles_dimensions().second);
}

/**
 * \brief calculate the empiric variogram in each anchor points
 * \param z a vector with the values of Z for each point in the dataset data
 * \param data a matrix with the coordinates of the points in the original dataset
 * \param anchorpoints  a matrix with the coordinates of each anchor point
 * \param epsilon the value of the bandwidth parameter epsilon
 * \param n_angles the number of the angles for the grid
 * \param n_intervals the number of intervals for the grid
 * \param kernel_id the type of kernel to be used
 * \param print if set to true print on console the time required to process the output
 * \param n_threads the number of threads to be used by OPENMP. If negative, let OPENMP autonomously decide how many
 * threads to open
 */
// [[Rcpp::export]]
Rcpp::List variogramlsm(const Eigen::VectorXd& z, const Eigen::MatrixXd& data, const Eigen::MatrixXd& anchorpoints,
    const double& epsilon, const size_t& n_angles, const size_t& n_intervals, const std::string& kernel_id,
    const bool print, const int& n_threads)
{
    // start the clock
    auto start = high_resolution_clock::now();
    // if n_threads is positive open open n_threads threads to process the data
    // otherwise let openmp decide autonomously how many threads use
    // if n_threads is greater than the maximum number of threads available open all the threads accessible
    if (n_threads > 0) {
        int max_threads = omp_get_max_threads();
        int used_threads = std::min(max_threads, n_threads);
        Rcpp::Rcout << "desired: " << n_threads << std::endl;
        Rcpp::Rcout << "max: " << max_threads << std::endl;
        Rcpp::Rcout << "used: " << used_threads << std::endl;
        omp_set_num_threads(used_threads);
    }

    matrixptr dd = std::make_shared<matrix>(data);
    vectorptr zz = std::make_shared<vector>(z);
    matrixptr anchorpointsptr = std::make_shared<matrix>(anchorpoints);

    SampleVar samplevar_(kernel_id, n_angles, n_intervals, epsilon);
    // build the sample variogram
    samplevar_.build_samplevar(dd, anchorpointsptr, zz);
    // stop the clock and calculate the processing time
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    if (print)
        Rcpp::Rcout << "task successfully completed in " << duration.count() << "ms" << std::endl;

    return Rcpp::List::create(Rcpp::Named("kernel") = *(samplevar_.get_kernel()),
        Rcpp::Named("grid") = *(samplevar_.get_grid()), Rcpp::Named("mean.x") = *(samplevar_.get_x()),
        Rcpp::Named("mean.y") = *(samplevar_.get_y()),
        Rcpp::Named("squaredweigths") = *(samplevar_.get_squaredweights()),
        Rcpp::Named("empiricvariogram") = *(samplevar_.get_variogram()), Rcpp::Named("anchorpoints") = anchorpoints,
        Rcpp::Named("epsilon") = epsilon);
}

/**
 * \brief for each anchorpoints solves a problem of nonlinear optimization and returns the results
 * \param anchorpoints a matrix with the coordinates of each anchor point
 * \param empiricvariogram the empiric variogram returned by the previour function
 * \param squaredweights squared weigths returned by the previous function
 * \param mean_x mean.x returned by the previous function
 * \param mean_y mean.y returned by the previous function
 * \param variogram_id the variogram to be used
 * \param parameters the starting position to be given to the optimizer
 * \param lowerbounds the lower bounds for the optimizer
 * \param upperbounds the upper bounds for the optimizer
 * \param epsilon the value of epsilon regulating the kernel
 * \param lowerdelta set the minimum value for Cross-Validation search for optimal delta in smoothing equal to
 * lowerdelta*epsilon 
 * \param upperdelta set the maximum value for Cross-Validation search for optimal delta in smoothing
 * equal to upperdelta*epsilon 
 * \param print if set to true print on console the time required to process the output
 * \param n_threads the number of threads to be used by OPENMP. If negative, let OPENMP autonomously decide how many
 * threads to open
 */
//[[Rcpp::export]]
Rcpp::List findsolutionslsm(const Eigen::MatrixXd& anchorpoints, const Eigen::MatrixXd& empiricvariogram,
    const Eigen::MatrixXd& squaredweights, const Eigen::VectorXd& mean_x, const Eigen::VectorXd& mean_y,
    std::string& variogram_id, const std::string& kernel_id, const Eigen::VectorXd& parameters,
    const Eigen::VectorXd& lowerbound, const Eigen::VectorXd& upperbound, const double& epsilon,
    const double& lowerdelta, const double& upperdelta, const bool print, const int& n_threads)
{
    // start the clock
    auto start = high_resolution_clock::now();
    // if n_threads is positive open open n_threads threads to process the data
    // otherwise let openmp decide autonomously how many threads use
    // if n_threads is greater than the maximum number of threads available open all the threads accessible
    if (n_threads > 0) {
        int max_threads = omp_get_max_threads();
        int used_threads = std::min(max_threads, n_threads);
        Rcpp::Rcout << "desired: " << n_threads << std::endl;
        Rcpp::Rcout << "max: " << max_threads << std::endl;
        Rcpp::Rcout << "used: " << used_threads << std::endl;
        omp_set_num_threads(used_threads);
    }

    matrixptr empiricvariogramptr = std::make_shared<matrix>(empiricvariogram);
    matrixptr squaredweightsptr = std::make_shared<matrix>(squaredweights);
    vectorptr xptr = std::make_shared<vector>(mean_x);
    vectorptr yptr = std::make_shared<vector>(mean_y);
    matrixptr anchorpointsptr = std::make_shared<matrix>(anchorpoints);

    Opt opt_(empiricvariogramptr, squaredweightsptr, xptr, yptr, variogram_id, parameters, lowerbound, upperbound);
    // solve the nonlinaear optimization problems and store the solutions inside opt_
    opt_.findallsolutions();
    // build the smoother and find delta by cross-validation
    Smt smt_(opt_.get_solutions(), anchorpointsptr, lowerdelta * epsilon, upperdelta * epsilon, kernel_id);

    double delta_ottimale = smt_.get_optimal_delta();
    // stop the clock and calculate the processing time
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    if (print)
        Rcpp::Rcout << "task successfully completed in " << duration.count() << "ms" << std::endl;

    return Rcpp::List::create(Rcpp::Named("solutions") = *(opt_.get_solutions()), Rcpp::Named("delta") = delta_ottimale,
        Rcpp::Named("epsilon") = epsilon, Rcpp::Named("anchorpoints") = anchorpoints);
}

/**
 * \brief predict the mean value and the punctual value of Z
 * \param z a vector with the values of Z for each point in the dataset data
 * \param data a matrix with the coordinates of the points in the original dataset
 * \param anchorpoints a matrix with the coordinates of each anchor point
 * \param epsilon bandwidth parameter epsilon regulating the kernel
 * \param delta delta regulating the smoothing
 * \param solutions the solution of the nonlinear optimization problem returned by the previous function
 * \param positions the position in which to perform the kriging
 * \param variogram_id the variogram to be used
 * \param kernel_id the kernel to be used inside the smoother
 * \param print if set to true print on console the time required to process the output
 * \param n_threads the number of threads to be used by OPENMP. If negative, let OPENMP autonomously decide how many
 * threads to open
 */
// [[Rcpp::export]]
Rcpp::List predikt(const Eigen::VectorXd& z, const Eigen::MatrixXd& data, const Eigen::MatrixXd& anchorpoints,
    const double& epsilon, const double& delta, const Eigen::MatrixXd& solutions, const Eigen::MatrixXd& positions,
    const std::string& variogram_id, const std::string& kernel_id, const bool print, const int& n_threads)
{
    // start the clock
    auto start = high_resolution_clock::now();
    // if n_threads is positive open open n_threads threads to process the data
    // otherwise let openmp decide autonomously how many threads use
    // if n_threads is greater than the maximum number of threads available open all the threads accessible
    if (n_threads > 0) {
        int max_threads = omp_get_max_threads();
        int used_threads = std::min(max_threads, n_threads);
        Rcpp::Rcout << "desired: " << n_threads << std::endl;
        Rcpp::Rcout << "max: " << max_threads << std::endl;
        Rcpp::Rcout << "used: " << used_threads << std::endl;
        omp_set_num_threads(used_threads);
    }

    matrixptr dd = std::make_shared<matrix>(data);
    vectorptr zz = std::make_shared<vector>(z);
    matrixptr solutionsptr = std::make_shared<matrix>(solutions);
    matrixptr anchorpointsptr = std::make_shared<matrix>(anchorpoints);

    Smt smt_(solutionsptr, anchorpointsptr, delta, kernel_id);
    Predictor predictor_(variogram_id, zz, smt_, epsilon, dd);
    // predict the mean, the variance and the pointwise prediction of z in positions
    matrix predicted_ys(predictor_.predict_z<cd::matrix, cd::matrix>(positions));
    vector predicted_means(predictor_.predict_mean<cd::matrix, cd::vector>(positions));
    // stop the clock and calculate the processing time
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    if (print)
        Rcpp::Rcout << predicted_ys.rows() << " pairs of values predicted in " << duration.count() << "ms" << std::endl;

    return Rcpp::List::create(Rcpp::Named("zpredicted") = predicted_ys.col(0),
        Rcpp::Named("predictedmean") = predicted_means, Rcpp::Named("krigingvariance") = predicted_ys.col(1));
}

/**
 * \brief find the value of the parameters regulating the variogram
 * \param solutions the solution of the nonlinear optimization problem returned by the previous function
 * \param anchorpoints the coordinates of the anchorpoints in which the optimization problem has been solved
 * \param delta the value of delta regulating the smoothing
 * \param positions where to smooth the parameters
 * \param kernel_id the kernel to be used inside the smoother
 * \param n_threads the number of threads to be used by OPENMP. If negative, let OPENMP autonomously decide how many
 * threads to open
 */
// [[Rcpp::export]]
Rcpp::List smoothing(const Eigen::MatrixXd solutions, const Eigen::MatrixXd& anchorpoints, const double& delta,
    const Eigen::MatrixXd& positions, const std::string& kernel_id, const int& n_threads)
{
    // if n_threads is positive open open n_threads threads to process the data
    // otherwise let openmp decide autonomously how many threads use
    // if n_threads is greater than the maximum number of threads available open all the threads accessible
    if (n_threads > 0) {
        int max_threads = omp_get_max_threads();
        int used_threads = std::min(max_threads, n_threads);
        Rcpp::Rcout << "desired: " << n_threads << std::endl;
        Rcpp::Rcout << "max: " << max_threads << std::endl;
        Rcpp::Rcout << "used: " << used_threads << std::endl;
        omp_set_num_threads(used_threads);
    }

    matrixptr solutionsptr = std::make_shared<matrix>(solutions);
    matrixptr anchorpointsptr = std::make_shared<matrix>(anchorpoints);

    Smt smt_(solutionsptr, anchorpointsptr, delta, kernel_id);

    Eigen::MatrixXd result(positions.rows(), solutions.cols());
    #pragma omp parallel for
    for (size_t i = 0; i < positions.rows(); ++i) {
        result.row(i) = smt_.smooth_vector(positions.row(i));
    }

    return Rcpp::List::create(Rcpp::Named("parameters") = result);
}
