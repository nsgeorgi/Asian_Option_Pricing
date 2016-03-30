#include <iostream>

#include "payoff.h"
#include "asian.h"
#include "path_generate.h"

int main(int argc, char **argv) {
	
	// First we create the parameter list
	
	unsigned num_sims = 100000;   // Number of simulated asset paths
	unsigned num_intervals = 250;  // Number of intervals for the asset path to be sampled 
	double S = 30.0;  // Option price
	double K = 29.0;  // Strike price
	double r = 0.08;   // Risk-free rate (8%)
	double v = 0.3;    // Volatility of the underlying (30%)
	double T = 1.00;    // One year until expiry
	std::vector<double> spot_prices(num_intervals, S);  // The vector of spot prices

														// Create the PayOff objects
	PayOff* pay_off_call = new PayOffCall(K);
	
	// Create the AsianOption objects
	AsianOptionArithmetic asian(pay_off_call);
	
	// Update the spot price vector with correct 
	// spot price paths at constant intervals
	double payoff_sum = 0.0;
	for (int i = 0; i < num_sims; i++) {
		calc_path_spot_prices(spot_prices, r, v, T);
		payoff_sum += asian.pay_off_price(spot_prices);
	}
	
	double discount_payoff_avg = (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);

	delete pay_off_call;
	
	// Finally we output the parameters and prices
	std::cout << "Number of Paths: " << num_sims << std::endl;
	std::cout << "Number of Ints:  " << num_intervals << std::endl;
	std::cout << "Underlying:      " << S << std::endl;
	std::cout << "Strike:          " << K << std::endl;
	std::cout << "Risk-Free Rate:  " << r << std::endl;
	std::cout << "Volatility:      " << v << std::endl;
	std::cout << "Maturity:        " << T << std::endl;

	std::cout << "Asian Price:     " << discount_payoff_avg << std::endl;
	system("PAUSE");
	return 0;
}