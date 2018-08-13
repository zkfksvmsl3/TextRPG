#pragma once


enum eConsoleColor
{
	BLACK,
	BLUE,
	REEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHTGRAY,
	DARKGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTMAGENTA,
	YELLOW,
	WHITE,

};


//struct Console;

class DoubleBuffering
{
private:
	//Console * con;
public:
	DoubleBuffering();
	~DoubleBuffering();
public:
	void CreateBuffer();
	void BufferWrite(int _x, int _y,const char* _string);
	void BufferWrite(int _x, int _y, const char* _string, eConsoleColor _fcolor, eConsoleColor _bcolor);

	void Flipping();
	void BufferClear();
	void Release();
	
	void GotoXY(int x, int y);
};