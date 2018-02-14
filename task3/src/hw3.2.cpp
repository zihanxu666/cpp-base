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
double expGenerator(double lambda)
{
    return -std::log(uniGenerator()) / lambda; //Y=-ln(U)/lambda to generate exp(lambda)
}
double expVariable()
{

    double
        Y1 = expGenerator(1),
        Y2 = expGenerator(1);

    if (Y2 > pow((1 - Y1), 2) / 2)
    {
        return Y1; //base case
    }
    else
    {
        return expVariable(); //recur
    }
}
//Part(b)
double normalGenerator()
{
    double Z;
    double U = uniGenerator();
    double Y = expVariable();
    if (U < 0.5)
    {
        Z = Y;
    }
    else if (U > 0.5)
    {
        Z = -Y;
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
    //Part(c)
    int t = 0;
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