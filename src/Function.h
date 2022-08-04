#pragma once
#include <string>
#include <iostream>

class Function
{
public:
	Function(std::string NAME, int LINE, int ENDL);
	~Function();
	int onLine;
	int endLine;
	std::string name;
private:

};

Function::Function(std::string NAME, int LINE, int ENDL)
{
	onLine = LINE;
	endLine = ENDL;
	name = NAME;
}

Function::~Function()
{
}