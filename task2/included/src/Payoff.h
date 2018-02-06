#pragma once

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
	double operator()(double spot) const
	{
		return strike > spot ? strike - spot : 0;
	}
private:
	double strike;
};

