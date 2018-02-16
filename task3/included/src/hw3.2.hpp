#include "hw.hpp"
#include "baseGenerator.hpp"

class HW32 : public HW
{
  public:
  HW32(Generator * generator);
  private:
    Generator * _generator;
  public:
  double generator();
  double expGenerator(double lambda);
  double expVariable();
  double normalGenerator();
  double calculateMean(double *data, int n);
  double calculateSD(double *data, double mean, int n);
  double * confidenceInterval(double mean, double SD);
  int service();

};