#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include "Variable.h"
#include "Function.h"

using namespace std;

std::string replace(std::string& source, char oldChar, char newChar) {
	std::string edited = source;
	for (size_t i = 0; i < edited.length(); i++)
	{
		if (edited[i] == oldChar)
			edited[i] = newChar;
	}
	return edited;
}

const std::string lx = "WeHa Language Ver - 0.3.1\n\n"; // Lang Version

void Parser(); // Main Parser

// Other Parsers
void ParseVarOut(std::string& code);
void ParseVarIn(std::string& code);
void ParsePrint(std::string& code);
void ParseStartFunc(std::string& code);
void ParseInput(std::string& code);
bool ParseFunction(std::string& code);
void ParseAssignVar(std::string& code);
void ParseNewVariable(std::string& code);