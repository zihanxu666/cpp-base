#include "../included/src/hw1.4.h"

/*
    auth by Zihan Xu
    create date: 2018-01-14 
    last update date: 2018-01-14
    objective: To find the root of f(x) = cos(x) - x
    method: bisection method
*/



//begin function implement
int HW14::service()
{
    Base_struct _a = init("lower"), _b = init("upper");

    std::cout << "Enter your tolerance please:" << std::endl;
    std::cin.clear();
    std::cin >> eps;

    if (_a.f_val * _b.f_val > 0 || _a.value >= _b.value) //check if the interval is valid for bisection method
    {

        while (_a.f_val * _b.f_val > 0 || _a.value >= _b.value)
        {
            std::cout << "The interval is invalid, please enter your interval again." << std::endl;
            _a = init("lower"), _b = init("upper");
        }
    }

    if(checkInit(_a))return 0; //check if a is the root of the function
    if(checkInit(_b))return 0; //check if b is the root of the function

    /*
    When interval [a,b] is valid such that f(a) and f(b) have different signs, 
    and neither a nor b is the root of the function
    then we start to use bisection method.
    */

    std::cout << "{'obj_a': {'value':" << _a.value << ", 'f_val':" << _a.f_val << " }," << std::endl;
    std::cout << "'obj_b': {'value':" << _b.value << ", 'f_val':" << _b.f_val << " }}" << std::endl;
    
    double m = (_a.value + _b.value) / 2; // initial_value of m

    while (std::abs(f(m)) >= eps) //repeat the bisection method until |f(x)|<eps
    {
        if (f(m) * _a.f_val > 0) //if f(m) have the same sign with f(a), a will be m.
        {
            _a.value = m;
        }
        else //f(m) have the same sign with f(b), b will be m.
        {
            _b.value = m;
        }

        m = (_a.value + _b.value) / 2;
    }
    std::cout << "The root of the function is " << m << "." << std::endl;

    return 0;
}

/*
function f = cos(x) - x 
*/
double HW14::f(double x)
{
    return cos(x) - x;
}

/*
to input lower and upper bound of the initial interval, 
return their values and results of the function
*/
HW14::Base_struct HW14::init(std::string keyword)
{
    Base_struct result;
    std::cout << "Enter " << keyword << " bound of your interval please:" << std::endl;
    std::cin.clear();
    std::cin >> result.value;
    result.f_val = f(result.value);
    return result;
}

/*
check if the initial valid input is the root of the function
*/
bool HW14::checkInit(Base_struct param)
{
    if (param.f_val == 0 || std::abs(param.f_val) < eps)
    {

        std::cout << "The root of the function is [" << param.value << "]." << std::endl;
        return true;
    }
    return false;
}
