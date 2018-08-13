#include "sString.h"

#include <iostream>
#include <conio.h>

sString::sString()
{

}


sString::~sString()
{

}

void sString::Init(int _line, eStringType _type, std::string _text)
{
	m_Line = _line;
	m_Type = _type;
	m_Text = _text;
}

void sString::Print()
{
	std::cout << m_Text << std::endl;
	_getch();

}

void sString::Process(int* nextBranch, eScene _type, bool* isQuit)
{
}
