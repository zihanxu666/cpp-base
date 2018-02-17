#include "baseGenerator.hpp"

class TestForNormalGeneratorGenerator : public Generator
{
  private:
    int mark=0;
  public:
    double generator();
};