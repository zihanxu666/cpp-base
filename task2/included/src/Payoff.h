#pragma once
#include <cassert>
class Payoff
{
 public:
	virtual double operator()(double spot) const = 0;
};

class Call : public Payoff
{
 public:
  Call(double strike) : strike(strike) { }
	double operator()(double spot) const
	{
		return spot > strike ? spot - strike : 0;
	}
 private:
	double strike;
};

class Put : public Payoff
{
public:
  Put(double strike) : strike(strike) { }
	double operator()(double spot) const
	{
		return strike > spot ? strike - spot : 0;
	}
private:
	double strike;
};

class Strangle:public Payoff
{
	public:
	Strangle(double strike1,double strike2) : strike1(strike1),strike2(strike2) { }
	double operator()(double spot) const
	{   assert(strike1<=strike2);
		if(strike1>=spot)
		{
			return strike2-spot;
		}
		else if(spot>=strike2)
		{
            return spot-strike1;
		}
		
			return 0;
		
		
	}
    private:
	double strike1,strike2;
};