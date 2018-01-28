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
#include "snakebody.h"

int i,j;
int startPos = 1;
char display[HEIGHT][WIDTH];                         // actual playing field in characters
int snakeY[255];
int snakeX[255];
int score = 0;


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
         if(i < BORDERTHICK)                                       // top 2 lines are borders
         {
            display[i][j] = LEDBORDER;
         }
         if(i >= HEIGHT - BORDERTHICK && i < HEIGHT)               // bottom 2 lines are borders
         {
            display[i][j] = LEDBORDER;
         }
         if(j < BORDERTHICK)                                       // first 2 columns are borders
         {
            display[i][j] = LEDBORDER;
         }
         if(j >= WIDTH - BORDERTHICK && i < WIDTH)                 // last 2 borders are columns
         {
            display[i][j] = LEDBORDER;
         }
         if((i >= BORDERTHICK && i < HEIGHT - BORDERTHICK) && (j >= BORDERTHICK && j < WIDTH - BORDERTHICK))  // area between borders is playingfield
         {
            display[i][j] = LEDOFF;
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
         display[i][j] = LEDOFF;
      }
   }
   printField();
}

//End of display states
//-----------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------//
//Display Snake


void displaySnakePosition()
{
   if (startPos == 1)
   {
      for(i = 1; i < SNAKELENGTH; i++)
      {

         snakeY[i] = STARTY;
         snakeX[i] = STARTX-i;

         display[snakeY[i]][snakeX[i]] = LEDSNAKE;

      }
      foodSpawnCollision();
      int Y = foodNoCollisionY();
      int X = foodNoCollisionX();

      display[Y][X] = LEDCOLLISON;
   }

   if (startPos == 0)
   {
      for(i = SNAKELENGTH + score; i > 0; i--)
      {
         snakeY[i] = snakeY[i-1];
         snakeX[i] = snakeX[i-1];

         display[snakeY[i]][snakeX[i]] = LEDSNAKE;
      }
      display[snakeY[SNAKELENGTH + score]][snakeX[SNAKELENGTH + score]] = LEDOFF;
      int Y = foodNoCollisionY();
      int X = foodNoCollisionX();

      display[Y][X] = LEDCOLLISON;
   }

   startPos = 0;

   snakeY[0] = positionHeadY();
   snakeX[0] = positionHeadX();
}


void displaySnake()
{
   standardDisplay();                                 // using standarddisplay to set background

   displaySnakePosition();

   foodCollision();

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


