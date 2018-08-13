#pragma once

#include "sString.h"	

class StringBranch
	:public sString
{
public:
	StringBranch();
	~StringBranch();
public:
	void Process(int* nextBranch, eScene type, bool* isQuit);

};

