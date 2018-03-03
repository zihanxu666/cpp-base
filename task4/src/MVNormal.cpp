#include "../included/src/MVNormal.hpp"
#include <random>
#include <cassert>
#include <cmath>

//Problem 1
MVNormal::MVNormal(Eigen::VectorXd mu, Eigen::MatrixXd Sigma)
: mu(mu), Sigma(Sigma)
{
    //check the mean matrix and the covariance matrix have matched sizes
    assert(mu.size() == Sigma.rows());
    
    std::random_device rd;
    rng.seed(rd());  // set seed
    
    //check Sigma matrix is a squared matrix
    assert(Sigma.rows() == Sigma.cols());
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
