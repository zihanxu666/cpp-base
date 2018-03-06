#include <iostream>
#include <random>
#include <cmath>

//call option payoff
double payoff(double spot, double strike)
{
    return spot > strike ? (spot - strike) : 0;
}
//simulate spot price using classical BS model
double spotPrice(double maturity)
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
    mean = calculateMean(data,n);
    
    for (int i = 0; i < n; i++)
        variance += pow(data[i] - mean, 2);
    
    return variance / n;
}

double calculateSD(double *data, int n)
{
    return sqrt(calculateVariance(data,n) *n/ (n - 1));
}
double *confidenceInterval(double mean, double SD)
{
    double *result = new double[2];
    result[0] = mean - 1.96 * SD;
    result[1] = mean + 1.96 * SD;
    return result;
}

double getb(double *spotPrice, double *payoff,double meanSpot, double meanPayoff, int n)
{
    double numerator=0;
    double denominator = 0;
    
    for (int i=0; i<n; i++){
        numerator+=(spotPrice[i]-meanSpot)*(payoff[i]-meanPayoff);
        denominator+=pow((spotPrice[i]-meanSpot),2);
    }
    return numerator/denominator;
}

double *getYb(double *spotPrice, double *Y, double b, int n)
{
    double r = 0.05, T = 0.25, s_0 = 50;
    double *Yb = new double[n];
    for (int i = 0; i < n; i++)
    {
        Yb[i] = Y[i] - b * (spotPrice[i] - std::exp(r * T) * s_0);
    }
    return Yb;
}

double normalCDF(double x)
{
    return std::erfc(-x / std::sqrt(2)) / 2;
}

double expectationPayoff(double t, double S)
{
    
    double d1 = (std::log(S / 55) + (0.05 + pow(0.3, 2) / 2) * (0.25 - t)) / (0.3 * sqrt(0.25 - t));
    double d2 = d1-0.3*sqrt(0.25-t);
    return normalCDF(d1) * S * std::exp(0.05*0.25) - normalCDF(d2) * 55;
}

int main()
{
    double EY= expectationPayoff(0,50);
    double T = 0.25, strike = 55.0;
    int m=1000;//sample size
    double Y_bar[4][m];
    double Yb_bar[4][m];
    int N[4] = {10, 100, 1000, 10000};
    int count[]={0,0,0,0};
    double sb=0;
    
    for (int k = 0; k < m; k++)
    {
        for (int i = 0; i < 4; i++)
        {
            double *S_T = new double[N[i]];
            double *Y = new double[N[i]];
            double meanST=0, meanY=0;
            for (int j = 0; j < N[i]; j++)
            {
                S_T[j] = spotPrice(T);
                Y[j] = payoff(S_T[j], strike);
                meanST+= S_T[j]/N[i];
                meanY+=Y[j]/N[i];
                
            }
            double b=getb(S_T,Y,meanST,meanY,N[i]);
            double *Yb = getYb(S_T, Y, b, N[i]);
            Y_bar[i][k] = meanY;
            Yb_bar[i][k] = calculateMean(Yb, N[i]);
            sb=calculateSD(Yb,N[i]);
            double *interval=confidenceInterval(Yb_bar[i][k],sb/sqrt(N[i]));
            if(EY>interval[0]&&EY<interval[1]){
                count[i]+=1;
            }
            delete[] S_T;
            delete[] Y;
            delete Yb;
            delete interval;
        }
        if (k % (m/10) == 0)
        {
            std::cout << k << std::endl;
        }
    }
    double variance[4][2];
    double rho[4];
    std::cout << "print result..." << std::endl;
    std::cout<<"EY="<<EY<<std::endl;
    for (int i = 0; i < 4; i++)
    {
        variance[i][0] = calculateVariance(Y_bar[i], m);
        variance[i][1] = calculateVariance(Yb_bar[i], m);
        rho[i] = 1 - variance[i][1] / variance[i][0];
        std::cout << "When n = [ " << N[i] << " ]. The variance of Y is " << variance[i][0] << " , the variance of Y(b) is " << variance[i][1] << ", and rho is " << rho[i] << std::endl;
        std::cout<<"The probability that EY lies in the 95% confidence interval is "<<count[i]/(m+0.0)<<std::endl;
    }
    return 0;
}
