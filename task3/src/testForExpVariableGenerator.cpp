#include "../included/src/testForExpVariableGenerator.hpp"

double TestForExpVariableGenerator::generator()
{
    double result=0.0;
    if(mark<0)
    {
        result= 0.5;
    }else{
        result= 0.8;
    }

    mark *=-1;
    return result;
}