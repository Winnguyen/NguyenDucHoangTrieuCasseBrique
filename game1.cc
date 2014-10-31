#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
using namespace std;

/* retourne 0 si aucune touche n'est appuyée, 
 * sinon retourne le code ASCII de la touche */
 int read_keybord();

/******************************************************************************/
#define H 30 // Hauteur
#define L 40 // Largeur
char screen[H][L];
int c=1; int bg=15, bd=25;
void screen_display()
{
  system("clear");
  for (int i=0; i<H; i++)
    for (int j=0; j<L; j++)
      if (i==0||i==H-1||j==0||j==L-1)
	screen[i][j]='|';

  
  for(int i=0; i<H; i++)
    {
      for (int j=0; j<L; j++)
	cout << screen[i][j];
      cout << endl;
    }
  // barre
  if (c==1)
    for(int j=bg; j<=bd; j++)
      screen[H-2][j]='=';


  
}

/******************************************************************************/

void clear_screen()
{
  for (int i=0; i<H; i++)
    for (int j=0; j<L; j++)
      if (screen[i][j]=='=') continue;
      else screen[i][j]= ' ';
}
/******************************************************************************/
int x=1,y=1;
 int a=1,b=1;
void update_game(int key)

{
  if (a==1) // le ballon mobilise de gauche a droite
    {
      if (b==1)
	{
	  screen[x][y]='*';
	  x++; y++;
	}

      if (x==H-1) // je fais comme cela pour eviter le cas " Le ballon apparait 2 fois dans le meme temps "
	{
	  b=0;
	  screen[x][y]='*';
	  x--; y--; 
	}

      if (b==0)
	{ 
	  screen[x][y]='*';
	  x--; y++;
	}

      if (y==L-1 && b==1)
	{
	  a=0;
	  x--; y--;
	}

      if (y==L-1 && b==0)
	{
	  a=0;
	  x++;y--;
	}
	  
      if(x==0)
	{
	  b=1;
	  x=x+2;
	}
      if (screen[x][y]=='=')
	{
	  b=0;
	  x=x-2;
	}
    }

  if (a==0)
    {  
      if (b==0)
	{	  
	  screen[x][y]='*';
	  x--;y--;
	}

      if (x==0)
	{
	  b=1;
	  x++;y++;
	}
      
      if (b==1)
	{
	  screen[x][y]='*';
	  x++;y--;
	}
      
      if(x==H-1)
	{
	  b=0;
	  x=x-2;
	}
      
      if(y==0)
	{
	  a=1;
	  y=y+2;
	}
      if (screen[x][y]=='=')
	{
	  b=0;
	  x=x-2;
	  
	  
	}
    }

  
}

/******************************************************************************/
void keyProcess(char key)
{
  if (key=='a' && bg>=1)   // le barre va a gauche
    {
      c=0;
      screen[H-2][bg]='=';bg--;
      screen[H-2][bd]=' ';bd--;
    } 
  
  if (key=='d' && bd<=L-2)  // le barre va a droite
    {
      c=0; 
      screen[H-2][bg]=' ';bg++;
      screen[H-2][bd]='=';bd++;
    }
  
}
/******************************************************************************/
int main()
{
  char key;   
  do
    {
      key=read_keybord();    
      clear_screen();
      update_game(key);
      screen_display();
      usleep(75 * 1000);
      keyProcess(key);      
    }
  
  while (key!= 'q');
}
/******************************************************************************/
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

int read_keybord() 
{
  int key;
  if (kbhit())
    key = getc(stdin);
  else
    key = 0;
  return key;
}
