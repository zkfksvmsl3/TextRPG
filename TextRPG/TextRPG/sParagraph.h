#pragma once
#include "SceneManager.h"

class sString;

class sParagraph
{
public:
	sString* _startNode;		// 
	sString* _currentNode;	// 현재 노드
public:
	sParagraph();
	~sParagraph();
public:
	void AddStringToParagraph(sString* _string);
	void Process(int* _branch,eScene _type ,bool* isQuit);
};

