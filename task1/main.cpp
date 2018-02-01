// Main.cpp
#define CATCH_CONFIG_RUNNER
#include <iostream>
// #include "included/src/gtest/gtest.h"

// #include "included/src/gtest/gtest.h"
// #include "test/Test1.1a.cpp"
// #include "test/ConfigureTest.cpp"

// #include "included/src/hw1.1b.h"
// #include "included/src/Test3.hpp"

#include "included/src/catch.hpp"
#include "included/src/hw1.1a.h"
#include "included/src/hw1.1b.h"
#include "included/src/hw1.2a.h"
#include "included/src/hw1.2b.h"
#include "included/src/hw1.3a.h"
#include "included/src/hw1.3b.h"
#include "included/src/hw1.4.h"
#include "included/src/hw1.5.h"
using std::cout;
// using ::testing::InitGoogleTest;
TEST_CASE("HW1_TEST","[BASE]"){
    
    SECTION("HW1.1A"){
        HW11a * obj1=new HW11a();
        REQUIRE( obj1 !=NULL );
        obj1->pattern(5);
        
    }
    SECTION("HW1.1B"){
        HW11b * obj2=new HW11b();
        REQUIRE( obj2 !=NULL );
        obj2->pattern(5,1);
        
    }
}
TEST_CASE("HW2_TEST","[BASE]"){
    
    SECTION("HW1.2A[normal]"){
        HW12a * obj1=new HW12a();
        REQUIRE( obj1 != NULL );
        obj1->checkPalindrome("asdfdsa");
        
    }
    SECTION("HW1.2A[error]"){
        HW12a * obj1=new HW12a();
        REQUIRE( obj1 != NULL );
        obj1->checkPalindrome("asdf");
        
    }
    
    SECTION("HW1.2B[normal]"){
        HW12b * obj2=new HW12b();
        REQUIRE( obj2 != NULL );
        std::string str="abc";
        
        obj2->reverse(str);
        
        REQUIRE(str == "cba");
        
    }
    
    SECTION("HW1.2B[error]"){
        HW12b * obj2=new HW12b();
        REQUIRE( obj2 != NULL );
        std::string str="abc";
        
        obj2->reverse(str);
        REQUIRE_FALSE(str=="abc");
        
    }
}

TEST_CASE("HW3_TEST","[BASE]")
{
    SECTION("HW1.3A[normal]"){
        HW13a * obj1=new HW13a();
        REQUIRE( obj1 != NULL);
        int result=obj1->binomialCoeff(3,2);
        REQUIRE(result==3);
        double * resultArray=obj1->binomial(1,0.3);
        REQUIRE(resultArray!=NULL);
    }
    SECTION("HW1.3B[normal]"){
        HW13b * obj2=new HW13b();
        REQUIRE( obj2 != NULL);
        int result=obj2->binomialCoeff(3,2);
        REQUIRE(result==3);
        
    }
}
TEST_CASE("HW4_TEST","[BASE]")
{
    SECTION("HW1.4[normal]"){
        HW14 * obj1=new HW14();
        REQUIRE( obj1 != NULL);
        
        double result=obj1->f(1);
        REQUIRE(result<0);
    }
}
TEST_CASE("HW5_TEST","[BASE]")
{
    SECTION("HW1.5[normal]"){
        HW15 * obj1=new HW15();
        REQUIRE( obj1 != NULL);
        SECTION("find date from String param"){
            
            int result=obj1->getParam("19-01-2018",0,2);
            REQUIRE(result==19);
            result=obj1->getParam("19-01-2018",3,2);
            REQUIRE(result==1);
            result=obj1->getParam("19-01-2018",6,4);
            REQUIRE(result==2018);
            
            result=obj1->getParam("19-01-2018",0);
            REQUIRE(result==19);
            result=obj1->getParam("19-01-2018",3);
            REQUIRE(result==1);
            result=obj1->getParam("19-01-2018",6);
            REQUIRE(result==20);
            result=obj1->getParam("19-01-2018",8);
            REQUIRE(result==18);
            
            int * resultArray=obj1->getAllParam("19-01-2018");
            
            REQUIRE(resultArray[0]==19);
            REQUIRE(resultArray[1]==1);
            REQUIRE(resultArray[2]==2018);
        }
        SECTION("check param"){
            
            int year=2016,month=2,day=29;
            
            int result=obj1->inputCheck(year,month,day);
            REQUIRE(result==0);
            
            year=2015,month=2,day=28;
            result=obj1->inputCheck(year,month,day);
            REQUIRE(result==0);
            
            year=2015,month=4,day=30;
            result=obj1->inputCheck(year,month,day);
            REQUIRE(result==0);
            
            year=2015,month=5,day=31;
            result=obj1->inputCheck(year,month,day);
            REQUIRE(result==0);
            
        }
    }
    SECTION("HW1.5[error]"){
        HW15 * obj1=new HW15();
        REQUIRE( obj1 != NULL);
        SECTION("check param"){
            
            int year=2016,month=2,day=30;
            
            int result=obj1->inputCheck(year,month,day);
            REQUIRE(result==1);
            
            year=2015,month=2,day=29;
            result=obj1->inputCheck(year,month,day);
            REQUIRE(result==1);
            
            year=2015,month=4,day=31;
            result=obj1->inputCheck(year,month,day);
            REQUIRE(result==1);
            
            year=2015,month=5,day=37;
            result=obj1->inputCheck(year,month,day);
            REQUIRE(result==1);
            
        }
    }
}

