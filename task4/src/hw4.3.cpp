#include <iostream>
#include "../included/src/BSMModel.h"
#include <vector>
#include <random>
#include <cmath>


int main(int argc, const char * argv[]) {
    //set up model
    double interest = 0.05, sigma = 0.3;
    BSMModel myModel(interest,sigma);
    double S_0 = 50.0, maturity = 0.25;
    double strike = 55;
    
    unsigned sample = 10; //10000 samples are needed
    double spotPrice[sample]; //10000 spot prices
    double optionPayoff[sample];
    
    for(int i = 0; i < sample; ++i){
        //generate BSM spot prices
        spotPrice[i] = myModel.sim_path(maturity, S_0, 2)[1]; //terminal spot price
        std::cout << spotPrice[i] << std::endl;
        
        //call option payoff (S-K)+
        if(spotPrice[i] > strike)
            optionPayoff[i] = spotPrice[i]-strike;
        else
            optionPayoff[i] = 0;
        std::cout << optionPayoff[i] << std::endl;
    }
    

    
    
    
    return 0;
}
