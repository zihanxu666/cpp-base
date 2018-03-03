#ifndef MVNormal_hpp
#define MVNormal_hpp

#include <stdio.h>
#include "Eigen/Eigen"
#include <random>

class MVNormal  // lots of room for improvement
{
public:
    MVNormal(Eigen::VectorXd mu, Eigen::MatrixXd Sigma);
    void seed(unsigned long new_seed);
    Eigen::VectorXd operator()();
private:
    std::mt19937 rng;
    std::normal_distribution<double> rnorm;
    Eigen::VectorXd mu;
    Eigen::MatrixXd Sigma;
    Eigen::MatrixXd L;  // L in Sigma = LL^T
};

#endif /* MVNormal_hpp */
