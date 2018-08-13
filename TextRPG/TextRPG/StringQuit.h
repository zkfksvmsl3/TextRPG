#pragma once

#include "sString.h"

class StringQuit
	: public sString
{
public:
	StringQuit();
	~StringQuit();
public:
	void Process(int* nextBranch, eScene type, bool* isQuit);
};

