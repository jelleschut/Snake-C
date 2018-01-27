#include "fsm.h"
#include "position.h"
#include "collision.h"
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int height = 16;                                      // total height playing field
int width = 40;                                       // total width playing field
int i,j;
char display[16][40];                                 // actual playing field in characters
char border = 'R';                                    // borders have red (R) LEDs
char field = '.';                                     // field LEDs are off
char snake = 'G';                                     // Snake LEDS are green (G)
char borderCollision = '*';

void printField(void)
{
   for(i = 0; i < height; i++)
   {
      for(j = 0; j < width; j++)
      {
         printf("%c",display[i][j]);                  // printing the playingfield
      }
      printf("\n");
   }
   printf("\n\n\n\n\n\n\n\n\n\n\n");
}

void standardDisplay(void)
{
   for(i = 0; i < height; i++)
   {
      for(j = 0; j < width; j++)
      {
         if(i < 2)                                       // top 2 lines are borders
         {
            display[i][j] = border;
         }
         if(i >= height - 2 && i < height)               // bottom 2 lines are borders
         {
            display[i][j] = border;
         }
         if(j < 2)                                       // first 2 columns are borders
         {
            display[i][j] = border;
         }
         if(j >= width - 2 && i < width)                 // last 2 borders are columns
         {
            display[i][j] = border;
         }
         if((i >= 2 && i < height-2) && (j >= 2 && j < width-2))  // area between borders is playingfield
         {
            display[i][j] = field;
         }
      }
   }
}

void displayConfirmReset(void)
{
   char areYouSureReset[40] = "ARE YOU SURE YOU WANT TO RESET?";
   char yesOrNo[20] = "Y / N";

   writeString(7, 4, areYouSureReset);
   writeString(9, 18, yesOrNo);

   printField();

}

void displayConfirmMenu(void)
{
   char areYouSureReturn[40] = "ARE YOU SURE YOU WANT TO RETURN";
   char toMainMenu[40] = "TO MAIN MENU?";
   char yesOrNo[20] = "Y / N";

   writeString(7, 4, areYouSureReturn);
   writeString(8, 14, toMainMenu);
   writeString(9, 18, yesOrNo);

   printField();
}

void displayMenu(void)
{
   char newGame[20] = "1:.NEW.GAME";
   char shutDown[20] = "2:.SHUT.DOWN";

   standardDisplay();

   writeString(6, 10, newGame);
   writeString(10, 10, shutDown);

   printField();
}

void displaySnake(int position[2])
{
   standardDisplay();                                 // using standarddisplay to set background

   display[position[0]][position[1]] = checkBorderCollision(position);

   printField();
}

void displayShutDown(void)
{
   for(i = 0; i < height; i++)
   {
      for(j = 0; j < width; j++)
      {
         display[i][j] = field;
      }
   }
   printField();
}


void writeString(int startX, int startY, char *string)
{
   int lengthString  = strlen(string);

   for (i = 0; i < lengthString; i++)
   {
      display[startX][startY+i] = string[i];
   }
}
