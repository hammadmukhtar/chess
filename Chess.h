/*
	For details, visit www.hammadmukhtar.com
*/

#ifndef CHESS_H
#define CHESS_H

#include <iostream>
#include "consoleSettings.h"
#include "List.h"
#include "List.cpp"


using namespace std;

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
	bool operator==(Box b)
	{
		if(this->x == b.x && this->y == b.y)
			return true;
		else 
			return false;
	}
};

struct Move
{
	Box from;
	Box to;
	char piece;
};

Move startMoves[2];
List<Move> OpponentMoves;
List<Move> moves;
List<Move> KingMoves;
List<Move> QueenMoves;
List<Move> BishopMoves;
List<Move> KnightMoves;
List<Move> RookMoves;
List<Move> PawnMoves;
List<Box> UnderAttackPieces;
List<Move> tempMoves;
Node<Move> * temp;

class Chess
{
private:
	Board board[8][8];

public:
	Chess()
	{
		char a[8] = {'R', 'k', 'B', 'Q' , 'K' , 'B', 'k' , 'R'};
		
		for(int i = 0, y = 2 ; i < 8 ; i++ , y+=2)
			for(int j = 0 , x = 10 ; j < 8 ; j++ , x+=4)
			{
				this->board[i][j].piece = ' ';
				this->board[i][j].x = x;
				this->board[i][j].y = y;
			}

		for(int i = 0 ; i < 8 ; i++)
		{	
			this->board[0][i].piece = a[i];
			this->board[0][i].color = 'B';
		}

		for(int i = 0 ; i < 8 ; i++)
		{	
			this->board[7][i].piece = a[i];
			this->board[7][i].color = 'W';
		}

		for(int i = 0 ; i < 8 ; i++)
		{
			this->board[1][i].piece = 'P';
			this->board[1][i].color = 'B';
			this->board[6][i].piece = 'P';
			this->board[6][i].color = 'W';
		}
		
	}

	void displayBoard()
	{
		int c;
		cout << endl;
		for(int i = 0 ; i < 8 ; i++)
		{
			setColor(3);
			cout << "\t";
			for(int k = 0 ; k < 8 ; k++)
				cout << "|===" ;
			cout << "|" << endl;
			if ( i == 0 || i == 1)
				c = 54;
			else if ( i == 6 || i == 7)
				c = 5;
			else
				c = 3;
			cout << "\t";
			for(int j = 0 ; j < 8 ; j++)
			{	
				setColor(3);	cout << "| ";	setColor(c);	 cout << this->board[i][j].piece << " ";
			}
			setColor(3);	cout << "|" << endl;
		}
		cout << "\t";
		for(int k = 0 ; k < 8 ; k++)
			cout << "|===" ;
		cout << "|" << endl;

		char player[40];
		setCursor(48,3);
		cout << "Enter Your Name Here: ";
		setCursor(48,4);
		cin.getline(player,40);
		player[13] = '\0';
		setCursor(48,4);
		cout << player << "'s Captured Pieces:";
		setCursor(48,3);
		cout << "                        ";

		setCursor(48,8);
		cout << "Computer's Captured Pieces:";

		setCursor(18,0);
		cout << "Computer";
		setCursor(18,18);
		cout << player;
		setCursor(18,20);
		cout << "P L A Y !";

		setCursor(9,22);
		cout << "By H A M M A D  M U K H T A R";
	}

