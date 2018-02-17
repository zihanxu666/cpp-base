#include "../included/src/testForNormalGeneratorGenerator.hpp"

double TestForNormalGeneratorGenerator::generator()
{

    double result;
    switch(mark)
    {
        case 0:
            result=0.3;
        break;
        case 1:
            result=0.5;
        break;
        case 2:
            result=0.8;
        break;
        default:
            result=0.3;
            mark=0;
        break;
    }
    mark++;
    return result;
}