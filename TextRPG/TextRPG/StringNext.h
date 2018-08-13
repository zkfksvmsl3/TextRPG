#pragma once
#include "sString.h"
class StringNext
	: public sString
{
public:
	StringNext();
	~StringNext();
public:
	void Process(int* nextBranch, eScene type, bool* isQuit);
};

