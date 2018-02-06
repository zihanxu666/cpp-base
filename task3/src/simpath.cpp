#include "../included/src/simpath.h"
#include <vector>
#include <cmath>
#include <random>

std::vector<double> SimulatePath(double maturity, int num_steps)
{
	double s_0 = std::log(30.0), mu = 0.1, sigma = 0.3;

	std::random_device rd;
	std::mt19937 rng(rd());
	std::normal_distribution<double> norm(0.0, 1.0);
 
	double drift_log = mu - 0.5*sigma*sigma;
	double dt = maturity / num_steps, sqrt_dt = std::sqrt(dt);

	std::vector<double> log_price(1 + num_steps);
	log_price[0] = s_0;
	for (int i = 1; i <= num_steps; ++i) {
		double dW = sqrt_dt*norm(rng);
		double ds = drift_log*dt + sigma*dW;
		log_price[i] = log_price[i - 1] + ds;
	}

	return log_price;
}
