#include "main.h"

const std::string scriptFormat = ".wh";
const std::string PrintFunction = "outline";
const std::string InputFunction = "inline";

const std::string varKeyWord = "var";
vector<Variable> Variables;
vector<string> ScriptCode;
int LineNum = 0;

int main(int argc, char const* argv[])
{
    printf(lx.c_str());
    while (true)
    {
        char inputChar[1024];
        printf("Command: ");
        scanf("%s", inputChar);
        string preCommand = inputChar;
        if (preCommand == "ex")
            exit(-1);
        if (preCommand == "parse") {
            printf("Script to open: ");
            scanf("%s", inputChar);
            preCommand = inputChar;
            preCommand += scriptFormat;
            ifstream ffrom;
            string lineCode = "";
            ffrom.open(preCommand);
            if (!ffrom.is_open())
                printf("\nfile error\n\n");
            else {
                while (!ffrom.eof())
                {
                    lineCode = "";
                    std::getline(ffrom, lineCode);
                    ScriptCode.push_back(lineCode);
                    Parser();
                    LineNum++;
                }
            }
            ffrom.close();
            ScriptCode.clear();
            Variables.clear();
            LineNum = 0;
        }
    }
    return 0;
}

void Parser(){
    string Code = ScriptCode[LineNum];
    //ParseNewVariable(Code);
    ParsePrint(Code);
    ParseInput(Code);
}
void ParsePrint(std::string& code) {
    string msg = "";
    string validCode = "";
    bool VALID = false;
    bool inBracket = false;
    bool inStringBrackets = false;

    for (int i = 0; i < PrintFunction.length(); i++)
    {
        validCode += code[i];
    }
    if (validCode != PrintFunction)
        return;
    for (int i = PrintFunction.length(); i < code.length(); i++)
    {
        if (code[i] == '(')
            inBracket = true;
        if (code[i] == '"' && inBracket)
            inStringBrackets = !inStringBrackets;
        if (code[i] != ')' && code[i] != '"' && inStringBrackets)
            msg += code[i];
        if (code[i] == ')') {
            inBracket = false;
            inStringBrackets = false;
            VALID = true;
        }
    }
    if (VALID) {
        printf(msg.c_str());
        printf("\n");
        VALID = false;
    }
}
void ParseInput(std::string& code) {
    char Input[1024];
    string msg = "";
    string validCode = "";
    bool VALID = false;
    bool inBracket = false;
    bool inStringBrackets = false;

    for (int i = 0; i < InputFunction.length(); i++)
    {
        validCode += code[i];
    }
    if (validCode != InputFunction)
        return;
    for (int i = InputFunction.length(); i < code.length(); i++)
    {
        if (code[i] == '(')
            inBracket = true;
        if (code[i] == '"' && inBracket)
            inStringBrackets = !inStringBrackets;
        if (code[i] != ')' && code[i] != '"' && inStringBrackets)
            msg += code[i];
        if (code[i] == ')') {
            inBracket = false;
            inStringBrackets = false;
            VALID = true;
        }
    }
    if (VALID) {
        printf(msg.c_str());
        scanf("%s", Input);
        VALID = false;
    }
}

void ParseNewVariable(std::string& code) {
    string name = "";
    string type = "";
    string value = "";
    string validCode = "";
    bool VALID = false;

    for (size_t i = 0; i < varKeyWord.length(); i++)
    {
        validCode += code[i];
    }

    if (validCode != varKeyWord)
        return;
    
    for (size_t i = varKeyWord.length() + 1; i < code.length() - 1; i++)
    {
        if (code[i] != ' ' || code[i] != '=' || code[i] != ':') 
            name += code[i];
        if (code[i] == ':' || code[i] == ' ')
            i = code.length() - 1;
    }

    if (name == " " || name == "")
        return;
    name = replace(name, ':', '\0');
    int totL = varKeyWord.length() + 1 + name.length();

    for (size_t i = totL; code[i] != ' '; i++)
    {
        type += code[i];
    }

    int mxh = totL + type.length();

    bool InStringBrackets = false;
    if (type == typeString)
    {
        for (size_t i = mxh; code[i] != ';'; i++)
        {
            if (code[i] == '\"')
                InStringBrackets = !InStringBrackets;
            if (code[i] != '\"' && code[i] != '=' && InStringBrackets)
            {
                value += code[i];
            }
        }
        Variable var(name, type, value);
        Variables.push_back(var);
        return;
    }
    if (type == typeNumber)
    {
        for (size_t i = mxh; code[i] != ';'; i++)
        {
            if (code[i] != '=')
            {
                value += code[i];
            }
        }
        value = replace(value, ' ', '\0');
        Variable var(name, type, value);
        Variables.push_back(var);
        return;
    }
    if (type == typeBool)
    {
        for (size_t i = mxh; code[i] != ';'; i++)
        {
            if (code[i] != '=' && code[i] != ' ')
                value += code[i];
        }
        Variable var(name, type, value);
        Variables.push_back(var);
        return;
    }
}