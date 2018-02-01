#include "../included/src/hw2.4.hpp"

double EuropeanVanilla::price_CRR(const BinomialModel &model) const
{
  std::vector<double> grid(1 + steps_expiry);

  // terminal condition
  for (unsigned int i = 0; i <= steps_expiry; ++i)
  {
    double spot_maturity = model.price(steps_expiry, i);
    grid[i] = my_payoff(spot_maturity);
  }

  double q_u = model.risk_neutral_prob(), q_d = 1.0 - q_u;
  double discount_factor = model.discount_factor();

  // backward induction
  for (int time = steps_expiry - 1; time >= 0; --time)
    for (int i = 0; i <= time; ++i)
      grid[i] = discount_factor * (q_d * grid[i] + q_u * grid[i + 1]);

  return grid[0];
}
int HW24::service()
{
  // define binomial model
  BinomialModel my_model(std::exp(0.3 * std::sqrt(0.5 / 20)), 1.0 / std::exp(0.3 * std::sqrt(0.5 / 20)), 0.0, 30.0);

  // define the option
  Call my_call(32.0); // initialize with strike price
  unsigned int steps_expiry = 20;
  EuropeanVanilla my_option(steps_expiry, my_call);

  // output price
  std::cout << "Option price under binomial model:" << my_option.price_CRR(my_model) << std::endl;

  return 0;
}
