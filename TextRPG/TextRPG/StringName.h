#pragma once

#include "sString.h"
#include <string>


class StringName
	:public sString
{
private:
	std::string sName;
public:
	StringName();
	~StringName();
public:
	void Process(int* nextBranch, eScene type,bool* isQuit);

};

