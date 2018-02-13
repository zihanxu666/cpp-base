#include <iostream>
#include <random>
#include <cmath>

double uniGenerator()
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_real_distribution<double> uni(0.0, 1.0);
    return uni(rng);
}
double expVariable()
{
    double Y1 = 0.0, Y2 = 0.0;
    while (Y2 <= pow((1 - Y1), 2) / 2)
    {
        Y1 = -std::log(uniGenerator()); //Y=-ln(U)/lambda~exp(lambda), lambda=1
        Y2 = -std::log(uniGenerator());
    }
    return Y1;
}
double normalDistribution()
{
    double Z = 0.0;
    if (uniGenerator() < 0.5)
    {
        Z = expVariable();
    }
    else if (uniGenerator() > 0.5)
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

    double upperBound = mean + 1.96 * SD;
    double lowerBound = mean - 1.96 * SD;
    double result[2] = {lowerBound, upperBound};
    return result;
}

int main()
{
    unsigned int time = 0;
    double St = 0;
    double tau[10000];
    for (int i = 0; i < 10000; i++)
    {
        while (-10 < St < 5)
        {
            St += normalDistribution();
            time++;
        }
        tau[i] = time;
    }
    double mean = calculateMean(tau, 10000);
    double SD = calculateSD(tau, 10000);
    double *interval = confidenceInterval(mean, SD);
    std::cout << "E(stopping time): " << mean << std::endl;
    std::cout << "Standard deviation of stopping time: " << SD << std::endl;
    std::cout << "The 95% confidence interval is [" << interval[0] << ", " << interval[1] << "]." << std::endl;
    return 0;
}