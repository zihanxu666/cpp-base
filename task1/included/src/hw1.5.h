#include <iostream>
#include <string>
#include <cmath>

class HW15
{
private:
//begin define variables
std::string date;
 int monthArray[12] ={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //array of days in each month
public:


//begin define functions
int inputCheck(int, int, int);
int * getAllParam(std::string date);
int getParam(std::string date, int start);
int getParam(std::string date, int start, int length);
int service();
};