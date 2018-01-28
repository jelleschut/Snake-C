#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "fsm.h"
#include "position.h"
#include "collision.h"
#include "macros.h"

int i,j;
int startPos = 1;
int X = STARTX;
int Y = STARTY;
char display[HEIGHT][WIDTH];                         // actual playing field in characters
char border = LEDBORDER;                                    // borders have red (R) LEDs
char field = LEDOFF;                                        // field LEDs are off
char snake = LEDSNAKE;                                      // Snake LEDS are green (G)

//-----------------------------------------------------------------------------------------------------//
// Basic screen functions

//Printing screen to terminal
void printField(void)
{
   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         printf("%c", display[i][j]);                  // printing the playingfield
      }
      printf("\n");
   }
   printf("\n\n\n\n\n\n\n\n\n\n\n");
}

//Empty display with borders
void standardDisplay(void)
{
   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         if(i < 2)                                       // top 2 lines are borders
         {
            display[i][j] = border;
         }
         if(i >= HEIGHT - 2 && i < HEIGHT)               // bottom 2 lines are borders
         {
            display[i][j] = border;
         }
         if(j < 2)                                       // first 2 columns are borders
         {
            display[i][j] = border;
         }
         if(j >= WIDTH - 2 && i < WIDTH)                 // last 2 borders are columns
         {
            display[i][j] = border;
         }
         if((i >= 2 && i < HEIGHT-2) && (j >= 2 && j < WIDTH-2))  // area between borders is playingfield
         {
            display[i][j] = field;
         }
      }
   }
}

//String writing function
void writeString(int startX, int startY, char *string)
{
   int lengthString  = strlen(string);

   for (i = 0; i < lengthString; i++)
   {
      display[startX][startY+i] = string[i];
   }
}
//end of basic screen functions
//-----------------------------------------------------------------------------------------------------//


//-----------------------------------------------------------------------------------------------------//
//Display States

//Main Menu
void displayMenu(void)
{
   char newGame[20] = "1:.NEW.GAME";
   char shutDown[20] = "2:.SHUT.DOWN";

   standardDisplay();

   writeString(6, 10, newGame);
   writeString(10, 10, shutDown);

   printField();
}

//Return to main menu
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

//Reset menu
void displayConfirmReset(void)
{
   char areYouSureReset[40] = "ARE YOU SURE YOU WANT TO RESET?";
   char yesOrNo[20] = "Y / N";

   writeString(7, 4, areYouSureReset);
   writeString(9, 18, yesOrNo);

   printField();
}

//Display Off
void displayShutDown(void)
{
   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         display[i][j] = field;
      }
   }
   printField();
}

//End of display states
//-----------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------//
//Display Snake

//snake position
void addToDisplay(int Y, int X, char LED)
{
   display[Y][X] = LED;
   //printf("%c", display[i][j]);
}

void displaySnake()
{
   int snakeY[255];
   int snakeX[255];

   standardDisplay();                                 // using standarddisplay to set background

   if (startPos == 1)
   {
      for(i = 1; i < SNAKELENGTH; i++)
      {

         snakeY[i] = STARTY;
         snakeX[i] = STARTX-i;

         display[snakeY[i]][snakeX[i]] = LEDSNAKE;

      }
   }

   if (startPos == 0)
   {
      for(i = SNAKELENGTH; i > 0; i--)
      {
         snakeY[i] = snakeY[i-1];
         snakeX[i] = snakeX[i-1];

         display[snakeY[i]][snakeX[i]] = LEDSNAKE;
      }
      display[snakeY[SNAKELENGTH]][snakeX[SNAKELENGTH]] = LEDOFF;
   }

   startPos = 0;

   snakeY[0] = positionHeadY();
   snakeX[0] = positionHeadX();

   if (borderCollision() == 1)
   {
      display[snakeY[0]][snakeX[0]] = LEDCOLLISON;
   }
   else
   {
      display[snakeY[0]][snakeX[0]] = LEDSNAKE;
   }
   printField();
}


