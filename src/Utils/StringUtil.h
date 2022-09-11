#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

namespace weha{
    class StringUtil
    
    {
    private:
        /* data */
    public:
        static std::string replace(std::string &source, char oldChar, char newChar)
        {
            std::string edited = source;
            for (size_t i = 0; i < edited.length(); i++)
            {
                if (edited[i] == oldChar)
                    edited[i] = newChar;
            }
            return edited;
        }
        static std::string replace(std::string &source, int startPoint, char oldChar, char newChar)
        {
            std::string edited = source;
            for (size_t i = startPoint; i < edited.length(); i++)
            {
                if (edited[i] == oldChar)
                    edited[i] = newChar;
            }
            return edited;
        }
        static std::string replace(std::string &source, int startPoint, int endPoint, char oldChar, char newChar)
        {
            std::string edited = source;
            for (size_t i = startPoint; i < endPoint; i++)
            {
                if (edited[i] == oldChar)
                    edited[i] = newChar;
            }
            return edited;
        }
    };
    
}