	void move(Box from, Box to)
	{
		Box f; Box t;
		f.y = ((from.x - 6)/4) - 1;
		f.x = (from.y/2) - 1;
	
		t.y = ((to.x - 6)/4) - 1;
		t.x = (to.y/2) - 1;

		int color;
		if(board[f.x][f.y].color == 'W')
			color = 5;
		else
			color = 54;

		if(isLegal(f,t,'W','B') && board[f.x][f.y].color != 'B')
		{
			if(board[t.x][t.y].color == 'B')
			{
				static int x = 48;
				setCursor(x,9);
				setColor(54);
				cout << board[t.x][t.y].piece << " ";
				x+=2;
			}

			board[t.x][t.y].piece = board[f.x][f.y].piece;
			board[t.x][t.y].color = 'W';
			board[f.x][f.y].piece = ' ';
			board[f.x][f.y].color = 0;

			setCursor(from.x,from.y);
			cout << ' ' ;
			setCursor(board[t.x][t.y].x,board[t.x][t.y].y);
			setColor(5);
			cout <<  board[t.x][t.y].piece ;

			if(t.x == 0 && board[t.x][t.y].piece == 'P' )
			{
				setCursor(board[t.x][t.y].x,board[t.x][t.y].y);
				setColor(9);
				cout <<  board[t.x][t.y].piece ;

				char c;
				setCursor(48,13);
				setColor(54);

				cout << "Choose Role for selected Pawn:";
				setCursor(48,14);
				cout << " Q | B | R | k : ";

				setColor(5);
				setCursor(65,14);
				do
				{
					cout << ' ';
					setCursor(65,14);
					cin.get(c);

					if(c == 'k' || c == 'K')
						c = tolower(c);
					else
						c = toupper(c);

				}while( c != 'Q' && c != 'B' && c != 'R' && c != 'k');

				setCursor(board[t.x][t.y].x,board[t.x][t.y].y);
				setColor(5);

				board[t.x][t.y].piece = c;
				cout << board[t.x][t.y].piece;

				setCursor(48,13);

				cout << "                               ";
				setCursor(48,14);
				cout << "                      ";
				
			}

			Sleep(1000);
			computersMove();
		}
		else
		{
			setColor(54);
			setCursor(3,20);
			cout << "NOTE: Illegal Move! Select the white piece ";
			setCursor(from.x,from.y);
			setColor(color);
			cout << board[f.x][f.y].piece ;
		}
	}

