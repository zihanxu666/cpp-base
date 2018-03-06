#include "../included/src/hw4.3b.hpp"
//call option payoff
double HW43b::payoff(double spot, double strike)
{
    return spot > strike ? (spot - strike) : 0;
}
//simulate spot price using classical BS model
double HW43b::spotPrice()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::normal_distribution<double> norm(0.0, 1.0);
  //  s_0 = 50.0, r = 0.05, sigma = 0.3;
  //  drift_log = r - 0.5 * sigma * sigma
  //  dt = 0.25
  //  dW = std::sqrt(dt) * norm(rng)
  //  log_price = s_0 + drift_log * dt + sigma * dW

    return 50.0*std::exp((0.05 - 0.5 * pow(0.3,2))*0.25 + 0.3*std::sqrt(0.25) * norm(rng));
}

double HW43b::calculateMean(double *data, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; i++)
    {
        sum += data[i];
    }

    return sum / n;
}
double HW43b::calculateVariance(double *data, int n)
{
    double mean, variance = 0.0;
    mean = calculateMean(data, n);

    for (int i = 0; i < n; i++)
        variance += pow(data[i] - mean, 2);

    return variance / (n - 1);
}
double HW43b::calculateCovariance(double *data1, double *data2, int n)
{
    double mean1, mean2, covariance = 0.0;

    double sum1 = 0.0, sum2 = 0.0;

    for (int i = 0; i < n; i++)
    {
        sum1 += data1[i];
        sum2 += data2[i];
    }
    mean1 = sum1 / n;
    mean2 = sum2 / n;

    for (int i = 0; i < n; i++)
        covariance += (data1[i] - mean1) * (data2[i] - mean2);

    return covariance / (n - 1);
}
double HW43b::calculateSD(double *data, int n)
{
    return sqrt(calculateVariance(data, n));
}
double *HW43b::confidenceInterval(double mean, double SD, int n)
{
    double *result = new double[2];
    if (n < 100)
    { //n=10,df=9,t_9=2.262
        result[0] = mean - 2.262 * SD;
        result[1] = mean + 2.262 * SD;
    }
    else if (n < 1000)
    { //n=100,t=1.984
        result[0] = mean - 1.984 * SD;
        result[1] = mean + 1.984 * SD;
    }
    else
    { //z=1.96
        result[0] = mean - 1.96 * SD;
        result[1] = mean + 1.96 * SD;
    }
    return result;
}
double HW43b::getb(double *spotPrice, double *payoff, int n)
{
    double b = calculateCovariance(spotPrice, payoff, n) / calculateVariance(spotPrice, n);
    return b;
}

double *HW43b::getYb(double *spotPrice, double *Y, int n)
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

double HW43b::normalCDF(double x)
{
    return std::erfc(-x / std::sqrt(2)) / 2;
}

double HW43b::expectationPayoff(double t, double S)
{

    double d1 = (std::log(S / 55) + (0.05 + pow(0.3, 2) / 2) * (0.25 - t)) / (0.3 * sqrt(0.25 - t));
    double d2 = d1 - 0.3 * sqrt(0.25 - t);
    return normalCDF(d1) * S * std::exp(0.05 * 0.25) - normalCDF(d2) * 55;
}

int HW43b::service()
{
    double EY = expectationPayoff(0, 50);
    double strike = 55.0;
    int m = 1000000; //sample size
    int n = 5;
    double Y_bar[n][m];
    double Yb_bar[n][m];
    int N[n];
    int count[n];
    for(int i=0;i<n;i++){
        N[i]=pow(10,i+1);
        count[i]=0;
    }

    double sb = 0;

    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < n; i++)
        {
            double * S_T = new double[N[i]];
            double * Y = new double[N[i]];
            for (int j = 0; j < N[i]; j++)
            {
                S_T[j] = spotPrice();
                Y[j] = payoff(S_T[j], strike);
            }

            double *Yb = getYb(S_T, Y, N[i]);
            Y_bar[i][k] = calculateMean(Y, N[i]);
            Yb_bar[i][k] = calculateMean(Yb, N[i]);
            sb = calculateSD(Yb, N[i]);
            double *interval = confidenceInterval(Yb_bar[i][k], sb / sqrt(N[i]), N[i]);
            if (EY > interval[0] && EY < interval[1])
            {
                count[i] += 1;
            }
            delete S_T;
            delete Y;
            delete Yb;
            delete interval;
        }
        if (k % (m / 10) == 0)
        {
            std::cout << k << std::endl;
        }
    }
    // double variance[n][2];
    // double rho[n];
    std::cout << "print result..." << std::endl;
    std::cout << "EY=" << EY << std::endl;
    for (int i = 0; i < n; i++)
    {
        // variance[i][0] = calculateVariance(Y_bar[i], m);
        // variance[i][1] = calculateVariance(Yb_bar[i], m);
        
        std::cout << "When n = [ " << N[i] << " ], the probability that EY lies in the 95% confidence interval is " << count[i] / (m + 0.0) << std::endl;
    }
    return 0;
}
