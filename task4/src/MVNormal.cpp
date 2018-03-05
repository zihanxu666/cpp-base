#include "../included/src/MVNormal.hpp"
#include <random>
#include <cassert>
#include <cmath>

//Problem 1
MVNormal::MVNormal(Eigen::VectorXd mu, Eigen::MatrixXd Sigma)
: mu(mu), Sigma(Sigma)
{
    //check if mu vector and sigma matrix have matched dimensions
    assert(mu.size() == Sigma.rows());
    //check if sigma matrix is a squared matrix
    assert(Sigma.rows() == Sigma.cols());
    //check if the sigma matrix is positive definite
    assert(decomp.info()!=Eigen::NumericalIssue);

    std::random_device rd;
    rng.seed(rd());  // set seed
    
    Eigen::LLT<Eigen::MatrixXd> decomp(Sigma);
    L = decomp.matrixL();
};

// Set the seed of the underlying random number generator
void MVNormal::seed(unsigned long my_seed)
{
    rng.seed(my_seed);
};

// Simulate a sample
Eigen::VectorXd MVNormal::operator()()
{
    int dim = mu.size();
    
    Eigen::VectorXd Z(dim);  // N(0, I)
    for (int i = 0; i < dim; ++i)
    {
        Z[i] = rnorm(rng);
    }
    
    Eigen::VectorXd X = mu + L*Z;  // N(mu_, Sigma_)
    
    return X;
};
