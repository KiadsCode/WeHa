#pragma once
#include <string>
#include <iostream>

const std::string typeNumber = "Number";
const std::string typeString = "String";
const std::string typeBool = "Boolean";
const std::string boolVarA = "true";
const std::string boolVarB = "false";
const std::string null = "nil";

namespace weha
{
    class Variable
    {
    public:
        int valueI;
        std::string name;
        std::string type;
        std::string valueS;
        std::string valueB;
        Variable(std::string NAME, std::string TYPE, std::string VALUE);
        ~Variable();
    };

    Variable::Variable(std::string NAME, std::string TYPE, std::string VALUE)
    {
        name = NAME;
        type = TYPE;
        valueS = VALUE;
        if (type == typeNumber)
        {
            if (valueS == null)
            {
                valueS = "0";
            }
            try
            {
                valueI = atoi(valueS.c_str());
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        if (type == typeBool)
        {
            if (valueS == null)
                valueS = boolVarB;
            if (valueS == boolVarA || valueS == boolVarB)
            {
                valueB = valueS;
            }
        }
    }
    Variable::~Variable()
    {
    }
}