#include <iostream>
#include <random>
#include <cmath>

//call option payoff
double payoff(double spot)
{
    return spot > 55.0 ? (spot - 55.0) : 0;
}
//simulate spot price using classical BS model
double spotPrice()
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
double calculateVariance(double *data, int n, double mean)
{
    double variance = 0.0;
    for (int i = 0; i < n; i++)
        variance += pow(data[i] - mean, 2);
    
    return variance / n;
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

// double *getYb(double *spotPrice, double *Y, double b, int n)
// {
//     double r = 0.05, T = 0.25, s_0 = 50;
//     double *Yb = new double[n];
//     for (int i = 0; i < n; i++)
//     {
//         Yb[i] = Y[i] - b * (spotPrice[i] - std::exp(r * T) * s_0);
//     }
//     return Yb;
// }



int main()
{
    
    int m=1000;//sample size
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
            double meanST=0;
            for (int j = 0; j < N[i]; j++)
            {
                S_T[j] = spotPrice();
                Y[j] = payoff(S_T[j]);
                meanST+= S_T[j]/(N[i]+0.0);
                Y_bar[i][k]+=Y[j]/(N[i]+0.0);
                
            }
            double b=getb(S_T,Y,meanST,Y_bar[i][k],N[i]);
            
            double *Yb = new double[N[i]];
            for (int j = 0; j < N[i]; j++)
            {
               Yb[j] = Y[j] - b * (S_T[j] - std::exp(0.05 * 0.25) * 50);
               Yb_bar[i][k]+=Yb[j]/(0.0+N[i]);
            }
            
            
            delete[] S_T;
            delete[] Y;
            delete[] Yb;
            
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
