#include "hw.hpp"

class HW43b : public HW
{
public:
  std::vector<int> task_count;

  std::mutex mt;
  int CLOCKS_PER_SEC_SIMPLE = 10000000;
  struct value
  {
    double S_T;
    double Y;
  };

  struct value_set
  {
    std::vector<value> values;
    double S_T_Mean;
    double Y_Mean;
  };

  struct a_final_result
  {
    double *Yb;
    double Yb_mean;
    double Y_mean;
  };

  struct final_result
  {
    double Y_variance;
    double Yb_variance;
    double rho;
  };
  std::vector<a_final_result> result_set;
  std::vector<final_result> set;

private:
public:
  double payoff(double spot, double strike);
  double spotPrice();
  double calculateMean(double *data, int n);
  double calculateVariance(double *data,double mean, int n);
  double calculateCovariance(double *data1, double *data2, int n);
  double *confidenceInterval(double mean, double SD, int n);
  double normalCDF(double x);
  double expectationPayoff(double t, double S);
  value getValue();
  double getb(std::vector<value> val, double y_mean, double s_t_mean, int n);
  a_final_result getYb(value_set values, double b, int n);
  int work(int all_step, int length, int log_step, int thread_id);
  int run(int count, int thread_count, int length);

  int service();
};