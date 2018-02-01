#include "hw.hpp"

class HW23:public HW
{
  public:
  private:
  public:
    int service();
    double normalCDF(double x);
    double Delta(double t, double S);
    double callPrice(double t, double S);
    double HedgePayoff(const std::vector<double> &path);
    double calculateSD(double *data, int n);
    void calculate(double *error, double *stockPrice, double *hedgePayoff, int numStep);
    void writeResultToFile(double *stockPrice, double *hedgePayoff, int numStep);
};