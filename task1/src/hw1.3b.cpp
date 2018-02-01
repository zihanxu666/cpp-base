#include "../included/src/hw1.3b.h"

/*
    auth by Zihan Xu
    create date: 2018-01-14 
    last update date: 2018-01-14
*/



//begin function implement
int HW13b::service()
{
    int n;
    double p;

    std::cout << "Please enter the value for n" << std::endl;
    std::cin >> n;
    std::cout << "n=[" << n << "] Please enter the value for p" << std::endl;
    std::cin >> p;
    std::cout << "n=[" << n << "] , p=[" << p << "]" << std::endl;

    double sum = 0.0; //initial value
    
    for (int k = 0; k <= n; k++)
    {
        sum += binomialCoeff(n, k) * pow(p, k) * pow(1 - p, n - k) * cos(k);
    }

    std::cout << "The result is [" << sum << "]" << std::endl;
    return 0;
}

// Return value of Binomial Coefficient C(n, k)
int HW13b::binomialCoeff(int n, int k)
{
    // Base Cases
    if (k == 0 || k == n)
        return 1;

    // Recur
    return binomialCoeff(n - 1, k - 1) + binomialCoeff(n - 1, k);
}
