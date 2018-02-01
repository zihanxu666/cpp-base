#include "../included/src/testFileStream.hpp"

TestFileStream::TestFileStream(string path)
{
    this->file_path = path;
}

int TestFileStream::closeFile()
{
    this->file_in.close();
    this->file_out.close();
    return 1;
}

int TestFileStream::openFile()
{
    this->file_in.open(this->file_path, fstream::in);
    this->file_out.open(this->file_path, fstream::app);
    return 1;
}

string TestFileStream::readAll()
{
    cout << "readLine..." << this->file_in.is_open() << "   " << endl;
    string result;
    string tmp;
    this->file_in.seekg(0,fstream::beg);
    while (file_in>>tmp)
    {
        result.append(tmp).append("\n");
    }

    return result;
}

string TestFileStream::readLine()
{
    cout << "readLine..." << this->file_in.is_open() << "   " << endl;
    string result;
    char tmp;
    // this->fileOperator.get(tmp);
    // this->fileOperator>>result;
    cout << this->file_in.tellg() << "=======" << endl;
    while ((tmp = this->file_in.get()) != EOF)
    {
        if(tmp =='\n'){
            return result;
            // cout.put(tmp);
        }
        result+=tmp;
    }

    return result;
}
int TestFileStream::writeLine(string value)
{
    cout << "write..." << this->file_out.is_open() << "   " << endl;
    this->now=time(0);
    this->ltm = localtime(&now);
    string time_stamp;
    time_stamp.append(to_string(1900+ltm->tm_year))
    .append("-")
    .append(to_string(1+ltm->tm_mon))
    .append("-")
    .append(to_string(ltm->tm_mday))
    .append("_")
    .append(to_string(ltm->tm_hour))
    .append(":")
    .append(to_string(ltm->tm_min))
    .append(":")
    .append(to_string(ltm->tm_sec));
    this->file_out << value <<"["<<time_stamp<<"]"<< endl;
    this->file_out.flush();
    return 1;
}
