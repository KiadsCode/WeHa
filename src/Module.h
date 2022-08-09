#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Function.h"
#include "Variable.h"
using namespace std;
namespace weha
{
	class Module
	{
	public:
		vector<Variable> vars;
		vector<Function> funcs;
		bool Imported = false;
		Module(std::string NAME, int LINE, int ENDL);
		~Module();
		int onLine;
		int endLine;
		std::string name;
	};

	Module::Module(std::string NAME, int LINE, int ENDL)
	{
		onLine = LINE;
		endLine = ENDL;
		name = NAME;
	}

	Module::~Module()
	{
		onLine = 0;
		endLine = 1;
		name = "unnamed module";
	}
}