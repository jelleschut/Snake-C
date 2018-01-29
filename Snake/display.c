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

void screenShot();

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
void writeString(int startY, /*int startX,*/ char *string)
{
   int lengthString  = strlen(string);
   int startX = (WIDTH/2) - (lengthString/2);

   for (i = 0; i < lengthString; i++)
   {
      display[startY][startX+i] = string[i];
   }


}
//end of basic screen functions
//-----------------------------------------------------------------------------------------------------//


//-----------------------------------------------------------------------------------------------------//
//Display States

//Main Menu
void displayMenu(void)
{
   char newGame[20]  = "1: NEW GAME ";
   char shutDown[20] = "2: SHUT DOWN";

   standardDisplay();

   writeString(6, /*10,*/ newGame);
   writeString(10, /*10,*/ shutDown);
}

//Return to main menu
void displayPause(void)
{
   char gamePaused[40] = "GAME PAUSED";
   char pressP[40] = "PRESS P TO CONTINUE";

   screenShot();

   writeString(7, /*4,*/ gamePaused);
   writeString(9, /*18,*/ pressP);
}

//Return to main menu
void displayConfirmMenu(void)
{
   char areYouSureReturn[40] = "ARE YOU SURE YOU WANT TO RETURN";
   char toMainMenu[40] = "TO MAIN MENU?";
   char yesOrNo[20] = "Y / N";

   screenShot();

   writeString(7, /*4,*/ areYouSureReturn);
   writeString(8, /*14,*/ toMainMenu);
   writeString(9, /*18,*/ yesOrNo);
}

//Reset menu
void displayConfirmReset(void)
{
   char areYouSureReset[40] = "ARE YOU SURE YOU WANT TO RESET?";
   char yesOrNo[20] = "Y / N";

   screenShot();

   writeString(7,/* 4,*/ areYouSureReset);
   writeString(9, /*18,*/ yesOrNo);

}

//Reset menu
void displayGameOver(void)
{
   char gameOver[40] = "GAME OVER";
   char finalScore[20] = "FINAL SCORE: ";
   char pressContinue[20] = "PRESS Y TO CONTINUE";
   char charScore[5];
   itoa(score, charScore, 10);
   strcat(finalScore, charScore);

   writeString(5, /*15,*/ gameOver);
   writeString(7, /*12,*/ finalScore);
   writeString(9, /*11,*/ pressContinue);

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
}
//End of display states
//-----------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------//
//Display Snake

void displayCollision(int Y, int X)
{
   display[Y-2][X+2] = LEDCOLLISON;
   display[Y-2][X-2] = LEDCOLLISON;
   display[Y-1][X-1] = LEDCOLLISON;
   display[Y-1][X+1] = LEDCOLLISON;
   display[Y][X] = LEDCOLLISON;
   display[Y+1][X-1] = LEDCOLLISON;
   display[Y+1][X+1] = LEDCOLLISON;
   display[Y+2][X-2] = LEDCOLLISON;
   display[Y+2][X+2] = LEDCOLLISON;
   /*for(i = (Y - 1); i < (Y + 2); i++)
      for(j = (X - 1); j < (X + 2); j++)
      {
         display[i][j] = LEDCOLLISON;
      }*/
}

void displayNewFood()
{
   randomFoodX();
   randomFoodY();

   EVENTS spawnChecker = foodSpawnCollision();

   while(spawnChecker == EVT_FOOD_SPAWN_COLLISION)
   {
      foodSpawnCollision();
   }

   int Y = foodNoCollisionY();
   int X = foodNoCollisionX();

   display[Y][X] = LEDFOOD;
}

void displayFood()
{
   int Y = foodNoCollisionY();
   int X = foodNoCollisionX();

   display[Y][X] = LEDFOOD;
}


void displaySnakeStartPosition()
{

   for(i = 0; i < SNAKELENGTH; i++)
   {

      snakeY[i] = STARTY;
      snakeX[i] = STARTX-i;

      display[snakeY[i]][snakeX[i]] = LEDSNAKE;

   }
}

void displaySnakePosition()
{

   for(i = SNAKELENGTH + score; i > 0; i--)
   {
      snakeY[i] = snakeY[i-1];
      snakeX[i] = snakeX[i-1];

      display[snakeY[i]][snakeX[i]] = LEDSNAKE;
   }

   snakeY[0] = positionHeadY();
   snakeX[0] = positionHeadX();
}

void screenShot()
{
   standardDisplay();
   for(i = 0; i < SNAKELENGTH + score; i++)
   {
      display[snakeY[i]][snakeX[i]] = LEDSNAKE;
   }
   displayFood();
}


void displayStart()
{
   standardDisplay();
   displaySnakeStartPosition();
   displayNewFood();
}

void displaySnake()
{
   standardDisplay();                                 // using standarddisplay to set background
   displaySnakePosition();
   displayFood();
}

void displayScreen(STATES currentState)
{
   STATES displayState = ST_DISPLAY_STANDBY;

      switch(currentState)
      {
         case ST_SHUT_DOWN:
            displayShutDown();
            displayState = ST_DISPLAY_SHUT_DOWN;
            break;

         case ST_INITIALISE:
            displayMenu();
            displayState = ST_DISPLAY_MAIN_MENU;
            break;

         case ST_CONFIRM_M:
            displayConfirmMenu();
            displayState = ST_DISPLAY_CONFIRM_MENU;
            break;

         case ST_CONFIRM_R:
            displayConfirmReset();
            displayState = ST_DISPLAY_CONFIRM_RESET;
            break;

         case ST_PAUSE:
            displayPause();
            displayState = ST_DISPLAY_PAUSE;
            break;

         case ST_GAME_OVER:
            displayGameOver();
            displayState = ST_DISPLAY_GAME_OVER;
            break;

         case ST_GAME_START:
            displayStart();
            displayState = ST_DISPLAY_GAME_START;
            break;

         case ST_SNAKE_UP:
            displaySnake();
            displayState = ST_DISPLAY_SNAKE;
            break;

         case ST_SNAKE_DOWN:
            displaySnake();
            displayState = ST_DISPLAY_SNAKE;
            break;

         case ST_SNAKE_LEFT:
            displaySnake();
            displayState = ST_DISPLAY_SNAKE;
            break;

         case ST_SNAKE_RIGHT:
            displaySnake();
            displayState = ST_DISPLAY_SNAKE;
            break;

         default:
            printf("Something went wrong!\n");
            printf("Nothing to display!\n");
      }


      if(displayState == ST_DISPLAY_SNAKE)
      {
         EVENTS food = foodCollision();
         EVENTS collision = collisionChecker();

         if(food == EVT_FOOD_COLLISION)
         {
            score++;
            displayNewFood();
         }

         if (collision == EVT_COLLISION)
         {
            displayCollision(snakeY[0], snakeX[0]);
         }
      }
   printField();
}








