/*
  For details, visit www.hammadmukhtar.com
*/

#include <iostream>
#include "Stack.h"
#include "Stack.cpp"
#include "Chess.h"

using namespace std;

Stack<Box> box(4);
Chess chess;
void UserMove(int x, int y);

class MouseInputHandler
{
      //mouse input handler callback function pointer
      typedef void (*MIHCB)(int,int,void*);
      
      public:
      MouseInputHandler(){}
      ~MouseInputHandler(){}
      void init();
      
      inline void start_polling()
      {
             _beginthread(polling_function,0,this);
             polling=true;
      }
      
      inline void stop_polling()
      {
             input.quit=true;
             while (polling);
      }
      
      int getx();
      int gety();
      void getxy(int & x, int & y);
      
      //setting the callbacks
      inline void set_lbdcb(MIHCB f){lbdcb=f;}
      inline void set_lbucb(MIHCB f){lbucb=f;}
      inline void set_lbccb(MIHCB f){lbccb=f;}
      inline void set_rbdcb(MIHCB f){}
      inline void set_rbucb(MIHCB f){}
      inline void set_rbccb(MIHCB f){}
      
      //setting the params for the callbacks
      inline void set_lbdcbp(void*p){lbdcbp=p;}
      inline void set_lbucbp(void*p){lbucbp=p;}
      inline void set_lbccbp(void*p){lbccbp=p;}
      inline void set_rbdcbp(void*p){}
      inline void set_rbucbp(void*p){}
      inline void set_rbccbp(void*p){}
      
      private:
      struct MouseInput
      {
             //current and previous mouse button status
             bool cleft, pleft;
             bool cright, pright;
             
             bool quit;
             int x,y;
                          
      } input;
      
      bool polling;
      
      static void polling_function(void*);
      static inline bool is_pressed(int key)
      {
		  int result = (GetAsyncKeyState(key)>>15);
		  if(result == 0)
			  return false;
		  else
			  return true;
      }
      
      MIHCB lbdcb;
      MIHCB lbucb;
      MIHCB lbccb;
      MIHCB rbdcb;
      MIHCB rbucb;
      MIHCB rbccb;
      
      void* lbdcbp;
      void* lbucbp;
      void* lbccbp;
      void* rbdcbp;
      void* rbucbp;
      void* rbccbp;
  
};

void MouseInputHandler::polling_function(void*p)
{
     MouseInputHandler * m=(MouseInputHandler*)p;
     
     m->input.quit=false;
     
     HWND window=GetConsoleWindow();
     RECT wpos;
     POINT cpos;
     
     
     m->input.cleft=m->input.pleft=m->input.cright=m->input.pright=false;
     int x,y;
     int tl/*, tr*/,t;
     
          
     while (!m->input.quit)
     {
           GetWindowRect(window,&wpos);
           GetCursorPos(&cpos);
           
           cpos.x-=wpos.left;
           cpos.y-=wpos.top;
           
           //transform screen to console coords
           x=(cpos.x-5)/8;           
           y=(cpos.y-25)/12;
           
           m->input.cleft=is_pressed(VK_LBUTTON);
           m->input.cright=is_pressed(VK_RBUTTON);
           
           //mouse down event: it was up and now is down 
           if (m->input.cleft && !m->input.pleft)
           {
              tl=(clock()*1000)/CLOCKS_PER_SEC;                
              m->lbdcb(x,y,m->lbdcbp);
           }
           
           //mouse up event: it was down and now is up
           if (!m->input.cleft && m->input.pleft)
           {
              t=(clock()*1000)/CLOCKS_PER_SEC;             
              m->lbucb(x,y,m->lbucbp);
              
              //mouse click event:
              //down->up in less than 100 ms
              if (t-tl<=100)
              m->lbccb(x,y,m->lbccbp);
           }
           
           //...more stuff here
           
           m->input.pleft=m->input.cleft;
           //m->input.pright=m->input.cright;
     
           Sleep(25);
     }
     m->polling=false;
}

void left_down(int x, int y, void*p)
{
	UserMove(x,y);
}

void UserMove(int x , int y)
{
	setCursor(3,20);
	if( x >= 9 && x <= 39 && y >= 1 && y <= 17)
	{
		cout << "                                              ";
		setCursor(3,20);
		Box b;
		b.x = x; b.y = y;
		char c = readFrom(x,y);
		if((( c >= 65 && c <= 90) || c == 'k' || c == ' ' ) && box.IsEmpty())
		{
			if(c == ' ' )
			{
				c = readFrom(x-1,y);
				if( c >= 65 && c <= 90 )
				{
					b.x = x-1;
					box.Push(b);
					setCursor(x-1,y);
					setColor(9);
					cout << c;
				}
				c = readFrom(x+1,y);
				if( c >= 65 && c <= 90 )
				{
					b.x = x+1;
					box.Push(b);
					setCursor(x+1,y);
					setColor(9);
					cout << c;
				}
			}
			else
			{
				box.Push(b);
				setCursor(x,y);
				setColor(9);
				cout << c;
			}
		}
		else if(!box.IsEmpty() &&( c == 'P' || c == 'Q' || c == 'K' || c == 'B' || c == 'R' || c == 'k' || c == ' '))
		{
			chess.move(box.Pop(),b);
		}
		else if(box.IsEmpty() && (c == ' ' || c == '=' || c == '|'))
		{
			setColor(54);
			cout << "NOTE: Select the White piece You want to move   ";
		}
	}
	else
	{
		setColor(54);
		cout << " NOTE: Out of Board! Select a white piece\n   ";
		box.ClearStack();
	}
}

void left_up(int x, int y, void*p)
{
    /* printf("up at (%d,%d) ",x,y);
	char c = readFrom(x,y);
	cout << c << " ";*/
}

void left_click(int x, int y, void*p)
{
 //    printf("click at (%d,%d) ",x,y);
	//cout << readFrom(x,y) << " ";

}

void initializeMouse()
{
	MouseInputHandler mouse;
    mouse.set_lbdcb(left_down);
    mouse.set_lbucb(left_up);
    mouse.set_lbccb(left_click);
    
    mouse.start_polling();

	mouse.stop_polling();
}

int main()
{
	/*WORD wAttributes = ( 7 | 58);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wAttributes);*/
	
	system("color 37");
	
	chess.displayBoard();

	initializeMouse();


	return 0;
}