	bool isLegal(Box from, Box to, char player = 'W' , char opponent = 'B')
	{
		if(board[from.x][from.y].color == opponent)
		{
			return false;
		}
		else if (board[from.x][from.y].piece == 'P')
		{
			if(board[from.x][from.y].color == 'W')
			{
				if(from.x == 6 )
				{
					if(board[to.x][to.y].piece == ' ' && ( to.x == 5 || (to.x == 4 && board[5][to.y].color == 0) ) && from.y == to.y )
					{
						return true;
					}
					else if( board[to.x][to.y].color == opponent && ( to.x == 5 /*|| (to.x == 4 && board[5][to.y].color == 0)*/ ) && 
						   (to.y == from.y + 1 || to.y == from.y - 1 ) )
					{
						return true;
					}
					else
					{
						return false;
					}

				}
				else
				{
					if(board[to.x][to.y].piece == ' ' && ( to.x == from.x - 1) && from.y == to.y )
					{
						return true;
					}
					else if( board[to.x][to.y].color == opponent && ( to.x == from.x - 1 ) && (to.y == from.y + 1 || to.y == from.y - 1 ) )
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else if (board[from.x][from.y].color == 'B')
			{
				if(from.x == 1 )
				{
					if(board[to.x][to.y].piece == ' ' && ( to.x == 2 || (to.x == 3 && board[2][to.y].color == 0) ) && from.y == to.y )
					{
						return true;
					}
					else if( board[to.x][to.y].color == opponent && ( to.x == 2 /*|| (to.x == 3 && board[2][to.y].color == 0) */) && (to.y == from.y + 1 || to.y == from.y - 1 ) )
					{
						return true;
					}
					else
					{
						return false;
					}

				}
				else
				{
					if(board[to.x][to.y].piece == ' ' && ( to.x == from.x + 1) && from.y == to.y )
					{
						return true;
					}
					else if( board[to.x][to.y].color == opponent && ( to.x == from.x + 1 ) && (to.y == from.y + 1 || to.y == from.y - 1 ) )
					{
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				return false;
			}
		}
		else if (board[from.x][from.y].piece == 'k')
		{
			if( board[to.x][to.y].color != player && (( (to.x == from.x - 2 || to.x == from.x + 2 ) && (to.y == from.y - 1 || to.y == from.y + 1) ) ||  
			  ( (to.y == from.y - 2 || to.y == from.y + 2 ) && (to.x == from.x - 1 || to.x == from.x + 1) ))  )
			{	
				return true;
			}
			else 
			{
				return false;
			}
		}
		else if (board[from.x][from.y].piece == 'R')
		{
			if( ( (to.x == from.x && !hasHurdle(from,to)) || (to.y == from.y && !hasHurdle(from,to)))  && board[to.x][to.y].color != player && !(to == from))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (board[from.x][from.y].piece == 'B')
		{
			if ( board[to.x][to.y].color != player && from.x != to.x && from.y != to.y && !hasDiagonalHurdle(from,to) )
			{
				return true;
			}
			else 
			{
				return false;
			}
		}
		else if (board[from.x][from.y].piece == 'Q')
		{
			if ( ( board[to.x][to.y].color != player && from.x != to.x && from.y != to.y && !hasDiagonalHurdle(from,to) ) ||   
			   ( ( (to.x == from.x && !hasHurdle(from,to)) || (to.y == from.y && !hasHurdle(from,to)))  && board[to.x][to.y].color != player) )
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (board[from.x][from.y].piece == 'K')
		{
			if(board[to.x][to.y].color != player &&( ( (to.x == from.x - 1 || to.x == from.x + 1 ) && (to.y == from.y ) ) ||  
				( (to.y == from.y - 1 || to.y == from.y + 1 ) && ( to.x == from.x ) ) || (to.x == from.x - 1 && to.y == from.y - 1) || 
				( to.x == from.x - 1 && to.y == from.y + 1  ) || (to.x == from.x + 1 && to.y == from.y - 1) || 
				( to.x == from.x + 1 && to.y == from.y + 1  )) )
			{	
				return true;
			}
			else 
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	bool hasHurdle(Box from, Box to)
	{
		if(from.y == to.y)
		{
			if(from.x < to.x && from.y == to.y)
			{
				for(int i = from.x + 1 ; i < to.x ; i++)
				{
					if(board[i][from.y].color != 0)
						return true;
				}
				return false;
			}
			else if (from.x > to.x && from.y == to.y)
			{
				for(int i = from.x - 1 ; i > to.x ; i--)
				{
					if(board[i][from.y].color != 0)
						return true;
				}
				return false;
			}
			else
			{
				return false;
			}
		}
		else if(from.x == to.x)
		{
			if (from.y < to.y && from.x == to.x)
			{
				for(int i = from.y + 1 ; i < to.y ; i++)
				{
					if(board[from.x][i].color != 0)
						return true;
				}
				return false;
			}
			else if (from.y > to.y && from.x == to.x)
			{
				for(int i = from.y - 1 ; i > to.y ; i--)
				{
					if(board[from.x][i].color != 0)
						return true;
				}
				return false;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	bool hasDiagonalHurdle(Box from , Box to)
	{
		if( to.x < from.x  && to.y > from.y)
		{
			for(int i = from.x - 1 , j = from.y + 1 ; i > to.x && j < to.y ; i-- , j++)
			{
				if(board[i][j].color != 0)
					return true;
			}
			for(int i = from.x - 1 , j = from.y + 1 ; i >= to.x && j <= to.y ; i-- , j++)
			{
				if(i == to.x && j == to.y )
					return false;
			}
			return true;
		}
		else if ( to.x > from.x  && to.y > from.y)
		{
			for(int i = from.x + 1 , j = from.y + 1 ; i < to.x && j < to.y ; i++ , j++)
			{
				if(board[i][j].color != 0)
					return true;
			}
			for(int i = from.x + 1 , j = from.y + 1 ; i <= to.x && j <= to.y ; i++ , j++)
			{
				if(i == to.x && j == to.y )
					return false;
			}
			return true;
		}
		else if ( to.x < from.x  && to.y < from.y)
		{
			for(int i = from.x - 1 , j = from.y - 1 ; i > to.x && j > to.y ; i-- , j--)
			{
				if(board[i][j].color != 0)
					return true;
			}
			for(int i = from.x - 1 , j = from.y - 1 ; i >= to.x && j >= to.y ; i-- , j--)
			{
				if(i == to.x && j == to.y )
					return false;
			}
			return true;
		}
		else if ( to.x > from.x  && to.y < from.y)
		{
			for(int i = from.x + 1 , j = from.y - 1 ; i < to.x && j > to.y ; i++ , j--)
			{
				if(board[i][j].color != 0)
					return true;
			}
			for(int i = from.x + 1 , j = from.y - 1 ; i <= to.x && j >= to.y ; i++ , j--)
			{
				if(i == to.x && j == to.y )
					return false;
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	void computersMove()
	{
		
		Box from;
		for(int i = 0 ; i < 8 ; i++)
		{
			for(int j = 0 ; j < 8 ; j++)
			{
				if(board[i][j].color == 'B' || board[i][j].color == 'W')
				{
					from.x = i; from.y = j;
					listPossibleMoves(from);
				}
			}
		}
		

		if( checkMate( kingPosition() ))
		{
			setCursor(3,20);
			cout << "NOTE: Computer King CheckMate! ";

			if(!saveTheKing())
			{
				setCursor(3,21);
				cout << "Congratulations! Y O U  W I N ! \n";
				exit(0);
			}
		}
		else
		{
			Move m;
			static int turn = 1;
			if(turn == 1)
			{
				Box f,t;
				f.x = 1; f.y = 4;
				t.x = 3 ; t.y = 4;
				
				m.from = f;
				m.to = t;
				m.piece = 'P';

				makeSelectedMove(m);
				turn++;
			}
			else
			{

				if(moves.head != NULL)
				{
					bool moved = false;

					checkMateTheKing();

				
					if(isBoardSafe())
					{
						moved = selectAKillMove(m);
						if(!moved)
						{
							moved = selectASafeMove(m);
							if(!moved)
							{
								moved = selectAPossibleMove(m);
								if(!moved)
								{
									m = moves.head->element;

									setCursor(3,20);
									cout << "Congratulations! Y O U  W I N ! \n";
									exit(0);
								}
							}
						}
					}
					else
					{
						moved = selectASafeMove(m);
						if(!moved)
						{
							moved = selectAKillMove(m);
							if(!moved)
							{
								moved = selectAPossibleMove(m);
								if(!moved)
								{
									m = moves.head->element;

									setCursor(3,20);
									cout << "Congratulations! Y O U  W I N ! \n";
									exit(0);
								}
							}
						}
					}
					makeSelectedMove(m);
				}
				else if( moves.head == NULL || OpponentMoves.head == NULL )
				{
					setCursor(3,20);
					cout << "Stalemate! G A M E  D R A W N !\n";
					exit(0);
				}
			}
		}
		deleteAllMoves();

	}

	void makeSelectedMove(Move m)
	{
		Box f = m.from;
		Box t = m.to;
		char piece = board[t.x][t.y].piece;

		if(board[t.x][t.y].color == 'W')
		{
			captured(piece);
		}

		board[t.x][t.y].piece = board[f.x][f.y].piece;
		board[t.x][t.y].color = 'B';
		board[f.x][f.y].piece = ' ';
		board[f.x][f.y].color = 0;

		updateBoard(f , t );

		if(t.x == 7 && board[t.x][t.y].piece == 'P' )
		{
			setCursor(board[t.x][t.y].x,board[t.x][t.y].y);
			setColor(9);
			cout <<  board[t.x][t.y].piece ;

			Sleep(3000);
			setCursor(board[t.x][t.y].x,board[t.x][t.y].y);
			setColor(54);

			board[t.x][t.y].piece = 'Q' ;
			cout << board[t.x][t.y].piece;
		}
		deleteAllMoves();
	}

	void deleteAllMoves()
	{
			moves.deleteAll();
			PawnMoves.deleteAll();
			KingMoves.deleteAll();
			QueenMoves.deleteAll();
			KnightMoves.deleteAll();
			BishopMoves.deleteAll();
			RookMoves.deleteAll();
			OpponentMoves.deleteAll();
			UnderAttackPieces.deleteAll();
			tempMoves.deleteAll();
	}

	Box kingPosition(char color = 'B')
	{
		Box temp;
		for(int i = 0 ; i < 8 ; i++)
		{
			for(int j = 0 ; j < 8 ; j++)
			{
				if(board[i][j].color == color &&  board[i][j].piece == 'K')
				{
					temp.x = i;
					temp.y = j;
					break;
				}
			}
		}
		return temp;
	}

	bool saveTheKing()
	{
		Box f ;
		Box t ;
		char piece;
		char color;
		bool safe = false;

		


		for(temp = PawnMoves.head ; temp != NULL && !safe; temp = temp->next)
		{
			f = temp->element.from;
			t = temp->element.to;
			piece = board[t.x][t.y].piece;
			color = board[t.x][t.y].color;

			board[t.x][t.y].piece = board[f.x][f.y].piece;
			board[t.x][t.y].color = 'B';
			board[f.x][f.y].piece = ' ';
			board[f.x][f.y].color = 0;

			if(!checkMate(kingPosition()))
			{
				if(piece != ' ' && color == 'W')
				{
					captured(piece);
				}
				safe = true;
				updateBoard(f , t );
						

				if(t.x == 7 && board[t.x][t.y].piece == 'P' )
				{
					setCursor(board[t.x][t.y].x,board[t.x][t.y].y);
					setColor(9);
					cout <<  board[t.x][t.y].piece ;

					Sleep(3000);
					setCursor(board[t.x][t.y].x,board[t.x][t.y].y);
					setColor(54);

					board[t.x][t.y].piece = 'Q' ;
					cout << board[t.x][t.y].piece;
				}

			}
			else
			{
				safe = false;

				board[f.x][f.y].piece = 'P';
				board[f.x][f.y].color = 'B';
				board[t.x][t.y].piece = piece;
				board[t.x][t.y].color = color;
			}
		}

		if(!safe)
		{
			for(temp = KnightMoves.head ; temp != NULL && !safe; temp = temp->next)
			{
				f = temp->element.from;
				t = temp->element.to;
				piece = board[t.x][t.y].piece;
				color = board[t.x][t.y].color;

				board[t.x][t.y].piece = board[f.x][f.y].piece;
				board[t.x][t.y].color = 'B';
				board[f.x][f.y].piece = ' ';
				board[f.x][f.y].color = 0;

				if(!checkMate(kingPosition()))
				{
					if(piece != ' ' && color == 'W')
					{
						captured(piece);
					}
					safe = true;
					updateBoard(f , t );
				}
				else
				{
					safe = false;

					board[f.x][f.y].piece = 'k';
					board[f.x][f.y].color = 'B';
					board[t.x][t.y].piece = piece;
					board[t.x][t.y].color = color;
				}
			}
		}

		if(!safe)
		{
			for(temp = BishopMoves.head ; temp != NULL && !safe; temp = temp->next)
			{
				f = temp->element.from;
				t = temp->element.to;
				piece = board[t.x][t.y].piece;
				color = board[t.x][t.y].color;

				board[t.x][t.y].piece = board[f.x][f.y].piece;
				board[t.x][t.y].color = 'B';
				board[f.x][f.y].piece = ' ';
				board[f.x][f.y].color = 0;

				if(!checkMate(kingPosition()))
				{
					if(piece != ' ' && color == 'W')
					{
						captured(piece);
					}
					safe = true;
					updateBoard(f , t );
				}
				else
				{
					safe = false;

					board[f.x][f.y].piece = 'B';
					board[f.x][f.y].color = 'B';
					board[t.x][t.y].piece = piece;
					board[t.x][t.y].color = color;
				}
			}
		}

		if(!safe)
		{
			for(temp = RookMoves.head ; temp != NULL && !safe; temp = temp->next)
			{
				f = temp->element.from;
				t = temp->element.to;
				piece = board[t.x][t.y].piece;
				color = board[t.x][t.y].color;

				board[t.x][t.y].piece = board[f.x][f.y].piece;
				board[t.x][t.y].color = 'B';
				board[f.x][f.y].piece = ' ';
				board[f.x][f.y].color = 0;

				if(!checkMate(kingPosition()))
				{
					if(piece != ' ' && color == 'W')
					{
						captured(piece);
					}
					safe = true;
					updateBoard(f , t );
				}
				else
				{
					safe = false;

					board[f.x][f.y].piece = 'R';
					board[f.x][f.y].color = 'B';
					board[t.x][t.y].piece = piece;
					board[t.x][t.y].color = color;
				}
			}
		}

		if(!safe)
		{
			for(temp = QueenMoves.head ; temp != NULL && !safe; temp = temp->next)
			{
				f = temp->element.from;
				t = temp->element.to;
				piece = board[t.x][t.y].piece;
				color = board[t.x][t.y].color;

				board[t.x][t.y].piece = board[f.x][f.y].piece;
				board[t.x][t.y].color = 'B';
				board[f.x][f.y].piece = ' ';
				board[f.x][f.y].color = 0;

				if(!checkMate(kingPosition()) && isLegal(f,t,'B','W'))
				{
					if(piece != ' ' && color == 'W')
					{
						captured(piece);
					}
					safe = true;
					updateBoard(f , t );
				}
				else
				{
					safe = false;

					board[f.x][f.y].piece = 'Q';
					board[f.x][f.y].color = 'B';
					board[t.x][t.y].piece = piece;
					board[t.x][t.y].color = color;
				}
			}
		}

		f = kingPosition();
		if(!safe)
		{
			for(temp = KingMoves.head ; temp != NULL && !safe ; temp = temp->next)
			{
				t = temp->element.to;
				piece = board[t.x][t.y].piece;
				color = board[t.x][t.y].color;

				board[t.x][t.y].piece = board[f.x][f.y].piece;
				board[t.x][t.y].color = 'B';
				board[f.x][f.y].piece = ' ';
				board[f.x][f.y].color = 0;

				if(!checkMate(kingPosition()))
				{
					if(piece != ' ' && color == 'W')
					{
						captured(piece);
					}
					safe = true;
					updateBoard(f , t );	
				}
				else
				{
					safe = false;

					board[f.x][f.y].piece = 'K';
					board[f.x][f.y].color = 'B';
					board[t.x][t.y].piece = piece;
					board[t.x][t.y].color = color;
				}
			}
		}
		return safe;
	}

	void checkMateTheKing()
	{
		Node<Move> * temp;
		for(temp = moves.head ; temp != NULL ; temp = temp->next)
		{
			if(isKillMove(temp->element.to) && board[temp->element.to.x][temp->element.to.y].piece == 'K')
			{
				setCursor(3,20);
				cout << "SORRY! Y O U  L O S E ! \n";
				exit(0);
			}
		}
	}
	
	bool selectAKillMove(Move & m)
	{
		Box f,t;
		char pieceF,pieceT;
		Node<Move> * temp;
		for(temp = moves.head ; temp != NULL ; temp = temp->next)
		{
			f = temp->element.from;
			t = temp->element.to;
			pieceF = board[f.x][f.y].piece;
			pieceT = board[t.x][t.y].piece;

			if(isKillMove(t) && pieceT == 'Q' )
			{
				m = temp->element;
				return true;
			}
			else if(isKillMove(t) && isSafeMove(f,t))
			{
				m = temp->element;
				return true;
			}
			else if(isKillMove(t) && pieceF == 'P' )
			{
				m = temp->element;
				return true;
			}
			else if (isKillMove(t) && pieceF == 'B' && (pieceT == 'k' || pieceT == 'Q' || pieceT == 'B' ))
			{
				m = temp->element;
				return true;
			}
		}
		return false;
	}

	bool selectASafeMove(Move & m)
	{
		Box f,t;
		Node<Move> * temp;
		for(temp = moves.head ; temp != NULL ; temp = temp->next)
		{
			f = temp->element.from;
			t = temp->element.to;

			if( isSafeMove(f,t) )
			{
				m = temp->element;
				return true;
			}
		}
		f = getThreatenedPiece();
		if( !(f == kingPosition()) )
		{
			for(int i = 0 ; i < 8 ; i++)
			{
				for(int j = 0 ; j < 8 ; j++)
				{
					t.x = i ; t.y = j;
					if(isLegal(f,t,'B','W') && isSafe(f,t) && isKingSafe(f,t))
					{
						m.from = f; m.to = t;
						return true;
					}
				}
			}
		}
		else if ( f == kingPosition() && checkMate(f) )
		{
			for(int i = 0 ; i < 8 ; i++)
			{
				for(int j = 0 ; j < 8 ; j++)
				{
					t.x = i ; t.y = j;
					if(isLegal(f,t,'B','W') && isSafe(f,t) && isKingSafe(f,t))
					{
						m.from = f; m.to = t;
						return true;
					}
				}
			}
		}
		return false;
	}

	Box getThreatenedPiece()
	{
		Node<Move> * temp;
		Node<Move> * temp2;
		for(temp = moves.head ; temp != NULL ; temp = temp->next)
		{
			for(temp2 = OpponentMoves.head ; temp2 != NULL ; temp2 = temp2->next)
			{
				if(temp->element.from == temp2->element.to)
				{
					UnderAttackPieces.addToTail(temp->element.from);
				}
			}
		}
		Node<Box> * temp3;
		Box mt;
		mt = kingPosition();
		bool got = false;
		for(temp3 = UnderAttackPieces.head ; temp3 != NULL ; temp3 = temp3->next)
		{
			if(board[temp3->element.x][temp3->element.y].piece == 'Q')
			{
				listMoves(temp3->element);
				for(Node<Move> * t = tempMoves.head ; t != NULL ; t = t->next )
				{
					if(isSafeMove(t->element.from, t->element.to))
					{
						mt = temp3->element;
						got = true;
						break;
					}
				}
				tempMoves.deleteAll();
			}
			else if (board[temp3->element.x][temp3->element.y].piece == 'k')
			{
				listMoves(temp3->element);
				for(Node<Move> * t = tempMoves.head ; t != NULL ; t = t->next )
				{
					if(isSafeMove(t->element.from, t->element.to))
					{
						mt = temp3->element;
						got = true;
					}
				}
				tempMoves.deleteAll();
			}
		}
		if(!got)
		{
			for(temp3 = UnderAttackPieces.head ; temp3 != NULL ; temp3 = temp3->next)
			{
				if(board[temp3->element.x][temp3->element.y].piece == 'B')
				{
					listMoves(temp3->element);
					for(Node<Move> * t = tempMoves.head ; t != NULL ; t = t->next )
					{
						if(isSafeMove(t->element.from, t->element.to))
						{
							mt = temp3->element;
							got = true;
							break;
						}
					}
					tempMoves.deleteAll();
				}
				else if (board[temp3->element.x][temp3->element.y].piece == 'R')
				{
					listMoves(temp3->element);
					for(Node<Move> * t = tempMoves.head ; t != NULL ; t = t->next )
					{
						if(isSafeMove(t->element.from, t->element.to))
						{
							mt = temp3->element;
							got = true;
						}
					}
					tempMoves.deleteAll();
				}
			}
		}

		if(!got)
		{
			for(temp3 = UnderAttackPieces.head ; temp3 != NULL ; temp3 = temp3->next)
			{
				if(board[temp3->element.x][temp3->element.y].piece == 'P')
				{
					listMoves(temp3->element);
					for(Node<Move> * t = tempMoves.head ; t != NULL ; t = t->next )
					{
						if(isSafeMove(t->element.from, t->element.to))
						{
							mt = temp3->element;
							got = true;
							break;
						}
					}
					tempMoves.deleteAll();
				}
			}
		}
		return mt;
	}

	void listMoves(Box from)
	{
		Box to;
		Move m;
		for(int i = 0 ; i < 8 ; i++)
		{
			for(int j = 0 ; j < 8 ; j++)
			{
				to.x = i; to.y = j;
				m.from = from;
				m.to = to;
				m.piece = board[from.x][from.y].piece;

				if(isLegal(from,to,'B','W'))
				{
					tempMoves.addToHead(m);
				}
			}
		}
	}

	bool isSafeMove(Box from, Box to)
	{
		char pieceF;
		char colorF;
		char pieceT;
		char colorT;
		bool safe;
		Box f = from;
		Box t = to;
		pieceF = board[f.x][f.y].piece;
		colorF = board[f.x][f.y].color;
		pieceT = board[t.x][t.y].piece;
		colorT = board[t.x][t.y].color;

		board[t.x][t.y].piece = board[f.x][f.y].piece;
		board[t.x][t.y].color = 'B';
		board[f.x][f.y].piece = ' ';
		board[f.x][f.y].color = 0;

		if(isBoardSafe())
			safe = true;
		else
			safe = false;

		board[f.x][f.y].piece = pieceF;
		board[f.x][f.y].color = colorF;
		board[t.x][t.y].piece = pieceT;
		board[t.x][t.y].color = colorT;

		return safe;
	}

	bool selectAPossibleMove(Move & m)
	{
		Box f,t;
		Node<Move> * temp;
		for(temp = moves.head ; temp != NULL ; temp = temp->next)
		{
			f = temp->element.from;
			t = temp->element.to;

			if( isKingSafe(f,t) )
			{
				m = temp->element;
				return true;
			}
		}
		return false;
	}

	void updateBoard(Box f , Box t , int color = 54)
	{
		int x = ((f.y + 1) * 4) + 6;
		int y = (f.x + 1) * 2;
		setCursor(x,y);
		cout << ' ' ;
		x = (t.y + 1) * 4 + 6;
		y = (t.x + 1) * 2;
		setCursor(x,y);
		setColor(color);
		cout <<  board[t.x][t.y].piece ;
	}

	void captured(char piece)
	{
		static int x = 48;
		setCursor(x,5);
		setColor(5);
		cout << piece << " ";
		x+=2;
	}
	
	bool checkMate( Box king)
	{
		Node<Move> * temp;
		for(temp = OpponentMoves.head ; temp->next != NULL ; temp = temp->next)
		{
			if(temp->element.to.x == king.x && temp->element.to.y == king.y && isLegal(temp->element.from,temp->element.to,'W','B'))
			{
				return true;
			}
		}

		return false;
	}

	bool isKillMove(Box to)
	{
		if(board[to.x][to.y].color == 'W')
			return true;
		else
			return false;
	}
	
	bool isBoardSafe()
	{
		Node<Move> * temp;
		for(temp = OpponentMoves.head ; temp->next != NULL ; temp = temp->next)
		{
			if( board[temp->element.to.x][temp->element.to.y].color == 'B' && isLegal(temp->element.from,temp->element.to,'W','B') )
			{
				return false;
			}
		}

		return true;
	}

	bool isKingSafe(Box from , Box to)
	{
		char pieceF;
		char colorF;
		char pieceT;
		char colorT;

		Box f = from;
		Box t = to;
		pieceF = board[f.x][f.y].piece;
		colorF = board[f.x][f.y].color;
		pieceT = board[t.x][t.y].piece;
		colorT = board[t.x][t.y].color;

		board[t.x][t.y].piece = board[f.x][f.y].piece;
		board[t.x][t.y].color = 'B';
		board[f.x][f.y].piece = ' ';
		board[f.x][f.y].color = 0;

		Node<Move> * temp;
		for(temp = OpponentMoves.head ; temp->next != NULL ; temp = temp->next)
		{
			if( board[temp->element.to.x][temp->element.to.y].piece == 'K' && board[temp->element.to.x][temp->element.to.y].color == 'B' && 
				isLegal(temp->element.from,temp->element.to,'W','B') )
			{
				board[f.x][f.y].piece = pieceF;
				board[f.x][f.y].color = colorF;
				board[t.x][t.y].piece = pieceT;
				board[t.x][t.y].color = colorT;
				return false;
			}
		}
		board[f.x][f.y].piece = pieceF;
		board[f.x][f.y].color = colorF;
		board[t.x][t.y].piece = pieceT;
		board[t.x][t.y].color = colorT;
		return true;
	}

	bool isSafe(Box from , Box to)
	{
		char pieceF;
		char colorF;
		char pieceT;
		char colorT;

		Box f = from;
		Box t = to;
		pieceF = board[f.x][f.y].piece;
		colorF = board[f.x][f.y].color;
		pieceT = board[t.x][t.y].piece;
		colorT = board[t.x][t.y].color;

		board[t.x][t.y].piece = board[f.x][f.y].piece;
		board[t.x][t.y].color = 'B';
		board[f.x][f.y].piece = ' ';
		board[f.x][f.y].color = 0;

		Node<Move> * temp;
		for(temp = OpponentMoves.head ; temp->next != NULL ; temp = temp->next)
		{
			if( temp->element.to.x == to.x && temp->element.to.y == to.y && board[temp->element.to.x][temp->element.to.y].color == 'B' && 
				isLegal(temp->element.from,temp->element.to,'W','B') )
			{
				board[f.x][f.y].piece = pieceF;
				board[f.x][f.y].color = colorF;
				board[t.x][t.y].piece = pieceT;
				board[t.x][t.y].color = colorT;
				return false;
			}
		}
		board[f.x][f.y].piece = pieceF;
		board[f.x][f.y].color = colorF;
		board[t.x][t.y].piece = pieceT;
		board[t.x][t.y].color = colorT;
		return true;
	}

	void listPossibleMoves(Box from)
	{
		Box to;
		Move m;
		for(int i = 0 ; i < 8 ; i++)
		{
			for(int j = 0 ; j < 8 ; j++)
			{
				to.x = i; to.y = j;
				m.from = from;
				m.to = to;
				m.piece = board[from.x][from.y].piece;

				if(isLegal(from,to,'B','W'))
				{
					if(m.piece == 'P' )
						if(isKillMove(m.to))
							PawnMoves.addToHead(m);
						else
							PawnMoves.addToTail(m);
					else if(m.piece == 'K')
						if(isKillMove(m.to))
							KingMoves.addToHead(m);
						else
							KingMoves.addToTail(m);
					else if(m.piece == 'Q')
						if(isKillMove(m.to))
							QueenMoves.addToHead(m);
						else
							QueenMoves.addToTail(m);
					else if(m.piece == 'k')
						if(isKillMove(m.to))
							KnightMoves.addToHead(m);
						else
							KnightMoves.addToTail(m);
					else if(m.piece == 'B')
						if(isKillMove(m.to))
							BishopMoves.addToHead(m);
						else
							BishopMoves.addToTail(m);
					else if(m.piece == 'R')
						if(isKillMove(m.to))
							RookMoves.addToHead(m);
						else
							RookMoves.addToTail(m);
					

					if(board[m.to.x][m.to.y].piece == 'Q' || (isKillMove(m.to) /*&& isSafeMove(m.from,m.to)*/) )
						moves.addToHead(m);
					else
						moves.addToTail(m);
				}

				if(isLegal(from,to,'W','B'))
				{
					OpponentMoves.addToTail(m);	
				}
			}
		}
	}
};

#endif