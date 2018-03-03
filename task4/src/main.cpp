#include "../included/src/BSMModel.h"
#include "../included/src/Payoff.h"
#include <iostream>
#include <vector>
#include <numeric>  // for std::accumulate

int main()
{
  // set up model
  double interest_rate = 0.02, sigma = 0.3;
  BSMModel my_model(interest_rate, sigma);
  double S_init = 40.0, maturity = 0.5;
  Call my_call(41.0);

  // simulate payoff at maturity
  unsigned N_sample = 200000;
  std::vector<double> payoff_maturity(N_sample);
  for(unsigned i = 0; i < N_sample; ++i) {
    double spot_maturity = (my_model.sim_path(maturity, S_init, 2))[1];  // only terminal price is needed
    payoff_maturity[i] = my_call(spot_maturity);
  }

  // output price
  double sample_average = std::accumulate(payoff_maturity.begin(), payoff_maturity.end(), 0.0)/N_sample;
	sample_average *= std::exp(-interest_rate*maturity);  // discounting
  
  std::cout << "Estimated price is " << sample_average << std::endl;
}