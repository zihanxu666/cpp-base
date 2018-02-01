#include "../included/src/hw2.2.hpp"

HW22::HW22()
{
}

HW22::HW22(std::vector<int> v1, std::vector<int> v2)
{
    initialize(v1, v2);
}

void HW22::initialize(std::vector<int> v1, std::vector<int> v2)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v1_length = v1.size();
    this->v2_length = v2.size();
}

std::vector<int> HW22::buildVector(std::string param)
{
    std::vector<int> result;

    in.str(param);
    char tmp[param.size()];
    strcpy(tmp, param.c_str());
    char *p = strtok(tmp, HW22::marks);

    while (p)
    {
        result.push_back(std::stoi(p));
        p = strtok(NULL, HW22::marks);
    }

    return result;
}

void HW22::merge(std::vector<int> &result, int v1_index, int v2_index)
{
    if (v1_index < v1_length && v2_index < v2_length)
    {
        if (v1[v1_index] < v2[v2_index])
        {
            result.push_back(v1[v1_index]);
            merge(result, v1_index + 1, v2_index);
        }
        else
        {
            result.push_back(v2[v2_index]);
            merge(result, v1_index, v2_index + 1);
        }
    }
    else
    {
        if (v1_index < v1_length)
        {
            result.push_back(v1[v1_index]);
            merge(result, v1_index + 1, v2_index);
        }
        if (v2_index < v2_length)
        {
            result.push_back(v2[v2_index]);
            merge(result, v1_index, v2_index + 1);
        }
    }
}

int HW22::service()
{
    std::vector<int> result;
    std::vector<int> tmp;

    std::vector<int> v1 = {2, 5, 5, 7, 10};
    std::vector<int> v2 = {1, 3, 5, 9, 11, 17, 20};

    std::cout << "default vector1 is:\n";

    for (auto val : v1)
    {
        std::cout << val << ",";
    }
    std::cout << std::endl;

    std::cout << "default vector2 is:\n";
    for (auto val : v2)
    {
        std::cout << val << ",";
    }
    std::cout << std::endl
              << std::endl;

    std::cout << "Do you want to change the vector1 and vector2 ?[y/n]\n";
    std::cin.clear();
    std::string inputString;
    std::cin.ignore();
    std::getline(std::cin, inputString);

    transform(inputString.begin(), inputString.end(), inputString.begin(), ::tolower);

    std::cout<<"--------\nthe inputString is: "<<inputString<<std::endl;
    if (inputString == "y" || inputString == "yes")
    {
        std::cout << "enter vector1:\n e.g.:1,2,3 or 1 2 3\n";
        std::cin.ignore();
        std::getline(std::cin, inputString);

        std::cout << "vector1[" << inputString << "]\n";
        v1 = buildVector(inputString);

        std::cout << "enter vector2:\n e.g.:1,2,3 or 1 2 3\n";
        std::cin.ignore();
        std::getline(std::cin, inputString);

        std::cout << "vector2[" << inputString << "]\n";

        v2 = buildVector(inputString);
    }

    initialize(v1, v2);

    merge(result, 0, 0);

    std::cout << "result is: \n";

    for (auto val : result)
    {
        std::cout << val << " ";
    }

    std::cout << std::endl;

    return 0;
}
