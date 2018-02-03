// Main.cpp
#define CATCH_CONFIG_RUNNER
#include <limits>
#include <string>
#include <cstdlib>
#include "included/src/catch.hpp"
#include "included/src/hw2.1.hpp"
#include "included/src/hw2.2.hpp"
#include "included/src/hw2.3.hpp"
#include "included/src/hw2.4.hpp"

TEST_CASE("HW2.1_TEST", "[BASE]")
{

	SECTION("HW2.1[normal]")
	{
		HW21 *obj = new HW21();
		REQUIRE(obj != NULL);
		std::string a = "true";
		std::string b = "is_true_string";

		bool result = obj->FindSubSeq(a, b);
		REQUIRE(result == true);
	}
	SECTION("HW2.1[error]")
	{
		HW21 *obj = new HW21();
		REQUIRE(obj != NULL);
		std::string a = "false";
		std::string b = "is_true_string";

		bool result = obj->FindSubSeq(a, b);
		REQUIRE(result == false);
	}
}

TEST_CASE("HW2.2_TEST", "[BASE]")
{

	SECTION("HW2.2[normal]")
	{
		HW22 *obj = new HW22();
		REQUIRE(obj != NULL);

		SECTION("HW2.2_buildVector_comma[normal]")
		{
			auto result = obj->buildVector("0,1,2,3,4,5");
			int i = 0;
			for (auto val : result)
			{
				REQUIRE(val == i++);
			}
		}

		SECTION("HW2.2_buildVector_space[normal]")
		{
			auto result = obj->buildVector("0 1 2 3 4 5");
			int i = 0;
			for (auto val : result)
			{
				REQUIRE(val == i++);
			}
		}

		SECTION("HW2.2_buildVector_mix[normal]")
		{
			auto result = obj->buildVector("0,1,2 3 4,5");
			int i = 0;
			for (auto val : result)
			{
				REQUIRE(val == i++);
			}
		}

		SECTION("HW2.2_merge[normal]")
		{
			std::vector<int> v1 = {0, 1, 3}, v2 = {2, 4}, result;
			obj->initialize(v1, v2);
			obj->merge(result, 0, 0);
			int i = 0;
			for (auto val : result)
			{
				REQUIRE(val == i++);
			}
		}
	}
	SECTION("HW2.2[error]")
	{
		HW22 *obj = new HW22();
		REQUIRE(obj != NULL);

		SECTION("HW2.2_buildVector[error]")
		{
			auto result = obj->buildVector("0|1|2|3|4|5");
			int i = 0;
			REQUIRE(result.empty() != true);
			REQUIRE(result.size() == 1);
		}
	}
}

TEST_CASE("HW2.3_TEST", "[BASE]")
{

	SECTION("HW2.3[normal]")
	{
		HW23 *obj = new HW23();
		REQUIRE(obj != NULL);
		SECTION("HW2.3_normalCDF[normal]")
		{
			double tmp=obj->normalCDF(0.0);
			bool result =std::fabs(tmp-0.5)<=std::numeric_limits<double> ::epsilon();
			REQUIRE(result==true);
		}

		SECTION("HW2.3_Delta[normal]")
		{
			double tmp = obj->Delta(0,30);
			char buffer[20];
			gcvt(tmp,6,buffer);
			std::string result=buffer;
			REQUIRE(result=="0.421455");
			
		}

		SECTION("HW2.3_callPrice[normal]")
		{
			double tmp = obj->callPrice(0,30);
			char buffer[20];
			gcvt(tmp,6,buffer);
			std::string result=buffer;
			REQUIRE(result=="1.73833");
		}

		SECTION("HW2.3_HedgePayoff[normal]")
		{
			std::vector<double> v1 = {1, 1, 1};
			double tmp=obj->HedgePayoff(v1);
			char buffer[20];
			gcvt(tmp,6,buffer);
			std::string result=buffer;
			REQUIRE(result=="1.73833");
			
		}
		SECTION("HW2.3_calculateSD[normal]")
		{
			double v1[] = {1,1,1};
			double result=obj->calculateSD(v1,3);
			
			REQUIRE(result==0);
		}
	}
}
int main(int argc, char **argv)
{
	std::string message = "enter number [1-4] to run , exit when enter number is [0]\n";
	message.append("1: run 2.1").append("\n").append("2: run 2.2").append("\n").append("3: run 2.3").append("\n").append("4: run 2.4");

	int result = Catch::Session().run(argc, argv);

	std::cout << message << std::endl;

	std::string str;

	int command = -1;
	int hw_length = 4;
	std::cin >> command;
	HW *objArray[hw_length];

	objArray[0] = new HW21();
	objArray[1] = new HW22();
	objArray[2] = new HW23();
	objArray[3] = new HW24();

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
