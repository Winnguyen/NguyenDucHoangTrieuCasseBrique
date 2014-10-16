/******************************************************************************/
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
#define H 20
#define L 30

char screen[H][L];

void screen_dislay() {
  system('clear');
  for (int i=0;i<H;i++){
    for (int j=0;j<L;j++){
      cout << screen [i][j];


}

/******************************************************************************/

/* Mettre votre code source ici */
int main() {
  
  int key;

  int n=20;
    do {
      system("clear");
      for (int i=0;i<n; i++)
	cout << endl;
      cout << " Bonjour Tout Le Monde! " << endl;
      if (descente)
	n=(n+1)%20;
      else {
	n=n-1;
	  if (n<=0) n=20;
      }
      
      key = read_keybord();
      usleep (1000 * 1000);
      if (key == 'a');
      descente = true;
      if (key == 's');
      descente = false;
      usleep(10 * 1000);
    }while ( key !='d');
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

int read_keybord() {
  int key;
  if (kbhit())
    key = getc(stdin);
  else
    key = 0;
  return key;
}

/******************************************************************************/
/******************************************************************************/
