#include "../included/src/hw1.5.h"

/*

    auth by Zihan Xu
    create date: 2018-01-15 
    last update date: 2018-01-18
    objective: To output the day of the week (Monday – Sunday), given a date (a string such as 
               08-12-1985 in dd-mm-yyyy format) 
    method: Zeller‘s congruence
    
*/



//begin function implement
int HW15::service()
{
    std::cout << "Enter your date in 'dd-mm-yyyy' plz:" << std::endl;
    std::cin.clear();
    std::cin >> date;

    int *p = getAllParam(date);

    while (inputCheck(p[2], p[1], p[0]))
    {
        std::cout << "Enter your date in 'dd-mm-yyyy' please:" << std::endl;
        std::cin.clear();
        std::cin >> date;

        p = getAllParam(date);
    }

    int day = p[0];   //day
    int month = p[1]; //month
    int year = p[2];  //year

    /*
    the months in Zeller‘s congruence are from 3 to 14, 
    so we need to convert month 1 or 2 in current year into month 13 or 14 in previous year.
    i.e. 01-01-2000 is 01-13-1999
    */
    if (month < 3)
    {
        month = month + 12;
        year = year - 1;
    }

    int d = day;            //day
    int m = month;          //month
    int c = year / 100;     //century-1
    int y = year - c * 100; //year in the century

    std::cout << "{'obj_date': {'c':" << c << ", 'y':" << y << "," << std::endl;
    std::cout << "              'm':" << m << ", 'd':" << d << " }}" << std::endl;

    /*
    use Zeller's conguence and input parameters c,y,m,d to calculate the day of the week
    */
    int w = y + y / 4 + c / 4 - 2 * c + 13 * (m + 1) / 5 + d - 1;
    w = w >= 0 ? (w % 7) : (w % 7 + 7); //if w < 0, add 7 to the result

    std::string week[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    std::cout << date << " is " << week[w] << "." << std::endl;
    return 0;
}
/*
To get all parameters day(2-digit number), month(2-digit number) and year(4-digit number) from the entered string.
*/
int * HW15::getAllParam(std::string date)
{
    int * result=new int[3];
    result[0] = getParam(date, 0);
    result[1] = getParam(date, 3);
    result[2] = getParam(date, 6, 4);
    return result;
}

int HW15::getParam(std::string date, int start)//to get 2-digit number from the string date, given date and start.
{
    return getParam(date, start, 2);
}

int HW15::getParam(std::string date, int start, int length)//to get n (= length)-digit number from the string date, given date, start and length
{
    int result = 0;
    for (int i = 0; i < length; i++)
    {
        result = result * 10 + (date[start++] - '0');
    }
    return result;
}

/*
check the validility of the input date
*/

 int HW15::inputCheck(int year, int month, int day)
{
    if (month > 12) //check validility of month entered
    {
        std::cout << "The date is invalid, since the number of months of a year cannot exceed 12." << std::endl;
        return 1;
    }
    if (month == 2) //check validility of entered days in Feburary, i.e. 29 in leap year or 28 in common year
    {
        if ((year % 4 == 0 && year%100 != 0) || (year%100 == 0 && year % 400 == 0)) //leap year
        {
            if (day > 29)
            {
                std::cout << "The date is invalid, since the days of Feburary in a leap year cannot exceed 29." << std::endl;
                return 1;
            }
        }
        else //common year
        {
            if (day > 28)
            {
                std::cout << "The date is invalid, since the days of Feburary in a common year cannot exceed 28." << std::endl;
                return 1;
            }
        }
    }

    else if (day > monthArray[month-1]) //check validility of days entered except for Feburary
    {
        std::string monthName[] = {"January", "February", " March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        std::cout << "The date is invalid, since the days of " << monthName[month - 1] << " cannot exceed " << monthArray[month - 1] << "." << std::endl;
        return 1;
    }
    return 0;
} 
