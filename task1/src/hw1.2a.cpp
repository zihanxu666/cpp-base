#include "../included/src/hw1.2a.h"
/*
    auth by Zihan Xu
    create date: 2018-01-11 
    last update date: 2018-01-11    
*/



//begin function implement
int HW12a::service()
{
    std::string str;
    std::cout << "Enter your string please:" << std::endl;
    getline(std::cin, str);
	

    checkPalindrome(str);
    return 0;
}

//check if the input is a palindrome or not (use pass by constant reference)
void HW12a::checkPalindrome(const std::string& str)
{
    int length = str.length();
    int median = length % 2 != 0 ? length / 2 : length / 2 - 1;
    bool palindrome = true;
    for (int i = 0; i < median; i++)
    {

        if (str[i] != str[length - 1 - i])
        {
            palindrome = false;
            std::cout << "The given string [" << str << "] is not a palindrome." << std::endl;
            return;
        }
    }
    if (palindrome == true)
        std::cout << "The given string [" << str << "] is a palindrome." << std::endl;

    return;
}