#include "sParagraph.h"

#include "sString.h"


sParagraph::sParagraph()
{
	_currentNode = 0;
}


sParagraph::~sParagraph()
{
}

void sParagraph::AddStringToParagraph(sString* str)
{
	if (NULL == _currentNode)
	{
		_currentNode = str;
		str->nextNode = NULL;
		_startNode = str;
	}
	else
	{
		_currentNode->nextNode = str;
		str->nextNode = NULL;
		_currentNode = str;
	}
}

void sParagraph::Process(int* _branch,eScene _type, bool* isQuit)
{
	int selectBranch = *_branch;
	
	_currentNode = _startNode;

	while (NULL != _currentNode)
	{
		_currentNode->Process(_branch,_type ,isQuit);
		_currentNode = _currentNode->nextNode;
	}
}
