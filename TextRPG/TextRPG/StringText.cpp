#include "StringText.h"

#include <conio.h>

StringText::StringText()
{
}


StringText::~StringText()
{
}

void StringText::Process(int * nextBranch, eScene type,bool * isQuit)
{
	Print();
	_getch();

}
