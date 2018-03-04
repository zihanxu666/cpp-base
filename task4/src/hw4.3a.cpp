#include <iostream>
#include <random>
#include <cmath>
#include "../included/src/hw4.3a.hpp"
//call option payoff
double HW43a::payoff(double spot, double strike)
{
    return spot > strike ? (spot - strike) : 0;
}
//simulate spot price using classical BS model
double HW43a::spotPrice(double maturity)
{
    double s_0 = std::log(50.0), r = 0.05, sigma = 0.3;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::normal_distribution<double> norm(0.0, 1.0);

    double drift_log = r - 0.5 * sigma * sigma;
    double dt = maturity, sqrt_dt = std::sqrt(dt);
    double dW = sqrt_dt * norm(rng);
    double log_price = s_0 + drift_log * dt + sigma * dW;

    return std::exp(log_price);
}

double HW43a::calculateMean(double *data, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; i++)
    {
        sum += data[i];
    }

    return sum / n;
}
double HW43a::calculateVariance(double *data, int n)
{
    double mean, variance = 0.0;
    mean = calculateMean(data,n);

    for (int i = 0; i < n; i++)
        variance += pow(data[i] - mean, 2);

    return variance / n;
}
double HW43a::calculateCovariance(double *data1, double *data2, int n)
{
    double mean1, mean2, covariance = 0.0;

    
    double sum1 = 0.0,sum2 = 0.0;

    for (int i = 0; i < n; i++)
    {
        sum1 += data1[i];
        sum2 += data2[i];
    }
    mean1 = sum1 / n;
    mean2 = sum2 / n;

    for (int i = 0; i < n; i++)
        covariance += (data1[i] - mean1) * (data2[i] - mean2);

    return covariance / n;
}


double HW43a::getb(double *spotPrice, double *payoff, int n)
{
    double b = calculateCovariance(spotPrice, payoff, n) / calculateVariance(spotPrice, n);
    return b;
}

double *HW43a::getYb(double *spotPrice, double *Y, int n)
{
    double r = 0.05, T = 0.25, s_0 = 50;
    double *Yb = new double[n];
    double b = getb(spotPrice, Y, n);
    for (int i = 0; i < n; i++)
    {
        Yb[i] = Y[i] - b * (spotPrice[i] - std::exp(r * T) * s_0);
    }
    return Yb;
}


int HW43a::service()
{
    double r = 0.05, T = 0.25, strike = 55.0;
    int m=10000;//sample size
    double Y_bar[4][m];
    double Yb_bar[4][m];
    int N[4] = {10, 100, 1000, 10000};
    
    
    
    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < 4; i++)
        {
            double *S_T = new double[N[i]];
            double *Y = new double[N[i]];
            for (int j = 0; j < N[i]; j++)
            {
                S_T[j] = spotPrice(T);
                Y[j] = payoff(S_T[j], strike);
            }

            double *Yb = getYb(S_T, Y, N[i]);
            
            Y_bar[i][k] = calculateMean(Y, N[i]);
            Yb_bar[i][k] = calculateMean(Yb, N[i]);
            
            delete S_T;
            delete Y;
            delete Yb;
        }
        if (k % (m/10) == 0)
        {
            std::cout << k << std::endl;
        }
    }
    double variance[4][2];
    double rho[4];
    std::cout << "print result..." << std::endl;
    for (int i = 0; i < 4; i++)
    {
        variance[i][0] = calculateVariance(Y_bar[i], m);
        variance[i][1] = calculateVariance(Yb_bar[i], m);
        rho[i] = 1 - variance[i][1] / variance[i][0];
        std::cout << "When n = [ " << N[i] << " ]. The variance of Y is " << variance[i][0] << " , the variance of Y(b) is " << variance[i][1] << ", and rho is " << rho[i] << std::endl;
        
    }
    return 0;
}
