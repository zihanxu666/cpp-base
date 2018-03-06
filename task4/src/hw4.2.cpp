#include <iostream>
#include "../included/src/Eigen/Eigen"
#include "../included/src/MVNormal.hpp"
#include <fstream>
#include "../included/src/hw4.2.hpp"

Eigen::VectorXd HW42::getOmega(Eigen::MatrixXd mu, Eigen::MatrixXd Sigma)
{
    //omega estimation

    Eigen::MatrixXd oneVector(3, 1);
    oneVector.setOnes(3, 1);
    double lambda = 1.5;
    double a = (oneVector.transpose() * Sigma.inverse() * oneVector)(0);
    double b = (oneVector.transpose() * Sigma.inverse() * mu)(0);

    Eigen::VectorXd omega = (Sigma.inverse() * oneVector) / a + (a * Sigma.inverse() * mu - b * Sigma.inverse() * oneVector) / (a * lambda);
    return omega;
}

double HW42::calculateVariance(Eigen::MatrixXd portfolioReturn, int n)
{
    Eigen::MatrixXd oneVector(n, 1);
    oneVector.setOnes(n, 1);

    return ((portfolioReturn - portfolioReturn.mean() * oneVector.transpose()) * (portfolioReturn.transpose() - portfolioReturn.mean() * oneVector))(0) / n;
}
int HW42::service()
{

    //Problem 2
    //part(a)
    Eigen::VectorXd mu(3);
    Eigen::MatrixXd Sigma(3, 3);
    mu << 0.04, 0.025, 0.06;
    Sigma << 0.00640000, 0.00368695, 0.00360000, 0.00368695, 0.00590000, 0.00311086, 0.00360000, 0.00311086, 0.00810000;

    MVNormal monthlyReturn(mu, Sigma);

    Eigen::MatrixXd omega(3, 1);//true optimal weight
    omega.col(0) = getOmega(mu, Sigma); 
    double trueMean=(omega.transpose()*mu)(0);
    double trueVariance=(omega.transpose()*Sigma*omega)(0);
    //repeat 500 times
    Eigen::MatrixXd omegaHat(3, 500); 
    Eigen::MatrixXd meanVariance(4, 500);
    for (int j = 0; j < 500; j++)
    {
        //generate 84 random normally distributed returns
        Eigen::MatrixXd Return(3, 84);

        for (int i = 0; i < 84; i++)
        {

            std::random_device rd;
            monthlyReturn.seed(rd());

            Return.col(i) = monthlyReturn();
        }

        Eigen::MatrixXd returnPast = Return.block(0, 0, 3, 60);//60 monthly return

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
        omegaHat.col(j) = getOmega(mu_hat, Sigma_hat);

        //part(b)
        Eigen::MatrixXd returnFuture = Return.block(0, 60, 3, 24);//24 monthly return

        Eigen::MatrixXd portfolioReturn(500, 24); //portfolio returns
        portfolioReturn.row(j) = omegaHat.col(j).transpose() * returnFuture;

        //sample mean and sample variance
        meanVariance(0, j) = portfolioReturn.row(j).mean();
        meanVariance(1, j) = calculateVariance(portfolioReturn.row(j), 24);

        Eigen::MatrixXd portfolioTheoretical(500, 24);
        portfolioTheoretical.row(j) = omega.transpose() * returnFuture; //returns of the theoretical optimal portfolio

        meanVariance(2, j) = portfolioTheoretical.row(j).mean();
        meanVariance(3, j) = calculateVariance(portfolioTheoretical.row(j), 24);
    }
    
    std::cout <<"Theoretical optimal portfolio is:"<<std::endl;
    std::cout << omega<<std::endl;
    std::cout << "True mean: "<<trueMean<<", true variance: "<<trueVariance<<std::endl;
    //output data
    std::ofstream myfile;
    myfile.open("output1.csv");
    myfile << omegaHat.transpose();
    myfile.close();

    //output data
    std::ofstream output;
    output.open("output2.csv");
    output << meanVariance.transpose();
    output.close();

    return 0;
}

int main()
{
    HW42 obj;
    obj.service();
}
