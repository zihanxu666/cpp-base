#include "../included/src/hw2.1_backup.hpp"

bool HW21BackUp::FindSubSeq(const std::string &a, const std::string &b)
{
    this->keywordMap = buildMapFromString(a);

    std::vector<int> lastIndex;

    int idx;

    for (char keyword : b)
    {

        auto mapIterator = this->keywordMap.find(keyword);
        bool haveKeyWord = false;

        auto iter = this->keywordMap.begin();

        if (mapIterator == this->keywordMap.end())
        {
            return false;
        }

        if (!lastIndex.empty())
        {
            for (auto val : lastIndex)
            {
                for (auto target : mapIterator->second)
                    if (val + 1 == target)
                    {
                        haveKeyWord = true;
                        break;
                    }
            }
        }
        else
        {
            haveKeyWord = true;
        }

        if (!haveKeyWord)
        {
            return false;
        }

        lastIndex = mapIterator->second;

        idx++;

        continue;
    }

    return true;
}

std::map<char, std::vector<int>> HW21BackUp::buildMapFromString(const std::string &value)
{
    std::map<char, std::vector<int>> result;

    int length = value.length();

    std::vector<int> charIndexVector;

    for (int i = 0; i < length; i++)
    {
        auto iter = result.find(value[i]);

        if (iter != result.end())
        {
            charIndexVector = iter->second;
        }

        charIndexVector.push_back(i);
        result[value[i]] = charIndexVector;

        charIndexVector.clear();
    }
    return result;
}







