#pragma once
#include "sString.h"

class StringText
	: public sString
{
public:
	StringText();
	~StringText();
public:
	void Process(int* nextBranch, eScene type,bool* isQuit);

};

