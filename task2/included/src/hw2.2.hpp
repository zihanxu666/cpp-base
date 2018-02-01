#include "hw.hpp"

class HW22:public HW
{
  public:
    HW22();
    HW22(std::vector<int> v1, std::vector<int> v2);

  private:
    std::vector<int> v1, v2;
    int v1_length, v2_length;
    std::stringstream in;
    const char * marks = ", ";

  public:
    void initialize(std::vector<int> v1, std::vector<int> v2);
    int service();
    std::vector<int> buildVector(std::string param);
    void merge(std::vector<int> &result, int v1_index, int v2_index);
};