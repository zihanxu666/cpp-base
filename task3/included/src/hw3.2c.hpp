#include "hw.hpp"

class HW32c : public HW
{
  public:
  private:
  public:
    double calculateMean(double *data, int n);
    double calculateSD(double *data, double mean, int n);
    double *confidenceInterval(double mean, double SD);
    int service();
};