/*
	For details, visit www.hammadmukhtar.com
*/

//Structs

struct Board
{
	char piece;
	char color;
	int x;
	int y;
};

struct Box
{
	int x;
	int y;
};

struct Move
{
	Box from;
	Box to;
	char piece;
};