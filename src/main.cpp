#include "main.h"

#pragma region DEFFUN
const std::string scriptFormat = ".wh";
const std::string PrintFunction = "outline";
const std::string PrintVarFunction = "outvar";
const std::string InputFunction = "inline";
#pragma endregion

#pragma region CHARS
const char execFunction = '~';
const char modStart = '#';
const char commentKeySign = '$';
#pragma endregion

#pragma region KEYWORDS
const std::string moduleKeyWord = "module";
const std::string mfsKeyWord = "mfs";
const std::string moduleEndKeyWord = "endmod";
const std::string mfKeyWord = "mf";
const std::string funcKeyWord = "function";
const std::string endFuncKeyWord = "end";
const std::string varKeyWord = "var";
const std::string letKeyWord = "let";
#pragma endregion

vector<Variable> Variables;
vector<Function> Functions;
vector<Module> Modules;
vector<Variable> MVars;
vector<Function> MFunc;
vector<string> ScriptCode;
int LineNum = 0;
unsigned int targetMod = 0;

int main(int argc, char const* argv[])
{
    printf(lx.c_str());
    while (true)
    {
        char inputChar[1024];
        printf("Command: ");
        scanf("%s", inputChar);
        string preCommand = inputChar;
        if (preCommand == ".ex")
            exit(-1);
        if (preCommand == ".load") {
            printf("Script to open: ");
            scanf("%s", inputChar);
            preCommand = inputChar;
            preCommand += scriptFormat;
            ifstream ffrom;
            string lineCode = "";
            ffrom.open(preCommand);
            LineNum = 0;
            if (!ffrom.is_open())
                printf("\nfile error\n\n");
            else {
                while (!ffrom.eof())
                {
                    lineCode = "";
                    std::getline(ffrom, lineCode);
                    ScriptCode.push_back(lineCode);
                }
                while (LineNum != ScriptCode.size())
                {
                    Parser();
                    LineNum++;
                }
                
            }
            ffrom.close();
            ScriptCode.clear();
            Variables.clear();
            Functions.clear();
            Modules.clear();
            LineNum = 0;
        }
    }
    return 0;
}

Variable FindVar(std::string name){
    int VARNUM = 0;
    for (size_t i = 0; i < Variables.size(); ++i)
    {
        if (strcmp(Variables[i].name.c_str(), name.c_str()) == 0) {
            VARNUM = i;
        }   
    }
    return Variables.at(VARNUM);
}
int FindVarNUM(std::string name){
    int VARNUM = 0;
    for (size_t i = 0; i < Variables.size(); ++i)
    {
        if (strcmp(Variables[i].name.c_str(), name.c_str()) == 0) {
            VARNUM = i;
        }   
    }
    return VARNUM;
}

Function FindFunc(std::string name) {
    int VARNUM = 0;
    for (size_t i = 0; i < Functions.size(); ++i)
    {
        if (strcmp(Functions[i].name.c_str(), name.c_str()) == 0) {
            VARNUM = i;
        }
    }
    return Functions.at(VARNUM);
}
int FindFuncNum(std::string name) {
    int VARNUM = 0;
    for (size_t i = 0; i < Functions.size(); ++i)
    {
        if (strcmp(Functions[i].name.c_str(), name.c_str()) == 0) {
            VARNUM = i;
        }
    }
    return VARNUM;
}
Module FindMod(std::string name) {
    int VARNUM = 0;
    for (size_t i = 0; i < Modules.size(); ++i)
    {
        if (strcmp(Modules[i].name.c_str(), name.c_str()) == 0) {
            VARNUM = i;
        }
    }
    return Modules.at(VARNUM);
}
Function FindFuncInModule(std::string moduleName,std::string name) {
    Module mod = FindMod(moduleName);
    int VARNUM = 0;
    for (size_t i = 0; i < mod.funcs.size(); ++i)
    {
        if (strcmp(mod.funcs[i].name.c_str(), name.c_str()) == 0) {
            VARNUM = i;
        }
    }
    return mod.funcs.at(VARNUM);
}
int FindFuncNumInMod(std::string moduleName, std::string name) {
    Module mod = FindMod(moduleName);
    int VARNUM = 0;
    for (size_t i = 0; i < mod.funcs.size(); ++i)
    {
        if (strcmp(mod.funcs[i].name.c_str(), name.c_str()) == 0) {
            VARNUM = i;
        }
    }
    return VARNUM;
}


