#include "../included/src/hw3.1.hpp"



int HW31::service()
{
  // define binomial model, u=1.1, d=1/1.1, r=0.03, spot=30.0
  BinomialModel my_model(1.1, 1.0 / 1.1, 0.03, 30.0);
  unsigned int steps_expiry = 5;//number of steps

  // define the call option
  Call my_call(32.0); // initialize with strike price
  AmericanVanilla my_optionAC(steps_expiry, my_call);

  //define the put option
  Put my_put(30.0); // initialize with strike price
  AmericanVanilla my_optionAP(steps_expiry, my_put);

  //define the strangle option
  Strangle my_strangle(30.0,32.0);// initialize with strike price, K1<=K2
  AmericanVanilla my_optionAS(steps_expiry, my_strangle);

  // output price
  std::cout << "American Call option price under binomial model:" << my_optionAC.price_Snell(my_model) << std::endl;

  std::cout << "American Put option price under binomial model:" << my_optionAP.price_Snell(my_model) << std::endl;

  std::cout << "American Strangle option price under binomial model:" << my_optionAS.price_Snell(my_model) << std::endl;

  return 0;
}
