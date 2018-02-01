#include <fstream>
#include <iostream>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::to_string;
using std::fstream;
using std::ios;
class TestFileStream
{
  private:
    string file_path;
    fstream file_in;
    fstream file_out;
    time_t now;
    tm * ltm;

  public:
    TestFileStream(string path);
    int openFile();
    int closeFile();
    string readLine();
    string readAll();
    int writeLine(string value);
};