#pragma once
#include <cmath>

class BinomialModel
{
public:
	BinomialModel(double u, double d, double R, double spot) :
		up_factor(u), down_factor(d), interest_rate(R), spot_init(spot) { }
	double risk_neutral_prob() const  // probability for the up direction
	{
		return ((1 + interest_rate) - down_factor)/(up_factor - down_factor);
	}
	double discount_factor() const  // 1/(1 + R)
	{
		return 1/(1 + interest_rate);
	}
	double price(unsigned int time, unsigned int num_up) const  // spot price at node (time, num_up)
	{
    return spot_init*std::pow(up_factor, num_up)*std::pow(down_factor, time - num_up);
	}
private:
	double up_factor;
	double down_factor;
	double interest_rate;
	double spot_init;
};