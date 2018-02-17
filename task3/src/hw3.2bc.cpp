#include "../included/src/hw3.2.hpp"

HW32::HW32(Generator * generator)
{
    _generator=generator;
}

double HW32::generator()
{
    return _generator->generator();
}
double HW32::expGenerator(double lambda)
{
    return -std::log(generator()) / lambda; //Y=-ln(U)/lambda to generate exp(lambda)
}
double HW32::expVariable()
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
double HW32::normalGenerator()
{
    double Z;
    double U = generator();
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
double HW32::calculateMean(double *data, int n)
{
    double sum = 0.0;

    int i;

    for (i = 0; i < n; i++)
    {
        sum += data[i];
    }

    return sum / n;
}
double HW32::calculateSD(double *data, double mean, int n)
{
    double standardDeviation = 0.0;

    int i;

    for (i = 0; i < n; i++)
        standardDeviation += pow(data[i] - mean, 2);

    return sqrt(standardDeviation / n);
}
double * HW32::confidenceInterval(double mean, double SD)
{
    double *result=new double[2];
    result[0] = mean - 1.96 * SD;
    result[1] = mean + 1.96 * SD;
    return result;
}

int HW32::service()
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