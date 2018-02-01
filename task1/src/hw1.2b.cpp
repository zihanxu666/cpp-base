#include "../included/src/hw1.2b.h"

/*
    auth by Zihan Xu
    create date: 2018-01-11 
    last update date: 2018-01-11    
*/


//begin function implement
int HW12b::service()
{
    std::string str;
    std::cout << "Enter your string please:" << std::endl;
    getline(std::cin, str);


    reverse(str);
    std::cout <<"The reverse of your input is ["<< str <<"]"<< std::endl;
    return 0;
}

//return the reverse (use pass by reference)
std::string HW12b::reverse(std::string& str)
{
    int length = str.length();
    std::string temp = str;
    for (int i = 0; i < length; i++)
    {

        str[i] = temp[length - 1 - i];
    }
    return str;
}
