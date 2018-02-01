#include <iostream>
#include <map>
#include <vector>



class HW21BackUp
{
  private:
    std::map<char,std::vector<int>> keywordMap;
  public:
    bool FindSubSeq(const std::string &a, const std::string &b);
    
    std::map<char,std::vector<int>>  buildMapFromString(const std::string &value);
};