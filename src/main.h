#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "Variable.h"
#include "Module.h"
#include "Function.h"

using namespace std;

std::string replace(std::string &source, char oldChar, char newChar)
{
	std::string edited = source;
	for (size_t i = 0; i < edited.length(); i++)
	{
		if (edited[i] == oldChar)
			edited[i] = newChar;
	}
	return edited;
}

const std::string lx = "WeHa Lang Ver - 0.6.8\n\n"; // Lang Version

void Parser(); // Main Parser

// Other Parsers
void ParseVarOut(std::string &code);
void ParsePrint(std::string &code);
void ParseImport(std::string &code);
bool ParseModule(std::string &code);
void ParseModuleSF(std::string &code);
void ParseModuleNV(std::string &code);
void ParseMP(std::string &code);
void ParseMFS(std::string &code);
void ParseStartFunc(std::string &code);
void ParseM(std::string &Code);
void ParseMV(std::string &Code);
void ParseInput(std::string &code);
bool ParseFunction(std::string &code);
void ParseAssignVar(std::string &code);
void ParseNewVariable(std::string &code);