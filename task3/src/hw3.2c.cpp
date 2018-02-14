#include <iostream>
#include <random>
#include <cmath>



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
double calculateSD(double *data, double mean, int n)
{
    double standardDeviation = 0.0;

    int i;

    for (i = 0; i < n; i++)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / n);
}
double *confidenceInterval(double mean, double SD)
{
    double *result;
    result[0] = mean - 1.96 * SD;
    result[1] = mean + 1.96 * SD;
    return result;
}

int main()
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::normal_distribution<double> norm(0.0, 1.0);
    int t = 0;
    double St = 0;
    double tau[10000];
    for (int i = 0; i < 10000; i++)
    {
        while (St > -10 && St < 5)
        {
            St += norm(rng);
            t++;
        }
        tau[i] = t;
        t = 0;
        St = 0;
    }
    double mean = calculateMean(tau, 10000);
    double SD = calculateSD(tau, mean, 10000);
    double *interval = confidenceInterval(mean, SD);

    std::cout << "E[stopping time]: " << mean << std::endl;
    std::cout << "Standard deviation of stopping time: " << SD << std::endl;
    std::cout << "The 95% confidence interval is [" << interval[0] << ", " << interval[1] << "]." << std::endl;

    return 0;
}



