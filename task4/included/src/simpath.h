#pragma once


// Generate a random path for the SDE
// d log S = (r - 0.5*sigma^2) dt + sigma dW
// In this implementation the parameters (S_0, r, sigma) are fixed.
// The user picks the maturity 
// It outputs log S(mautrity),
double SimulatePath(double maturity);