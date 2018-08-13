#pragma once

#include <string>

#include "SceneManager.h"

enum eStringType
{
	TEXT,
	NAME,
	BRANCH,
	NEXT,
	QUIT,
	RANDOM = 7,
};


class sString
{
private:
	std::string m_Text;
	eStringType m_Type;
	int m_Line;
protected:
	int iPlayerSelect;
	char chText;

public:
	sString();
	~sString();
public:
	sString* nextNode;
public:
	void Init(int _line, eStringType _type, std::string _text);
	void Print();
	virtual void Process(int* nextBranch, eScene _type, bool* isQuit);

};

