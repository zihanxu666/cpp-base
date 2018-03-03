#include <iostream>
#include "../included/src/Eigen/Eigen"
#include "../included/src/MVNormal.hpp"
#include <fstream>

Eigen::VectorXd getOmega(Eigen::MatrixXd mu, Eigen::MatrixXd Sigma)
{
    //omega estimation

    Eigen::MatrixXd oneVector(3,1);
    oneVector.setOnes(3,1);
    double lambda = 1.5;

    
    double sigmaFactor = (oneVector.transpose() * Sigma.inverse() * oneVector)(0);

    
    double muFactor = (oneVector.transpose() * Sigma.inverse() * mu)(0);

    
    Eigen::VectorXd omega = (Sigma.inverse() * oneVector) / sigmaFactor + (sigmaFactor * Sigma.inverse() * mu - muFactor * Sigma.inverse() * oneVector) / (sigmaFactor * lambda);
    return omega;
}

double calculateVariance(Eigen::MatrixXd portfolioReturn, int n)
{
    Eigen::MatrixXd oneVector(n,1);
    oneVector.setOnes(n,1);

    return ((portfolioReturn - portfolioReturn.mean() * oneVector.transpose()) * (portfolioReturn.transpose() - portfolioReturn.mean() * oneVector))(0)/n;
}
int main()
{

    //Problem 2

    //part(a)
    Eigen::VectorXd mu(3);
    Eigen::MatrixXd Sigma(3, 3);
    mu << 0.04, 0.025, 0.06;
    Sigma << 0.00640000, 0.00368695, 0.00360000, 0.00368695, 0.00590000, 0.00311086, 0.00360000, 0.00311086, 0.00810000;

    MVNormal monthlyReturn(mu, Sigma);

    Eigen::MatrixXd omega.col(0) = getOmega(mu, Sigma); //true optimal weight
    //repeat 500 times
    Eigen::MatrixXd omega500(3, 500); //
    Eigen::MatrixXd meanVariance(4, 500);
    for (int j = 0; j < 500; j++)
    {
        //generate 60 random normally distributed returns
        Eigen::MatrixXd Return(3, 84);

        for (int i = 0; i < 84; i++)
        {

            std::random_device rd;
            monthlyReturn.seed(rd());

            Return.col(i) = monthlyReturn();
        }

        Eigen::MatrixXd returnPast = Return.block(0, 0, 3, 60);

        //mu estimation
        Eigen::VectorXd mu_hat(3);
        for (int i = 0; i < 3; i++)
        {
            mu_hat(i) = returnPast.row(i).mean();
        }
        //sigma estimation
        Eigen::MatrixXd Sigma_hat(3, 3);
        Eigen::MatrixXd centered = returnPast.colwise() - returnPast.rowwise().mean();
        Sigma_hat = (centered * (centered.transpose())) / (double(returnPast.cols()) - 1);
        //part(a)
        omega500.col(j) = getOmega(mu_hat, Sigma_hat);

        //part(b)
        Eigen::MatrixXd returnFuture = Return.block(0, 60, 3, 24);

        Eigen::MatrixXd portfolioReturn(500, 24); //portfolio returns
        portfolioReturn.row(j) = omega500.col(j).transpose() * returnFuture;
        
        //sample mean and sample variance
        meanVariance(0,j)=portfolioReturn.row(j).mean();
        meanVariance(1,j)= calculateVariance(portfolioReturn.row(j), 24);
        

        Eigen::MatrixXd portfolioTheoretical(500, 24);
        portfolioTheoretical.row(j) = omega.transpose() * returnFuture; //returns of the theoretical optimal portfolio
        
        meanVariance(2,j)= portfolioTheoretical.row(j).mean();
        meanVariance(3,j) = calculateVariance(portfolioTheoretical.row(j), 24);
    }
    std::cout<<omega;
    //output data
    std::ofstream myfile;
    myfile.open("output1.csv");

        myfile << omega500;

    myfile.close();

    //output data
    std::ofstream output;
    output.open("output2.csv");

    output<<meanVariance;

    output.close();

    return 0;
}
