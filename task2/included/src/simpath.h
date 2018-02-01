#pragma once

#include <vector>

// Generate a random path for the SDE
//   d log S = (mu - 0.5*sigma^2) dt + sigma dW
// In this implementation the parameters (S_0, mu, sigma) are fixed.
// The user picks the maturity and the number of time steps.
// It outputs log S(0), log S(h), log S(2h), ..., log S(mautrity),
// where h = maturity / num_steps.
std::vector<double> SimulatePath(double maturity, int num_steps);