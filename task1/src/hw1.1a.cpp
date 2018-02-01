#include "../included/src/hw1.1a.h"

#include <iostream>
/*
    auth by Zihan Xu
    create date: 2018-01-11 
    last update date: 2018-01-11    
*/


//begin function implement
/*
  The function return a pattern like
  1
  01
  101
  0101
  10101
  in this case, n=5 is the number of rows,
  each line is ended with '1'.
 */

int  HW11a::pattern(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j >= 0; j--)
        {
            if (j % 2 == 0)
            {
                std::cout << "1";
            }
            else
            {
                std::cout << "0";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}

int HW11a::service()
 {
     //begin define variable
     int rowNumber;
     std::cout << "Enter your row number please:" << std::endl;
     std::cin >> rowNumber;
     HW11a hw11a;
     hw11a.pattern(rowNumber);
     return 0;
 }

