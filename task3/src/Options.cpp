#include "../included/src/BinomialModel.h"
#include "../included/src/Options.h"
#include <vector>
#include <cmath>

double EuropeanVanilla::price_CRR(const BinomialModel& model) const
{
  std::vector<double> grid(1 + steps_expiry);

  // terminal condition
	for (unsigned int i = 0; i <= steps_expiry; ++i) {
    double spot_maturity = model.price(steps_expiry, i);
    grid[i] = my_payoff(spot_maturity);
	}
 
  double q_u = model.risk_neutral_prob(), q_d = 1.0 - q_u;
  double discount_factor = model.discount_factor();

	// backward induction
  for(int time = steps_expiry - 1; time >= 0; --time)
		for (int i = 0; i <= time; ++i)
      grid[i] = discount_factor*(q_d*grid[i] + q_u*grid[i + 1]);

  return grid[0];
}
//1.(b) American option
double AmericanVanilla::price_Snell(const BinomialModel& model) const
{
  std::vector<double> grid(1 + steps_expiry);

  // terminal condition
	for (unsigned int i = 0; i <= steps_expiry; ++i) {
    double spot_maturity = model.price(steps_expiry, i);
    grid[i] = my_payoff(spot_maturity);
	}
 
  double q_u = model.risk_neutral_prob(), q_d = 1.0 - q_u;
  double discount_factor = model.discount_factor();

	// backward induction
  for(int time = steps_expiry - 1; time >= 0; --time)
		for (int i = 0; i <= time; ++i)
      grid[i] = my_payoff(model.price(time,i))>discount_factor*(q_d*grid[i] + q_u*grid[i + 1])?my_payoff(model.price(time,i)):discount_factor*(q_d*grid[i] + q_u*grid[i + 1]);

  return grid[0];
}
