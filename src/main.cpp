#include "main.h"

#pragma region ENUMS
enum class AssignEnum
{
    PlusNum,
    PlusVarm,
    MinusNum,
    MinusVar,
    AssignStr,
    AssignStrVar,
    AssignBool,
    AssignBoolVar,
    AssignNum,
    AssignNumVar
};
enum class IFOperators
{
    IsEqual,
    IsntEqual,
    LowerThan,
    GreaterThan
};
#pragma endregion

#pragma region DEFFUN
const std::string importFunction = "import";
const std::string scriptFormat = ".wh";
const std::string PrintFunction = "print";
const std::string InputFunction = "input";
#pragma endregion

#pragma region CHARS
const char execFunction = '~';
const char commentKeySign = '$';
#pragma endregion

#pragma region KEYWORDS
const std::string moduleKeyWord = "module";
const std::string mfsKeyWord = "mfs";
const std::string mpKeyWord = "mp";
const std::string ifKeyWord = "if";
const std::string endIfKeyWord = "endif";
const std::string moduleEndKeyWord = "endmod";
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

int main(int argc, const char *argv[])
{
    if (argv[1] != nullptr)
    {
        ifstream ffrom;
        string lineCode = "";
        ffrom.open(argv[1]);

        LineNum = 0;
        if (!ffrom.is_open())
            printf("\nfile error\n\n");
        else
        {
            while (!ffrom.eof())
            {
                bool spaceTrime = true;
                int spaceEnd = 0;
                lineCode = "";
                std::getline(ffrom, lineCode);
                for (size_t i = 0; spaceTrime; i++)
                {
                    if (lineCode[i] != ' ')
                    {
                        spaceEnd = i;
                        spaceTrime = false;
                    }
                }
                lineCode = lineCode.substr(spaceEnd, lineCode.length());
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
        getch();
        exit(0);
    }

    printf(lx.c_str());
    while (true)
    {
        char inputChar[1024];
        printf("Command: ");
        scanf("%s", inputChar);
        string preCommand = inputChar;
        if (preCommand == "clrVar")
            Variables.clear();

        if (preCommand == "cls" || preCommand == "clear")
            system("cls");
        if (preCommand == ".load")
        {
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
            else
            {
                while (!ffrom.eof())
                {
                    bool spaceTrime = true;
                    int spaceEnd = 0;
                    lineCode = "";
                    std::getline(ffrom, lineCode);
                    for (size_t i = 0; spaceTrime; i++)
                    {
                        if (lineCode[i] != ' ')
                        {
                            spaceEnd = i;
                            spaceTrime = false;
                        }
                    }
                    lineCode = lineCode.substr(spaceEnd, lineCode.length());
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
        else
        {
            LineNum = 0;
            ScriptCode.push_back(preCommand);
            Parser();
        }
        ScriptCode.clear();
        LineNum = 0;
    }

    return 0;
}

#pragma region Finder
Variable FindVar(std::string name)
{
    int VARNUM = 0;
    for (size_t i = 0; i < Variables.size(); ++i)
    {
        if (strcmp(Variables[i].name.c_str(), name.c_str()) == 0)
        {
            VARNUM = i;
        }
    }
    return Variables.at(VARNUM);
}
int FindVarNUM(std::string name)
{
    int VARNUM = 0;
    for (size_t i = 0; i < Variables.size(); ++i)
    {
        if (strcmp(Variables[i].name.c_str(), name.c_str()) == 0)
        {
            VARNUM = i;
        }
    }
    return VARNUM;
}
Function FindFunc(std::string name)
{
    int VARNUM = 0;
    for (size_t i = 0; i < Functions.size(); ++i)
    {
        if (strcmp(Functions[i].name.c_str(), name.c_str()) == 0)
        {
            VARNUM = i;
        }
    }
    return Functions.at(VARNUM);
}
int FindFuncNum(std::string name)
{
    int VARNUM = 0;
    for (size_t i = 0; i < Functions.size(); ++i)
    {
        if (strcmp(Functions[i].name.c_str(), name.c_str()) == 0)
        {
            VARNUM = i;
        }
    }
    return VARNUM;
}
Module FindMod(std::string name)
{
    int VARNUM = 0;
    for (size_t i = 0; i < Modules.size(); ++i)
    {
        if (strcmp(Modules[i].name.c_str(), name.c_str()) == 0)
        {
            VARNUM = i;
        }
    }
    return Modules.at(VARNUM);
}
int FindModNum(std::string name)
{
    int VARNUM = 0;
    for (size_t i = 0; i < Modules.size(); ++i)
    {
        if (strcmp(Modules[i].name.c_str(), name.c_str()) == 0)
        {
            VARNUM = i;
        }
    }
    return VARNUM;
}
Function FindFuncInModule(std::string moduleName, std::string name)
{
    Module mod = FindMod(moduleName);
    int VARNUM = 0;
    for (size_t i = 0; i < mod.funcs.size(); ++i)
    {
        if (strcmp(mod.funcs[i].name.c_str(), name.c_str()) == 0)
        {
            VARNUM = i;
        }
    }
    return mod.funcs.at(VARNUM);
}
int FindFuncNumInMod(std::string moduleName, std::string name)
{
    Module mod = FindMod(moduleName);
    int VARNUM = 0;
    for (size_t i = 0; i < mod.funcs.size(); ++i)
    {
        if (strcmp(mod.funcs[i].name.c_str(), name.c_str()) == 0)
        {
            VARNUM = i;
        }
    }
    return VARNUM;
}
Variable FindVarInModule(std::string moduleName, std::string name)
{
    Module mod = FindMod(moduleName);
    int VARNUM = 0;
    for (size_t i = 0; i < mod.vars.size(); ++i)
    {
        if (strcmp(mod.vars[i].name.c_str(), name.c_str()) == 0)
        {
            VARNUM = i;
        }
    }
    return mod.vars.at(VARNUM);
}
int FindVarNumInMod(std::string moduleName, std::string name)
{
    Module mod = FindMod(moduleName);
    int VARNUM = 0;
    for (size_t i = 0; i < mod.vars.size(); ++i)
    {
        if (strcmp(mod.vars[i].name.c_str(), name.c_str()) == 0)
        {
            VARNUM = i;
        }
    }
    return VARNUM;
}

#pragma endregion

void Parser()
{
    string Code = ScriptCode[LineNum];
    ParseMV(Code);
}

#pragma region PARSER
bool ParseFunction(std::string &code)
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
        return false;
    if (valid == funcKeyWord)
        start = LineNum;

    for (size_t i = funcKeyWord.length(); code[i] != '('; i++)
    {
        if (code[i] != ' ' && code[i] != '(')
            name += code[i];
    }
    int lnForArgs = funcKeyWord.length() + name.length();
    for (size_t i = lnForArgs; code[i] != ')'; i++)
    {
    }
    for (size_t i = start + 1; i < ScriptCode.size(); i++)
    {
        if (ScriptCode[i] == endFuncKeyWord.c_str())
        {
            endF = i;
            LineNum = endF;
            Function func(name, start, endF);
            Functions.push_back(func);
            return true;
        }
    }
    return false;
}
bool ParseModule(std::string &code)
{
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

    for (size_t i = moduleKeyWord.length(); i < code.length(); i++)
    {
        if (code[i] != ' ' && code[i] != '(' && code[i] != '#')
            name += code[i];
    }
    for (size_t i = start + 1; i < ScriptCode.size(); i++)
    {
        if (ScriptCode[i] == moduleEndKeyWord.c_str())
        {
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
void ParseImport(std::string &code)
{
    string msg = "";
    string validCode = "";
    bool VALID = false;
    bool inBracket = false;

    for (size_t i = 0; i < code.length(); i++)
    {
        if (validCode != importFunction)
            validCode += code[i];
    }
    if (validCode != importFunction)
        return;
    for (size_t i = importFunction.length(); i < code.length(); i++)
    {
        if (code[i] == '(')
            inBracket = true;
        if (code[i] != '(' && code[i] != ')' && code[i] != '"')
            msg += code[i];
        if (code[i] == ')')
        {
            inBracket = false;
            VALID = true;
        }
    }
    if (VALID)
    {
        Module mod = Modules.at(FindModNum(msg));
        if (!mod.Imported)
        {
            for (size_t i = 0; i < mod.funcs.size(); i++)
            {
                Functions.push_back(mod.funcs.at(i));
            }
            for (size_t i = 0; i < mod.vars.size(); i++)
            {
                Variables.push_back(mod.vars.at(i));
            }
            Modules.at(FindModNum(msg)).Imported = true;
            return;
        }
        VALID = false;
    }
}
void ParseMFS(std::string &code)
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
        if (!nameOfModuleVAL)
        {
            if (code[i] == '(')
                inBracket = true;
            if (code[i] != '(' && code[i] != ')' && code[i] != '"' && inBracket)
                msg += code[i];
            if (code[i] == ')')
            {
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
    if (VALID)
    {
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
void ParseMP(std::string &code)
{

    string msg = "";
    string validCode = "";
    bool VALID = false;
    bool inBracket = false;
    bool nameOfModuleVAL = false;

    for (int i = 0; i < code.length(); i++)
    {
        if (validCode != mpKeyWord)
            validCode += code[i];
    }
    if (validCode != mpKeyWord)
        return;
    int ccp = 0;
    for (int i = mpKeyWord.length(); i < code.length(); i++)
    {
        if (!nameOfModuleVAL)
        {
            if (code[i] == '(')
                inBracket = true;
            if (code[i] != '(' && code[i] != ')' && code[i] != '"' && inBracket)
                msg += code[i];
            if (code[i] == ')')
            {
                inBracket = false;
                ccp = i;
                nameOfModuleVAL = true;
            }
        }
    }
    int LineBefore = LineNum;
    bool dotFinded = false;
    bool InArg = false;
    string funcArg = "";
    for (size_t i = ccp + 1; code[i] != ')'; i++)
    {
        if (code[i] == '.')
            dotFinded = true;
        if (code[i] != '.' && dotFinded && code[i] != '(')
            funcArg += code[i];
    }

    if (funcArg == "" || funcArg == " ")
        return;
    else
        VALID = true;
    if (VALID)
    {
        Variable var = FindVarInModule(msg, funcArg);
        if (var.type == typeBool)
        {
            printf("%s", var.valueB.c_str());
            printf("\n");
            return;
        }
        if (var.type == typeString)
        {
            printf("%s", var.valueS.c_str());
            printf("\n");
            return;
        }
        if (var.type == typeNumber)
        {
            printf("%d", var.valueI);
            printf("\n");
            return;
        }
        VALID = false;
    }
}
void ParseAssignVar(std::string &code)
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
    name = StringUtil::replace(name, ':', '\0');
    name = StringUtil::replace(name, ' ', '\0');
    int totL = letKeyWord.length() + 1 + name.length();
    Variable var = Variables.at(FindVarNUM(name));
    int mxh = totL;

    bool InStringBrackets = false;
    AssignEnum assignType{};
    if (var.type == typeString)
    {
        bool IsAESelected = false;
        for (size_t i = mxh; i < code.length(); i++)
        {
            if (code[i] == '=' && code[i + 1] == '=' && !IsAESelected)
            {
                assignType = AssignEnum::AssignStrVar;
                IsAESelected = true;
            }
            if (code[i] == '=' && code[i + 1] == '=' && !IsAESelected)
            {
                assignType = AssignEnum::AssignStrVar;
                IsAESelected = true;
            }
            if (code[i] == '\"')
                InStringBrackets = !InStringBrackets;
            if (code[i] != '\"' && code[i] != '=' && InStringBrackets && assignType == AssignEnum::AssignStr)
            {
                value += code[i];
            }
            if (code[i] != '\"' && code[i] != '=' && code[i] != ' ' && assignType == AssignEnum::AssignStrVar)
            {
                value += code[i];
            }
        }
        if (assignType == AssignEnum::AssignStr)
        {
            Variables[FindVarNUM(name)].valueS = value;
            return;
        }
        if (assignType == AssignEnum::AssignStrVar)
        {
            Variables[FindVarNUM(name)].valueS = FindVar(value).valueS;
            return;
        }
        return;
    }

    if (var.type == typeNumber)
    {
        bool IsAESelected = false;
        for (size_t i = mxh; i < code.length(); i++)
        {
            if (code[i] == '+' && code[i + 1] == '=' && !IsAESelected)
            {
                assignType = AssignEnum::PlusVarm;
                IsAESelected = true;
            }
            if (code[i] == '+' && code[i + 1] == ' ' && !IsAESelected)
            {
                assignType = AssignEnum::PlusNum;
                IsAESelected = true;
            }
            if (code[i] == '-' && code[i + 1] == '=' && !IsAESelected)
            {
                assignType = AssignEnum::MinusVar;
                IsAESelected = true;
            }
            if (code[i] == '-' && code[i + 1] == ' ' && !IsAESelected)
            {
                assignType = AssignEnum::MinusNum;
                IsAESelected = true;
            }
            if (code[i] == '=' && code[i + 1] == '=' && !IsAESelected)
            {
                assignType = AssignEnum::AssignNumVar;
                IsAESelected = true;
            }
            if (code[i] == '=' && code[i + 1] == ' ' && !IsAESelected)
            {
                assignType = AssignEnum::AssignNumVar;
                IsAESelected = true;
            }
            if (code[i] != '=' && code[i] != '+' && code[i] != '-' && code[i] != ' ')
            {
                value += code[i];
            }
        }
        int VARNUM = 0;
        for (size_t i = 0; i < Variables.size(); ++i)
        {
            if (strcmp(Variables[i].name.c_str(), name.c_str()) == 0)
            {
                VARNUM = i;
            }
        }
        if (assignType == AssignEnum::AssignNum)
        {
            Variables[VARNUM].valueI = atoi(value.c_str());
            return;
        }
        if (assignType == AssignEnum::AssignNumVar)
        {
            Variables[VARNUM].valueI = FindVar(value).valueI;
            return;
        }
        if (assignType == AssignEnum::PlusNum)
        {
            Variables[VARNUM].valueI += atoi(value.c_str());
            return;
        }
        if (assignType == AssignEnum::PlusVarm)
        {
            Variables[VARNUM].valueI += FindVar(value).valueI;
            return;
        }
        if (assignType == AssignEnum::MinusNum)
        {
            Variables[VARNUM].valueI -= atoi(value.c_str());
            return;
        }
        if (assignType == AssignEnum::MinusVar)
        {
            Variables[VARNUM].valueI -= FindVar(value).valueI;
            return;
        }
        return;
    }
    if (var.type == typeBool)
    {
        bool IsAESelected = false;
        for (size_t i = mxh; i < code.length(); i++)
        {
            if (code[i] == '=' && code[i + 1] == '=' && !IsAESelected)
            {
                assignType = AssignEnum::AssignBoolVar;
                IsAESelected = true;
            }
            if (code[i] == '=' && code[i + 1] == ' ' && !IsAESelected)
            {
                assignType = AssignEnum::AssignBool;
                IsAESelected = true;
            }
            if (code[i] != '=' && code[i] != ' ')
                value += code[i];
        }
        if (assignType == AssignEnum::AssignBool)
        {
            Variables[FindVarNUM(name)].valueB = value;
            return;
        }
        if (assignType == AssignEnum::AssignBoolVar)
        {
            Variables[FindVarNUM(name)].valueB = FindVar(value).valueB;
            return;
        }
    }
}
void ParseMV(std::string &Code)
{
    if (Code[0] == commentKeySign || Code[0] == '\0')
        return;
    if (ParseModule(Code))
        return;
    if (ParseFunction(Code))
        return;
    ParsePrint(Code);
    ParseStartFunc(Code);
    ParseNewVariable(Code);
    ParseAssignVar(Code);
    ParseImport(Code);
    ParseMFS(Code);
    ParseMP(Code);
    ParseInput(Code);
    ParseIf(Code);
}
void ParseM(std::string &Code)
{
    if (Code[0] == commentKeySign || Code[0] == '\0')
        return;
    if (ParseModule(Code))
        return;
    ParseModuleNV(Code);
    ParseModuleSF(Code);
    ParseMFS(Code);
}
void ParseModuleNV(std::string &code)
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
    name = StringUtil::replace(name, ':', '\0');
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
void ParseModuleSF(std::string &code)
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
        if (ScriptCode[i] == endFuncKeyWord.c_str())
        {
            endF = i;
            LineNum = endF;
            Function func(name, start, endF);
            MFunc.push_back(func);
            return;
        }
    }
}
void ParseStartFunc(std::string &code)
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
    if (VALID)
    {

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
void ParsePrint(std::string &code)
{
    string msg = "";
    string validCode = "";
    bool VALID = false;
    bool inBracket = false;
    bool inStringBrackets = false;
    bool isVariable = false;

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
        if (code[i] != ')' && code[i] != '"' && inStringBrackets && !isVariable)
            msg += code[i];
        if (code[i] != ')' && code[i] != '"' && !inStringBrackets && isVariable)
            msg += code[i];

        if (code[i] != '(' && code[i] != ')' && code[i] != '\"' && !inStringBrackets) {
            isVariable = true;
        }

        if (code[i] == ')')
        {
            inBracket = false;
            inStringBrackets = false;
            VALID = true;
        }
    }
    if (VALID)
    {
        if (!isVariable) {
            printf(msg.c_str());
            printf("\n");
        }
        if (isVariable) {
            Variable var = FindVar(msg);
            if (var.type == typeNumber) {
                printf("%d\n", var.valueI);
                return;
            }
            if (var.type == typeBool) {
                printf("%b\n", var.valueB);
                return;
            }
            if (var.type == typeString) {
                printf("%s\n", var.valueS);
                return;
            }
        }
        VALID = false;
    }
}
void ParseInput(std::string &code)
{
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
        if (code[i] == ')')
        {
            inBracket = false;
            inStringBrackets = false;
            VALID = true;
        }
    }
    if (VALID)
    {
        printf(msg.c_str());
        scanf("%s", Input);
        VALID = false;
    }
}
void ParseNewVariable(std::string &code)
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
    name = StringUtil::replace(name, ':', '\0');
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
void ParseIf(std::string& code)
{
    string valid = "";
    string sm = "";
    string Aname = "";
    string Bname = "";
    int start = 0, endF = 1;
    bool operatorSelected = false;
    IFOperators finoperator;
    int checkL = LineNum;

    for (size_t i = 0; i < code.length(); i++)
    {
        if (valid != ifKeyWord && code[i] != ' ' && code[i] != '\t')
            valid += code[i];
    }

    if (valid != ifKeyWord)
        return;
    if (valid == ifKeyWord)
        start = LineNum;

    for (size_t i = ifKeyWord.length() + 1; code[i] != ' '; i++)
    {
        if (code[i] != ' ' && code[i] != '=' && code[i] != '!' && code[i] != '<' && code[i] != '>')
            Aname += code[i];
    }
    for (size_t i = ifKeyWord.length() + Aname.length() + 2; code[i] != ' '; i++)
    {
        if (code[i] == '=' && code[i + 1] == '=' && !operatorSelected) {
            finoperator = IFOperators::IsEqual;
            operatorSelected = true;
        }
        if (code[i] == '!' && code[i + 1] == '=' && !operatorSelected) {
            finoperator = IFOperators::IsntEqual;
            operatorSelected = true;
        }
        if (code[i] == '>' && code[i + 1] == ' ' && !operatorSelected) {
            finoperator = IFOperators::GreaterThan;
            operatorSelected = true;
        }
        if (code[i] == '<' && code[i + 1] == ' ' && !operatorSelected) {
            finoperator = IFOperators::LowerThan;
            operatorSelected = true;
        }
    }
    for (size_t i = ifKeyWord.length() + Aname.length() + 1; i < code.length(); i++)
    {
        if (code[i] != ' ' && code[i] != '=' && code[i] != '!' && code[i] != '<' && code[i] != '>')
            Bname += code[i];
    }
    bool nTT = true;
    for (size_t i = start + 1; i < ScriptCode.size(); i++)
    {
        nTT = true;
        int startTrim = 0;
        string ccode = ScriptCode[i];
        for (size_t i = 0; nTT; i++)
        {
            if (ccode[i] != '\t') {
                startTrim = i;
                nTT = false;
            }
        }
        ccode = ccode.substr(startTrim, ScriptCode[i].length());
        if (ccode == endIfKeyWord.c_str())
        {
            endF = i;
            LineNum = start + 1;
            break;
        }
    }
    bool needToParse = false;
    Variable varA = FindVar(Aname);
    Variable varB = FindVar(Bname);
    bool needToTrim = true;
    switch (finoperator)
    {
    case IFOperators::IsEqual:
        if (varA.type == typeString && varB.type == typeString) {
            if (varA.valueS == varB.valueS) {
                needToParse = true;
                break;
            }
        }
        if (varA.type == typeNumber && varB.type == typeNumber) {
            if (varA.valueI == varB.valueI) {
                needToParse = true;
                break;
            }
        }
        if (varA.type == typeBool && varB.type == typeBool) {
            if (varA.valueB == varB.valueB) {
                needToParse = true;
                break;
            }
        }
        break;
    case IFOperators::IsntEqual:
        if (varA.type == typeString && varB.type == typeString) {
            if (varA.valueS != varB.valueS) {
                needToParse = true;
                break;
            }
        }
        if (varA.type == typeNumber && varB.type == typeNumber) {
            if (varA.valueI != varB.valueI) {
                needToParse = true;
                break;
            }
        }
        if (varA.type == typeBool && varB.type == typeBool) {
            if (varA.valueB != varB.valueB) {
                needToParse = true;
                break;
            }
        }
        break;
    case IFOperators::GreaterThan:
        if (varA.type == typeNumber && varB.type == typeNumber) {
            if (varA.valueI > varB.valueI) {
                needToParse = true;
                break;
            }
        }
        break;
    case IFOperators::LowerThan:
        if (varA.type == typeNumber && varB.type == typeNumber) {
            if (varA.valueI < varB.valueI) {
                needToParse = true;
                break;
            }
        }
        break;
    }
    if (needToParse) {
        for (size_t i = start + 1; i != endF;)
        {
            int startTrim = 0;
            string ccode = ScriptCode[i];
            for (size_t i = 0; needToTrim; i++)
            {
                if (ccode[i] != '\t') {
                    startTrim = i;
                    needToTrim = false;
                }
            }
            ccode = ccode.substr(startTrim, ccode.length());
            ParseMV(ccode);
            i++;
            if (i == endF) {
                needToParse = false;
                LineNum = endF;
                break;
            }
        }
        needToParse = false;
        return;
    }
    else {
        return;
    }
}
#pragma endregion