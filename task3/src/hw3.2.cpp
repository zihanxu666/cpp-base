#include <iostream>
#include <random>
#include <cmath>


double uniGenerator()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> uni(0.0, 1.0);
    return uni(rng);
}
double expGenerator(double lambda)
{
    return -std::log(uniGenerator()) / lambda; //Y=-ln(U)/lambda~exp(lambda)
}
double expVariable()
{
    double
        Y1 = expGenerator(1),
        Y2 = expGenerator(1);

    if (Y2 > pow((1 - Y1), 2) / 2)
    {
        return Y1;
    }

    expVariable();
}
double normalGenerator()
{
    double Z = 0.0;
    double U = uniGenerator();
    if (U < 0.5)
    {
        Z = expVariable();
    }
    else if (U > 0.5)
    {
        Z = -expVariable();
    }
    return Z;
}
double calculateMean(double *data, int n)
{
    double sum = 0.0;

    int i;

    for (i = 0; i < n; i++)
    {
        sum += data[i];
    }

    return sum / n;
}
double calculateSD(double *data, int n)
{
    double sum = 0.0, mean, standardDeviation = 0.0;

    int i;

    for (i = 0; i < n; i++)
    {
        sum += data[i];
    }

    mean = sum / n;

    for (i = 0; i < n; i++)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / n);
}
double *confidenceInterval(double mean, double SD)
{
    double *result;
    double upperBound = mean + 1.96 * SD;
    double lowerBound = mean - 1.96 * SD;
    result[0]=lowerBound;
    result[1]=upperBound;
    return result;
}

int main()
{
    int t= 0;
    double St = 0;
    double tau[10000];
    for (int i = 0; i < 10000; i++)
    {  
        while (St > -10 && St < 5)
        {
            St += normalGenerator();
            t++;
            
        }
        tau[i] = t;
        t=0;
        St=0;
    }
    double mean = calculateMean(tau, 10000);
    double SD = calculateSD(tau, 10000);
    double *interval = confidenceInterval(mean, SD);

    std::cout << "E[stopping time]: " << mean << std::endl;
    std::cout << "Standard deviation of stopping time: " << SD << std::endl;
    std::cout << "The 95% confidence interval is [" << interval[0] << ", " << interval[1] << "]." << std::endl;

    
    

    return 0;
}