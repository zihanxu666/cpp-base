#include "../included/src/hw2.1.hpp"


int HW21::service()
{
    std::string subseq;
    std::string seq;
    std::cin.clear();
    std::cout << "Please enter your subsequence:" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, subseq);
    std::cout << "Please enter your sequence:" << std::endl;
    std::cin.ignore();
    std::getline(std::cin, seq);

    if (FindSubSeq(subseq, seq))
    {
        std::cout << subseq << " is a subsequence of " << seq << "." << std::endl;
    }
    else
    {
        std::cout << subseq << " is not a subsequence of " << seq << "." << std::endl;
    }
    return 0;
}
bool HW21::FindSubSeq(const std::string &a, const std::string &b)
{
    int m = a.length();
    int n = b.length();

    if (m > n)
        return false;
    int j = 0;

    for (int i = 0; i < n && j < m; i++)
        if (a[j] == b[i])
            j++;

    return (j == m);
}
