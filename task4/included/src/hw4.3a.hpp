#include "hw.hpp"

class HW43a : public HW
{
  public:
  private:
  public:
    double payoff(double spot, double strike);
    double spotPrice(double maturity);
    double calculateMean(double *data, int n);
    double calculateVariance(double *data, int n);
    double calculateCovariance(double *data1, double *data2, int n);
    double getb(double *spotPrice, double *payoff, int n);
    double *getYb(double *spotPrice, double *Y, int n);
    int service();
};