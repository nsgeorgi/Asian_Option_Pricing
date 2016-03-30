#ifndef __ASIAN_H
#define __ASIAN_H

#include <vector>
#include "payoff.h"

class AsianOption {
protected:
	PayOff* pay_off;  // Pay-off class (in this instance call or put) 

public:
	AsianOption(PayOff* _pay_off);
	virtual ~AsianOption() {};

	// Pure virtual pay-off operator (this will determine arithmetic or geometric)
	virtual double pay_off_price(const std::vector<double>& spot_prices) const = 0;
};

class AsianOptionArithmetic : public AsianOption {
public:
	AsianOptionArithmetic(PayOff* _pay_off);
	virtual ~AsianOptionArithmetic() {};

	// Override the pure virtual function to produce arithmetic Asian Options
	virtual double pay_off_price(const std::vector<double>& spot_prices) const;
};

class AsianOptionGeometric : public AsianOption {
public:
	AsianOptionGeometric(PayOff* _pay_off);
	virtual ~AsianOptionGeometric() {};

	// Overide the pure virtual function to produce geometric Asian Options
	virtual double pay_off_price(const std::vector<double>& spot_prices) const;
};

#endif