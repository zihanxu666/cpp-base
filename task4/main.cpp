// Main.cpp
#define CATCH_CONFIG_RUNNER
#include <limits>
#include <string>
#include <cstdlib>

#include "included/src/catch.hpp"
// #include "included/src/hw3.1.hpp"
// #include "included/src/hw3.2.hpp"
// #include "included/src/hw3.2c.hpp"
// #include "included/src/generatorBuilder.hpp"

// TEST_CASE("HW3.1_TEST", "[BASE]")
// {

// 	SECTION("HW3.1[normal]")
// 	{
// 		HW31 *obj = new HW31();
// 		REQUIRE(obj != NULL);
// 	}
// }

// TEST_CASE("HW3.2_TEST", "[BASE]")
// {

// 	SECTION("HW3.2[normal]")
// 	{

// 		SECTION("HW3.2_expGenerator[normal]")
// 		{

// 			HW32 *obj = new HW32(GeneratorBuilder::getGenerator(GeneratorType::TEST_EXP_GENERATOR));
// 			REQUIRE(obj != NULL);
// 			auto tmp = obj->expGenerator(1);
// 			char buffer[20];
// 			gcvt(tmp, 6, buffer);
// 			std::string result = buffer;
// 			REQUIRE(result == "0.223144");
// 		}

// 		SECTION("HW3.2_expVariable[normal]")
// 		{
// 			HW32 *obj = new HW32(GeneratorBuilder::getGenerator(GeneratorType::TEST_EXP_VARABLE));
// 			REQUIRE(obj != NULL);
// 			auto tmp = obj->expVariable();
// 			char buffer[20];
// 			gcvt(tmp, 6, buffer);
// 			std::string result = buffer;
// 			REQUIRE(result == "0.693147");
// 		}

// 		SECTION("HW3.2_normalGenerator[normal]")
// 		{
// 			HW32 *obj = new HW32(GeneratorBuilder::getGenerator(GeneratorType::TEST_NORMAL));
// 			REQUIRE(obj != NULL);
// 			auto tmp = obj->normalGenerator();
// 			char buffer[20];
// 			gcvt(tmp, 6, buffer);
// 			std::string result = buffer;
// 			REQUIRE(result == "0.693147");
// 		}

// 		SECTION("HW3.2_calculateMean[normal]")
// 		{
// 			HW32 *obj = new HW32(GeneratorBuilder::getGenerator(GeneratorType::SIMPLE));
// 			REQUIRE(obj != NULL);
// 			double array[3] = {0.1, 0.1, 0.1};

// 			auto tmp = obj->calculateMean(array, 3);
// 			char buffer[20];
// 			gcvt(tmp, 3, buffer);
// 			std::string result = buffer;
// 			REQUIRE(result == "0.1");
// 		}

// 		SECTION("HW3.2_calculateSD[normal]")
// 		{
// 			HW32 *obj = new HW32(GeneratorBuilder::getGenerator(GeneratorType::SIMPLE));
// 			REQUIRE(obj != NULL);
// 			double array[3] = {0.1, 0.1, 0.1};
// 			auto tmp = obj->calculateSD(array, 0.1, 3);
// 			REQUIRE(tmp == 0);
// 		}
// 		SECTION("HW3.2_confidenceInterval[normal]")
// 		{
// 			HW32 *obj = new HW32(GeneratorBuilder::getGenerator(GeneratorType::SIMPLE));
// 			REQUIRE(obj != NULL);
// 			auto *tmp = obj->confidenceInterval(0, 1);
// 			char buffer1[20];
// 			char buffer2[20];
// 			gcvt(*tmp, 3, buffer1);
// 			gcvt(*(tmp + 1), 3, buffer2);
// 			std::string lower = buffer1;
// 			std::string upper = buffer2;
// 			REQUIRE(lower == "-1.96");
// 			REQUIRE(upper == "1.96");
// 		}
// 	}
// }

// TEST_CASE("HW3.2c_TEST", "[BASE]")
// {

// 	SECTION("HW3.2c[normal]")
// 	{
// 		HW32c *obj = new HW32c();
// 		REQUIRE(obj != NULL);

// 		SECTION("HW2.3_calculateMean[normal]")
// 		{
// 			double array[3] = {0.1, 0.1, 0.1};

// 			auto tmp = obj->calculateMean(array, 3);
// 			char buffer[20];
// 			gcvt(tmp, 3, buffer);
// 			std::string result = buffer;
// 			REQUIRE(result == "0.1");
// 		}

// 		SECTION("HW3.2c_calculateSD[normal]")
// 		{
// 			double array[3] = {0.1, 0.1, 0.1};
// 			auto tmp = obj->calculateSD(array, 0.1, 3);
// 			REQUIRE(tmp == 0);
// 		}

// 		SECTION("HW3.2c_confidenceInterval]")
// 		{
// 			auto *tmp = obj->confidenceInterval(0, 1);
// 			char buffer1[20];
// 			char buffer2[20];
// 			gcvt(*tmp, 3, buffer1);
// 			gcvt(*(tmp + 1), 3, buffer2);
// 			std::string lower = buffer1;
// 			std::string upper = buffer2;
// 			REQUIRE(lower == "-1.96");
// 			REQUIRE(upper == "1.96");
// 		}
// 	}
// }

int main(int argc, char **argv)
{
	int hw_length = 3;
	std::string message = "enter number [1-";
	message.append(std::to_string(hw_length)).append("] to run , exit when enter number is [0]\n").append("1: run 3.1").append("\n").append("2: run 3.2").append("\n").append("3: run 3.2c");

	int result = Catch::Session().run(argc, argv);

	std::cout << message << std::endl;

	std::string str;

	int command = -1;

	std::cin >> command;
	HW *objArray[hw_length];

	objArray[0] = new HW31();
	objArray[1] = new HW32(GeneratorBuilder::getGenerator(GeneratorType::UNI));
	objArray[2] = new HW32c();

	while (command != 0)
	{

		if (command <= hw_length)
		{
			objArray[command - 1]->service();
		}
		command = -1;
		std::cout << "============================================" << std::endl;
		std::cout << message << std::endl;
		std::cin >> command;
	}

	for (auto p : objArray)
	{
		delete p;
	}

	std::cout << "bye..." << std::endl;
}