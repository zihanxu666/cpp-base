#include "../included/src/generatorBuilder.hpp"


Generator * GeneratorBuilder::getGenerator(GeneratorType type)
{
    Generator * result=NULL;

    switch (type)
    {
        case GeneratorType::UNI:
            result=new UniGenerator();
        break;

        case GeneratorType::SIMPLE:
            result=new SimpleGenerator();
        break;

        case GeneratorType::TEST_EXP_GENERATOR:
            result=new TestForExpGeneratorGenerator();
        break;

        case GeneratorType::TEST_EXP_VARABLE:
            result=new TestForExpVariableGenerator();
        break;

        case GeneratorType::TEST_NORMAL:
            result=new TestForNormalGeneratorGenerator();
        break;

        default:
            result=new UniGenerator();
        break;
    }

    return result;
}

