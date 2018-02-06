#pragma once
#include "BinomialModel.h"
#include "Payoff.h"

class VanillaOption
{
 protected:
  VanillaOption(unsigned int expiry, const Payoff& payoff) : 
    steps_expiry(expiry), my_payoff(payoff) { }
 protected:
	unsigned int steps_expiry;  // maturity
  const Payoff& my_payoff;
};

class EuropeanVanilla : public VanillaOption
{
 public:
  EuropeanVanilla(int expiry, const Payoff& payoff) : VanillaOption(expiry, payoff) { }
  double price_CRR(const BinomialModel& model) const;
};



// to be implemented
class AmericanVanilla : public VanillaOption
{
  public:
  // ...
  AmericanVanilla(int expiry, const Payoff& payoff):
  VanillaOption(expiry, payoff){ }
  double price_Snell(const BinomialModel& model) const;
};
