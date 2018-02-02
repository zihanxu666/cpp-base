#include "../included/src/hw2.3.hpp"
#include "../included/src/simpath.h"

//calculate CDF of normal distribution
double HW23::normalCDF(double x)
{
    return std::erfc(-x / std::sqrt(2)) / 2;
}
//part(a) delta function
double HW23::Delta(double t, double S)
{
    double d1 = (std::log(S / 32) + (0 + pow(0.3, 2) / 2) * (0.5 - t)) / (0.3 * sqrt(0.5 - t));
    return normalCDF(d1);
}

//call option price
double HW23::callPrice(double t, double S)
{
    double d2 = (std::log(S / 32) + (0 - pow(0.3, 2) / 2) * (0.5 - t)) / (0.3 * sqrt(0.5 - t));
    return Delta(t, S) * S - normalCDF(d2) * 32;
}

//part(b) hedge payoff function
double HW23::HedgePayoff(const std::vector<double> &path)
{
    double t = 0;
    double M = path.size() - 1;
    double portfolioValue = callPrice(0, 30); //initial value is C(0,S(0))

    for (int k = 0; k < M; k++)
    {
        t = k * 0.5 / M;
        portfolioValue = portfolioValue + Delta(t, std::exp(path[k])) * (std::exp(path[k + 1]) - std::exp(path[k]));
    }
    return portfolioValue; //terminal portfolio value
}

//standard deviation
double HW23::calculateSD(double *data, int n)
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

void HW23::calculate(double *error, double *stockPrice, double *hedgePayoff, int numStep)
{
    for (int i = 0; i < 2000; i++)
    { //N = 2000
        std::vector<double> path = SimulatePath(0.5, numStep);

        double optionPayoff;

        optionPayoff = std::exp(path[numStep]) - 32 > 0 ? std::exp(path[numStep]) - 32 : 0; //option payoff=max(S-K,0)

        error[i] = optionPayoff - HedgePayoff(path);
        stockPrice[i] = std::exp(path[numStep]);
        hedgePayoff[i] = HedgePayoff(path);
    }
}

void HW23::writeResultToFile(double *stockPrice, double *hedgePayoff, int numStep)
{
    std::ofstream output;
    std::string fileName = "numstep";
    fileName.append("_").append(std::to_string(numStep)).append(".csv");
    output.open(fileName);
    for (int i = 0; i < 2000; i++)
    {
        output << stockPrice[i] << "," << hedgePayoff[i] << "\n";
    }
    output.close();
}

int HW23::service()
{

    double result[4][3][2000];

    int numStepArray[4] = {5, 10, 20,100};

    for (int i = 0; i < 4; i++)
    {
        calculate(result[i][0], result[i][1], result[i][2], numStepArray[i]);
    }

    for (int i = 0; i < 4; i++)
    {
        writeResultToFile(result[i][1], result[i][2], numStepArray[i]);
        std::cout << "When numstep=" << numStepArray[i] << ", the SD of errors: " << calculateSD(result[i][0], 2000) << std::endl;
    }
    
    // output price
    std::cout << "Option price under BSM model:" << callPrice(0, 30) << std::endl;
    return 0;
}
