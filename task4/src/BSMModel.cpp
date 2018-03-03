#include "BSMModel.h"

std::vector<double> BSMModel::sim_path(double maturity, double S_init, unsigned length_out)
{
	std::vector<double> path(length_out);

	// trivial case
    if (length_out == 1) {
        path[0] = S_init;
        return path;
    }
  
  // first simulate path of log S, then take exp (numerically more stable)
    path[0] = std::log(S_init);
    unsigned num_period = length_out - 1;
    double growth_rate = interest_rate - 0.5*sigma*sigma;
    double dt = maturity/num_period;
    double drift = growth_rate*dt;
    double volatility = sigma*std::sqrt(dt);

	for (unsigned i = 1; i <= num_period; ++i) {
        double dlogS = drift + volatility*normal(rng);
    path[i] = path[i - 1] + dlogS;
	
    }

  // get S = exp(log S)
    for (unsigned i = 0; i < length_out; ++i)
        path[i] = std::exp(path[i]);

	return path;
}
