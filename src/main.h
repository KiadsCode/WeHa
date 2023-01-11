#include <fstream>
#include <string>
#include <conio.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <conio.h>
#include "Variable.h"
#include "Module.h"
#include "Function.h"
#include "Utils/StringUtil.h"

using namespace std;
using namespace weha;

const string lx = "WeHa Ver - 1.0.3\n\n"; // Lang Version

void Parser(); // Main Parser

// Other Parsers
void ParseIf(string &code);
void ParsePrint(string &code);
void ParseImport(string &code);
bool ParseModule(string &code);
void ParseModuleSF(string &code);
void ParseModuleNV(string &code);
void ParseMP(string &code);
void ParseMFS(string &code);
void ParseStartFunc(string &code);
void ParseM(string &Code);
void ParseWhile(string& code);
void ParseMV(string &Code);
void ParseInput(string &code);
bool ParseFunction(string &code);
void ParseAssignVar(string &code);
void ParseNewVariable(string &code);