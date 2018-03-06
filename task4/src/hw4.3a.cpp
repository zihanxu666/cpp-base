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
double HW43a::spotPrice()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::normal_distribution<double> norm(0.0, 1.0);
  //  s_0 = 50.0, r = 0.05, sigma = 0.3;
  //  drift_log = r - 0.5 * sigma * sigma
  //  dt = 0.25
  //  dW = sqrt(dt) * norm(rng)
  //  log_price = log(s_0) + drift_log * dt + sigma * dW

    return 50.0*std::exp((0.05 - 0.5 * pow(0.3,2))*0.25 + 0.3*std::sqrt(0.25) * norm(rng));
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

    return variance / (n-1);
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

    return covariance / (n-1);
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
    double strike = 55.0;
    int m=10000;//sample size
    int n=4;
    double Y_bar[n][m];
    double Yb_bar[n][m];
    int N[n];
    for(int i=0;i<n;i++){
        N[i]=pow(10,i+1);
    }
    
    
    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < n; i++)
        {
            double *S_T = new double[N[i]];
            double *Y = new double[N[i]];
            for (int j = 0; j < N[i]; j++)
            {
                S_T[j] = spotPrice();
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
    double variance[n][2];
    double rho[n];
    std::cout << "print result..." << std::endl;
    for (int i = 0; i < n; i++)
    {
        variance[i][0] = calculateVariance(Y_bar[i], m);
        variance[i][1] = calculateVariance(Yb_bar[i], m);
        rho[i] = 1 - variance[i][1] / variance[i][0];
        std::cout << "When n = [ " << N[i] << " ]. The variance of Y is " << variance[i][0] << " , the variance of Y(b) is " << variance[i][1] << ", and rho is " << rho[i] << std::endl;
        
    }
    return 0;
}
