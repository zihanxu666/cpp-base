#include "hw.hpp"

class HW43b : public HW
{
  public:
  private:
  public:
    double payoff(double spot, double strike);
    double spotPrice(double maturity);
    double calculateMean(double *data, int n);
    double calculateVariance(double *data, int n);
    double calculateCovariance(double *data1, double *data2, int n);
    double calculateSD(double *data, int n);
    double *confidenceInterval(double mean, double SD, int n);
    double getb(double *spotPrice, double *payoff, int n);
    double *getYb(double *spotPrice, double *Y, int n);
    double normalCDF(double x);
    double expectationPayoff(double t, double S);
    int service();
};