void Parser() {
    string Code = ScriptCode[LineNum];
    ParseMV(Code);
}


#pragma region PARSER
bool ParseFunction(std::string& code) {
    string valid = "";
    string name = "";
    int start = 0, endF = 1;
    int checkL = LineNum;

    for (size_t i = 0; i < code.length(); i++)
    {
        if (valid != funcKeyWord)
            valid += code[i];
    }

    if (valid != funcKeyWord)
        return false;
    if (valid == funcKeyWord)
        start = LineNum;

    for (size_t i = funcKeyWord.length(); code[i] != '('; i++)
    {
        if (code[i] != ' ' && code[i] != '(')
            name += code[i];
    }
    for (size_t i = start + 1; i < ScriptCode.size(); i++)
    {
        if (ScriptCode[i] == endFuncKeyWord.c_str()) {
            endF = i;
            LineNum = endF;
            Function func(name, start, endF);
            Functions.push_back(func);
            return true;
        }
    }
    return false;
}
bool ParseModule(std::string& code) {
    string valid = "";
    string name = "";
    int start = 0, endF = 1;
    int checkL = LineNum;

    for (size_t i = 0; i < code.length(); i++)
    {
        if (valid != moduleKeyWord)
            valid += code[i];
    }

    if (valid != moduleKeyWord)
        return false;
    if (valid == moduleKeyWord)
        start = LineNum;

    for (size_t i = moduleKeyWord.length(); code[i] != modStart; i++)
    {
        if (code[i] != ' ' && code[i] != '(')
            name += code[i];
    }
    for (size_t i = start + 1; i < ScriptCode.size(); i++)
    {
        if (ScriptCode[i] == moduleEndKeyWord.c_str()) {
            endF = i;
            LineNum = start + 1;
            Module modl(name, start, endF);
            while (LineNum != endF)
            {
                ParseM(ScriptCode.at(LineNum));
                LineNum++;
            }
            modl.vars = MVars;
            modl.funcs = MFunc;
            MFunc.clear();
            MVars.clear();
            Modules.push_back(modl);
            return true;
        }
    }
    return false;
}
void ParseMFS(std::string& code)
{
    string msg = "";
    string validCode = "";
    bool VALID = false;
    bool inBracket = false;
    bool nameOfModuleVAL = false;

    for (int i = 0; i < code.length(); i++)
    {
        if (validCode != mfsKeyWord)
            validCode += code[i];
    }
    if (validCode != mfsKeyWord)
        return;
    int ccp = 0;
    for (int i = mfsKeyWord.length(); i < code.length(); i++)
    {
        if (!nameOfModuleVAL) {
            if (code[i] == '(')
                inBracket = true;
            if (code[i] != '(' && code[i] != ')' && code[i] != '"' && inBracket)
                msg += code[i];
            if (code[i] == ')') {
                inBracket = false;
                ccp = i;
                nameOfModuleVAL = true;
            }
        }
    }
    int LineBefore = LineNum;
    string funcName = "";
    bool dotFinded = false;
    for (size_t i = ccp + 1; code[i] != ')'; i++)
    {
        if (code[i] == '.')
            dotFinded = true;
        if (code[i] != '.' && dotFinded && code[i] != '(')
            funcName += code[i];
    }
    if (funcName == "" || funcName == " ")
        return;
    else
        VALID = true;
    if (VALID) {
        Module mod = FindMod(msg);
        Function fun = mod.funcs.at(FindFuncNumInMod(msg, funcName));
        LineNum = fun.onLine + 1;

        while (LineNum != fun.endLine)
        {
            string Code = ScriptCode[LineNum];
            ParseMV(Code);
            LineNum++;
        }

        LineNum = LineBefore;

        VALID = false;
    }
}
void ParseAssignVar(std::string& code)
{
    string name = "";
    string value = "";
    string validCode = "";
    bool VALID = false;

    for (size_t i = 0; i < code.length(); i++)
    {
        if (validCode != letKeyWord)
            validCode += code[i];
    }

    if (validCode != letKeyWord)
        return;
    
    for (size_t i = letKeyWord.length() + 1; i < code.length() - 1; i++)
    {
        if (code[i] != ' ' || code[i] != '=' || code[i] != ':') 
            name += code[i];
        if (code[i] == ':' || code[i] == ' ')
            i = code.length() - 1;
    }

    if (name == " " || name == "")
        return;
    name = replace(name, ':', '\0');
    name = replace(name, ' ', '\0');
    int totL = letKeyWord.length() + 1 + name.length();
    Variable var = Variables.at(FindVarNUM(name));
    int mxh = totL;

    bool InStringBrackets = false;
    if (var.type == typeString)
    {
        for (size_t i = mxh; i < code.length(); i++)
        {
            if (code[i] == '\"')
                InStringBrackets = !InStringBrackets;
            if (code[i] != '\"' && code[i] != '=' && InStringBrackets)
            {
                value += code[i];
            }
        }
        Variables[FindVarNUM(name)].valueS = value;
        return;
    }
    
    if (var.type == typeNumber)
    {
        char msc;
        for (size_t i = mxh - 1; i < code.length(); i++)
        {
            if (code[i] == '=' || code[i] == '+' || code[i] == '-')
                msc = code[i];
            if (code[i] != '=' && code[i] != '+' && code[i] != '-' && code[i] != ' ')
            {
                value += code[i];
            }
        }
        int VARNUM = 0;
        for (size_t i = 0; i < Variables.size(); ++i)
        {
            if (strcmp(Variables[i].name.c_str(), name.c_str()) == 0) {
                VARNUM = i;
            }
        }
        if (msc == '=') {
            Variables[VARNUM].valueI = atoi(value.c_str());
            return;
        }
        if (msc == '+') {
            Variables[VARNUM].valueI += atoi(value.c_str());
            return;
        }
        if (msc == '-') {
            Variables[VARNUM].valueI -= atoi(value.c_str());
            return;
        }
        return;
    }
    if (var.type == typeBool)
    {
        for (size_t i = mxh; i < code.length(); i++)
        {
            if (code[i] != '=' && code[i] != ' ')
                value += code[i];
        }
        Variables[FindVarNUM(name)].valueB = value;
        return;
    }
}
void ParseVarOut(std::string& code) {
    string msg = "";
    string validCode = "";
    bool VALID = false;
    bool inBracket = false;

    for (int i = 0; i < code.length(); i++)
    {
        if (validCode != PrintVarFunction)
            validCode += code[i];
    }
    if (validCode != PrintVarFunction)
        return;
    for (int i = PrintVarFunction.length(); i < code.length(); i++)
    {
        if (code[i] == '(')
            inBracket = true;
        if (code[i] != '(' && code[i] != ')' && code[i] != '"')
            msg += code[i];
        if (code[i] == ')') {
            inBracket = false;
            VALID = true;
        }
    }
    if (VALID) {
        Variable varMAIN = FindVar(msg);
        if (varMAIN.type == typeString)
            printf(varMAIN.valueS.c_str());
        if (varMAIN.type == typeBool)
            printf(varMAIN.valueB.c_str());
        if (varMAIN.type == typeNumber)
            printf("%d", varMAIN.valueI);
        printf("\n");
        VALID = false;
    }
}
void ParseMV(std::string& Code) {
    if (Code[0] == commentKeySign || Code[0] == '\0')
        return;
    if (ParseModule(Code))
        return;
    if (ParseFunction(Code))
        return;
    ParseStartFunc(Code);
    ParseNewVariable(Code);
    ParseAssignVar(Code);
    ParseMFS(Code);
    ParseVarOut(Code);
    ParsePrint(Code);
    ParseInput(Code);
}
void ParseM(std::string& Code) {
    if (Code[0] == commentKeySign || Code[0] == '\0')
        return;
    if (ParseModule(Code))
        return;
    ParseModuleNV(Code);
    ParseModuleSF(Code);
    ParseMFS(Code);
}
void ParseModuleNV(std::string& code)
{
    string name = "";
    string type = "";
    string value = "";
    string validCode = "";
    bool VALID = false;

    for (size_t i = 0; i < code.length(); i++)
    {
        if (validCode != varKeyWord)
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
        for (size_t i = mxh; i < code.length(); i++)
        {
            if (code[i] == '\"')
                InStringBrackets = !InStringBrackets;
            if (code[i] != '\"' && code[i] != '=' && InStringBrackets)
            {
                value += code[i];
            }
        }
        Variable var(name, type, value);
        MVars.push_back(var);
        return;
    }
    if (type == typeNumber)
    {
        for (size_t i = mxh; i < code.length(); i++)
        {
            if (code[i] != '=' && code[i] != ' ')
            {
                value += code[i];
            }
        }
        Variable var(name, type, value);
        MVars.push_back(var);
        return;
    }
    if (type == typeBool)
    {
        for (size_t i = mxh; i < code.length(); i++)
        {
            if (code[i] != '=' && code[i] != ' ')
                value += code[i];
        }
        Variable var(name, type, value);
        MVars.push_back(var);
        return;
    }
}
void ParseModuleSF(std::string& code)
{
    string valid = "";
    string name = "";
    int start = 0, endF = 1;
    int checkL = LineNum;

    for (size_t i = 0; i < code.length(); i++)
    {
        if (valid != funcKeyWord)
            valid += code[i];
    }

    if (valid != funcKeyWord)
        return;
    if (valid == funcKeyWord)
        start = LineNum;

    for (size_t i = funcKeyWord.length(); code[i] != '('; i++)
    {
        if (code[i] != ' ' && code[i] != '(')
            name += code[i];
    }
    for (size_t i = start + 1; i < ScriptCode.size(); i++)
    {
        if (ScriptCode[i] == endFuncKeyWord.c_str()) {
            endF = i;
            LineNum = endF;
            Function func(name, start, endF);
            MFunc.push_back(func);
            return;
        }
    }
}
void ParseStartFunc(std::string& code)
{
    string msg = "";
    int LineBefore = LineNum;
    string validCode = "";
    bool VALID = false;
    bool inBracket = false;

    if (code[0] != execFunction)
        return;
    for (int i = 1; code[i] != '('; i++)
    {
        msg += code[i];
    }
    for (size_t i = msg.length() + 1; i < code.length(); i++)
    {
        if (code[i] == ')' && code[i - 1] == '(')
            VALID = true;
    }
    if (VALID) {

        LineNum = FindFunc(msg).onLine + 1;

        while (LineNum != FindFunc(msg).endLine)
        {
            string Code = ScriptCode[LineNum];
            ParseMV(Code);
            LineNum++;
        }

        LineNum = LineBefore;

        VALID = false;
    }
}
void ParsePrint(std::string& code) {
    string msg = "";
    string validCode = "";
    bool VALID = false;
    bool inBracket = false;
    bool inStringBrackets = false;

    for (int i = 0; i < code.length(); i++)
    {
        if (validCode != PrintFunction)
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

    for (size_t i = 0; i < code.length(); i++)
    {
        if (validCode != InputFunction)
            validCode += code[i];
    }
    if (validCode != InputFunction)
        return;
    for (size_t i = InputFunction.length(); i < code.length(); i++)
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

    for (size_t i = 0; i < code.length(); i++)
    {
        if (validCode != varKeyWord)
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
        for (size_t i = mxh; i < code.length(); i++)
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
        for (size_t i = mxh; i < code.length(); i++)
        {
            if (code[i] != '=' && code[i] != ' ')
            {
                value += code[i];
            }
        }
        Variable var(name, type, value);
        Variables.push_back(var);
        return;
    }
    if (type == typeBool)
    {
        for (size_t i = mxh; i < code.length(); i++)
        {
            if (code[i] != '=' && code[i] != ' ')
                value += code[i];
        }
        Variable var(name, type, value);
        Variables.push_back(var);
        return;
    }
}
#pragma endregion