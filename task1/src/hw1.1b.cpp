#include <iostream>
#include "../included/src/hw1.1b.h"
/*
    auth by Zihan Xu
    create date: 2018-01-11 
    last update date: 2018-01-11    
*/

//begin define function
// void pattern(int, int);

//begin function implement
int HW11b::service()
{
    //begin define variable
    int rowNumber;
    int temp = 1;

    std::cout << "Enter your row number please:" << std::endl;
    std::cin.clear();
    std::cin >> rowNumber;
    if (rowNumber % 2 == 0) //check if # of rows is an even number.
    {
        std::cout << "The row number " << rowNumber << " is not odd. " << std::endl;
        return 0;
    }
    HW11b obj;
    obj.pattern(rowNumber, temp);
    return 0;
}

/*
The function return a patter like
1
2 3 
4 5 6
7 8 9 10 
11 12 13 
14 15
16
in this case, x(# of rows) = 7, and it cannot be even number
*/
void  HW11b::pattern(int x, int temp)
{
    for (int i = 0; i <= x / 2; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            std::cout << temp++ << " ";
        }
        std::cout << std::endl;
    }

    for (int i = x / 2 - 1; i >= 0; i--)
    {
        for (int j = 0; j <= i; j++)
        {
            std::cout << temp++ << " ";
        }
        std::cout << std::endl;
    }
}
