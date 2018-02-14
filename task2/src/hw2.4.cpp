#include "../included/src/hw2.4.hpp"


int HW24::service()
{
  // // define binomial model
  // BinomialModel my_model(std::exp(0.3 * std::sqrt(0.5 / 20)), 1.0 / std::exp(0.3 * std::sqrt(0.5 / 20)), 0.0, 30.0);

  // // define the option
  // Call my_call(32.0); // initialize with strike price
  // unsigned int steps_expiry = 20;
  // EuropeanVanilla my_option(steps_expiry, my_call);

  // // output price
  // std::cout << "Option price under binomial model:" << my_option.price_CRR(my_model) << std::endl;
// define binomial model
  BinomialModel my_model(std::exp(0.3 * std::sqrt(0.5 / 20)), 1.0 / std::exp(0.3 * std::sqrt(0.5 / 20)), 0.03, 30.0);

  // define the call option
  Call my_call(40.0); // initialize with strike price
  unsigned int steps_expiry = 20;
  EuropeanVanilla my_optionEC(steps_expiry, my_call);
  AmericanVanilla my_optionAC(steps_expiry, my_call);

  //define the put option
  Put my_put(30.0); // initialize with strike price
  EuropeanVanilla my_optionEP(steps_expiry, my_put);
  AmericanVanilla my_optionAP(steps_expiry, my_put);

  //define the strangle option
  Strangle my_strangle(34.0,32.0);
  EuropeanVanilla my_optionES(steps_expiry, my_strangle);
  AmericanVanilla my_optionAS(steps_expiry, my_strangle);

  // output price
  std::cout << "European Call option price under binomial model:" << my_optionEC.price_CRR(my_model) << std::endl;
  
  std::cout << "American Call option price under binomial model:" << my_optionAC.price_Snell(my_model) << std::endl;

  std::cout << "European Put option price under binomial model:" << my_optionEP.price_CRR(my_model) << std::endl;
  
  std::cout << "American Put option price under binomial model:" << my_optionAP.price_Snell(my_model) << std::endl;

  std::cout << "European Strangle option price under binomial model:" << my_optionES.price_CRR(my_model) << std::endl;
  
  std::cout << "American Strangle option price under binomial model:" << my_optionAS.price_Snell(my_model) << std::endl;
  return 0;
}
