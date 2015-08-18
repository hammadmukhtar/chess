/*
	For details, visit www.hammadmukhtar.com
*/

#include <Windows.h>
#include <cstdlib>
#include <process.h>
#include <ctime>

void setColor(int c)
{
	WORD wAttributes = ( c | 58);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wAttributes);

}

void setCursor(int x,int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

char readFrom(int x, int y)
{
	char* str = new char;
	DWORD nLength = 1;
	COORD readCoord;
	readCoord.X = x; readCoord.Y = y;
	DWORD num_read=0;
	ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (LPTSTR)str, nLength, readCoord,(LPDWORD)&num_read);
	return *str;
}


