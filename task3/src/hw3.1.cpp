#include "../included/src/hw3.1.hpp"


int HW31::service()
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
