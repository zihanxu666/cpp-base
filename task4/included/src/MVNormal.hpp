//  MVNormal.hpp
//  Problem1
//  HW 4
//  Created by Yu Dai on 2/19/18.


#ifndef MVNormal_hpp
#define MVNormal_hpp

#include <stdio.h>
#include <Eigen/Dense>
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
