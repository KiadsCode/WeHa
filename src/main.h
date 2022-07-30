#include <fstream>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <vector>
#include "Variable.h"
using namespace std;

std::string replace(std::string& source, char oldChar, char newChar) {
	std::string edited = source;
	for (int i = 0; i < edited.length(); i++)
	{
		if (edited[i] == oldChar)
			edited[i] = newChar;
	}
	return edited;
}

const std::string lx = "WeHa Language Ver - 0.2\n\n";

void Parser();

void ParsePrint(std::string& code);
void ParseInput(std::string& code);
void ParseNewVariable(std::string& code);