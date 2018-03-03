#include "../included/src/simpath.h"
#include <cmath>
#include <random>

double SimulatePath(double maturity)
{
	double s_0 = std::log(50.0), r = 0.05, sigma = 0.3;

	std::random_device rd;
	std::mt19937 rng(rd());
	std::normal_distribution<double> norm(0.0, 1.0);
 
	double drift_log = r - 0.5*sigma*sigma;
	double dt = maturity, sqrt_dt = std::sqrt(dt);
	double dW = sqrt_dt*norm(rng);
	double log_price=drift_log*dt + sigma*dW;

	return log_price;
}
