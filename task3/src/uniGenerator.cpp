#include "../included/src/uniGenerator.hpp"

double UniGenerator::generator()
{
    static std::random_device rd;
    static std::mt19937 rng(rd());
    static std::uniform_real_distribution<double> uni(0.0, 1.0);
    return uni(rng);
}