int main(int argc, char** argv) {
    // testing::InitGoogleTest(&argc,argv);
    // // //Runs all tests using Google Test.
    // // Test3 t;
    // // std::cout<<"111111111"<<t.add(1, 2)<<std::endl;
    // return RUN_ALL_TESTS();
    // hw11a::pattern(10,1);
    int result = Catch::Session().run( argc, argv );
    std::cout<<"enter number [1-8] to run , exit when enter number is [0]"<<std::endl;
    std::cout<<"1: run 1.1a"<<std::endl;
    std::cout<<"2: run 1.1b"<<std::endl;
    std::cout<<"3: run 1.2a"<<std::endl;
    std::cout<<"4: run 1.2b"<<std::endl;
    std::cout<<"5: run 1.3a"<<std::endl;
    std::cout<<"6: run 1.3b"<<std::endl;
    std::cout<<"7: run 1.4"<<std::endl;
    std::cout<<"8: run 1.5"<<std::endl;
    
    int command=-1;
    std::cin>>command;
    HW11a obj1;
    HW11b obj2;
    HW12a obj3;
    HW12b obj4;
    HW13a obj5;
    HW13b obj6;
    HW14 obj7;
    HW15 obj8;
    
    while(command!=0)
    {
        switch (command)
        {
            case 1:
                obj1.service();
                break;
            case 2:
                obj2.service();
                break;
            case 3:
                obj3.service();
                break;
            case 4:
                obj4.service();
                break;
            case 5:
                obj5.service();
                break;
            case 6:
                obj6.service();
                break;
            case 7:
                obj7.service();
                break;
            case 8:
                obj8.service();
                break;
            default:
                break;
        }
        command=-1;
        std::cout<<"============================================"<<std::endl;
        std::cout<<"enter number [1-8] to run , exit when enter number is [0]"<<std::endl;
        std::cout<<"1: run 1.1a"<<std::endl;
        std::cout<<"2: run 1.1b"<<std::endl;
        std::cout<<"3: run 1.2a"<<std::endl;
        std::cout<<"4: run 1.2b"<<std::endl;
        std::cout<<"5: run 1.3a"<<std::endl;
        std::cout<<"6: run 1.3b"<<std::endl;
        std::cout<<"7: run 1.4"<<std::endl;
        std::cout<<"8: run 1.5"<<std::endl;
        std::cin>>command;
    }
    std::cout<<"bye..."<<std::endl;
}
