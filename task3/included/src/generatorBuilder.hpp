#include "baseGenerator.hpp"
#include "simpleGenerator.hpp"
#include "uniGenerator.hpp"
#include "testForExpGeneratorGenerator.hpp"
#include "testForExpVariableGenerator.hpp"
#include "testForNormalGeneratorGenerator.hpp"

#include <string>

enum class GeneratorType
{
    SIMPLE,
    UNI,
    TEST_EXP_GENERATOR,TEST_EXP_VARABLE,
    TEST_NORMAL
};

class GeneratorBuilder
{
    public:
    private:
    public:
    static Generator * getGenerator(GeneratorType type);
};
