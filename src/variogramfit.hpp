#ifndef GRADIENT
#define GRADIENT

#include "traits.hpp"
#include "LBFGSB.h"
#include <vector>

/**
 * \brief a very simple "helper" function to calculate the value of the parameter "h" needed in different functions
*/
cd::scalar compute_anisotropic_h(const cd::scalar &lambda1, const cd::scalar &lambda2, const cd::scalar &phi, const cd::scalar &x, const cd::scalar &y);


/**
 * \return sigma*sigma*(1-e^-h)
*/
cd::scalar exponential(const cd::vector &params, const cd::scalar &x, const cd::scalar &y);


/**
 * \brief allows to select between different functions for the variogram
 * \param id    the name of your favourite variogram
*/
cd::variogramfunction make_variogramiso(const std::string &id);



/**
 * \brief functor to pass to the optimizer
*/
struct funzionedaottimizzare
{
    const cd::matrixptr empiricvariogram;
    const cd::matrixptr squaredweights;
    const cd::vectorptr x;
    const cd::vectorptr y;
    unsigned int x0;
    cd::variogramfunction gammaiso;

    /**
     * \brief constructor
     * \param empiricvariogram_     a shared pointer to the empiric variogram
     * \param squaredweights_       a shared pointer to the squared weights
     * \param x_                    a shared pointer to the vector of the abscissas of the centers
     * \param y_                    a shared pointer to the vector of the ordinates of the centers
     * \param x0_                   the index of the position x0
     * \param id                    the name of the variogram of your choice
    */
    funzionedaottimizzare(const cd::matrixptr empiricvariogram_, const cd::matrixptr squaredweights_, const cd::vectorptr x_, const cd::vectorptr y_, unsigned int x0_, 
    const std::string &id);

    /**
     * \param params    a vector containing the previous value of the parameters of the function (lambda1, lambda2, phi, sigma, etc.)
     * \param grad      a vector containing the previous value of the gradient which will be updated
    */
    cd::scalar operator() (const cd::vector &params, cd::vector &grad);
    cd::scalar operator() (const cd::vector &params);
};



/**
 * \brief a class to find the real value of the parameters of the variogram in each point by optimizing the correspondent funzionedaottimizzare relying on the library LBFGSpp
*/
class opt
{
private:
    cd::matrixptr empiricvariogram;
    cd::matrixptr squaredweights;
    cd::vectorptr x;
    cd::vectorptr y;
    std::string id;

    cd::matrixptr solutions = nullptr;

    /**
     * \brief find the optimal solution for the point in position pos
     * \param pos   the index of the position in which find the optimal solution
    */
    cd::vector findonesolution(const unsigned int pos) const;

public:
    /**
     * \brief constructor
     * \param empiricvariogram_     a shared pointer to the empiric variogram
     * \param squaredweights_       a shared pointer to the squared weights
     * \param x_                    a shared pointer to the vector of the abscissas of the centers
     * \param y_                    a shared pointer to the vector of the ordinates of the centers
     * \param id                    the name of the variogram of your choice
    */
    opt(const cd::matrixptr empiricvariogram_, const cd::matrixptr squaredweights_, const cd::vectorptr x_, const cd::vectorptr y_,
    const std::string &id_);

    /**
     * \brief find the optimal solution in different positions
     * \param pos   a vector containing the indeces of all the positions
    */
    void findsomesolutions(const cd::vectorind &pos);

    /**
     * \brief find the optimal solution in all the position
    */
    void findallsolutions();

    cd::matrixptr get_solutions() const;
};




#endif //GRADIENT