#include "main.h"

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
            LineNum = 0;
        }
    }
    return 0;
}

void Parser(){
    string Code = ScriptCode[LineNum];
    ParsePrint(Code);
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