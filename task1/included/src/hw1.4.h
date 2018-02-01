#include <iostream>
#include <string>
#include <cmath>

class HW14
{
private:
    //begin define variables
    double eps; //tolerance of f(x)
public:

    struct Base_struct
    {
        double value;
        double f_val;//f(value)
    };
//begin define functions
double f(double);
Base_struct init(std::string keyword);
bool checkInit(Base_struct value);
int service();
};
