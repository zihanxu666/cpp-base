#include <iostream>
#include <random>
#include <cmath>
#include <vector>
//call option payoff
double payoff(double spot, double strike)
{
    return spot > strike ? (spot - strike) : 0;
}

double spotPrice(double maturity)
{
    double s_0 = std::log(50.0), r = 0.05, sigma = 0.3;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::normal_distribution<double> norm(0.0, 1.0);

    double drift_log = r - 0.5 * sigma * sigma;
    double dt = maturity, sqrt_dt = std::sqrt(dt);
    double dW = sqrt_dt * norm(rng);
    double log_price = drift_log * dt + sigma * dW;

    return std::exp(log_price);
}
double *getSpotPrice(int n)
{
    double *S_T = new double[n];
    for (int i = 0; i < n; i++)
    {
        S_T[i] = spotPrice(0.25);
    }
    return S_T;
}
double calculateMean(double *data, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; i++)
    {
        sum += data[i];
    }

    return sum / n;
}
double calculateVariance(double *data, int n)
{
    double mean, variance = 0.0;

    mean = calculateMean(data, n);

    for (int i = 0; i < n; i++)
        variance += pow(data[i] - mean, 2);

    return variance / n;
}
double calculateCovariance(double *data1, double *data2, int n)
{
    double mean1, mean2, covariance = 0.0;

    mean1 = calculateMean(data1, n);
    mean2 = calculateMean(data2, n);

    for (int i = 0; i < n; i++)
        covariance += (data1[i] - mean1) * (data2[i] - mean2);

    return covariance / n;
}

double getb(double *spotPrice, double *payoff, int n)
{
    double b = calculateCovariance(spotPrice, payoff, n) / calculateVariance(spotPrice, n);
    return b;
}

double *getY(double *spotPrice, int n)
{
    double *Y = new double[n];
    for (int i = 0; i < n; i++)
    {
        Y[i] = payoff(spotPrice[i], 55);
    }
    return Y;
}

double *getYb(double *spotPrice, double *Y, int n)
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

int main()
{
    //set up model
    double maturity = 0.25;
    double strike = 55;

    
    double Y_bar[4][10000];
    double Yb_bar[4][10000];
    int N[4] = {10, 100, 1000, 10000};
    
    double b[4];
    for (int k = 0; k < 10000; k++)
    {
        for (int i = 0; i < 4; i++)
        { 
            double *S_T=getSpotPrice(N[i]);
            double *Y=getY(S_T,N[i]);
            b[i] = getb(S_T, Y, N[i]);
            double *Yb = getYb(S_T, Y, N[i]);
            Y_bar[i][k] = calculateMean(Y, N[i]);
            Yb_bar[i][k] = calculateMean(Yb, N[i]);
        }
    }
    double variance[4][2];
    double rho[4];
    for (int i=0;i<4;i++){
        variance[i][1]=calculateVariance(Y_bar[i],10000);
        variance[i][2]=calculateVariance(Yb_bar[i],10000);
        rho[i]=1-variance[i][2]/variance[i][1];
    }

    return 0;
}
