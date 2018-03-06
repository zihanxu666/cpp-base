// Main.cpp
#define CATCH_CONFIG_RUNNER
#include <limits>
#include <string>
#include <cstdlib>

#include "included/src/catch.hpp"
#include "included/src/hw4.2.hpp"
#include "included/src/hw4.3a.hpp"
#include "included/src/hw4.3b.hpp"

TEST_CASE("HW4.2_TEST", "[BASE]")
{

	SECTION("HW4.2[normal]")
	{

		SECTION("HW4.2_getOmega[normal]")
		{
			Eigen::VectorXd mu(3);
			Eigen::MatrixXd Sigma(3, 3);
			mu << 0.04, 0.025, 0.06;
			Sigma << 0.00640000, 0.00368695, 0.00360000, 0.00368695, 0.00590000, 0.00311086, 0.00360000, 0.00311086, 0.00810000;
			Eigen::VectorXd result = obj->getOmega(mu, Sigma);
			double tmp1=result[0];
			tmp
			char buffer[20];
			gcvt(tmp, 6, buffer);
			std::string result = buffer;
			REQUIRE(result == "0.223144");
		}

		SECTION("HW3.2_expVariable[normal]")
		{
			HW32 *obj = new HW32(GeneratorBuilder::getGenerator(GeneratorType::TEST_EXP_VARABLE));
			REQUIRE(obj != NULL);
			auto tmp = obj->expVariable();
			char buffer[20];
			gcvt(tmp, 6, buffer);
			std::string result = buffer;
			REQUIRE(result == "0.693147");
		}
	}
}

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
	message.append(std::to_string(hw_length)).append("] to run , exit when enter number is [0]\n").append("1: run 4.2").append("\n").append("2: run 4.3a").append("\n").append("3: run 4.3b");

	int result = Catch::Session().run(argc, argv);

	std::cout << message << std::endl;

	std::string str;

	int command = -1;

	std::cin >> command;
	HW *objArray[hw_length];

	objArray[0] = new HW42();
	objArray[1] = new HW43a();
	objArray[2] = new HW43b();

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