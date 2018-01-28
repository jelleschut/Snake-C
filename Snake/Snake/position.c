#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <time.h>

#include "display.h"
#include "macros.h"
#include "snakebody.h"

int snakeHeadY = STARTY;
int snakeHeadX = STARTX;
int randFoodY;
int randFoodX;
int movement[2] = {0,0};
int start = 0;

void positionStart()
{
   snakeHeadY = STARTY;
   snakeHeadX = STARTX;
   movement[0] = 0;
   movement[1] = 0;
}

void positionHead()
{
   if(start == 1)
   {
      positionStart();
      start = 0;
   }

   snakeHeadY += movement[0];                             // Y coordinate updated for movement
   snakeHeadX += movement[1];
}

void move(int direction)
{

   switch(direction)
   {
      case 0:
         movement[0] = 0;
         movement[1] = 0;
         break;
      case 1:
         movement[0] = -1;
         movement[1] = 0;
          break;
      case 2:
         movement[0] = 0;
         movement[1] = 1;
         break;
      case 3:
         movement[0] = 1;
         movement[1] = 0;
         break;
      case 4:
         movement[0] = 0;
         movement[1] = -1;
         break;
      case 5:
         start = 1;
      default:
         movement[0] = 0;
         movement[1] = 0;
   }

   positionHead();
}

int positionHeadY()
{
   return snakeHeadY;
}

int positionHeadX()
{
   return snakeHeadX;
}

void randomFoodY()
{
   srand(time(NULL));
   randFoodY = rand() % (HEIGHT - (2 * BORDERTHICK)) + BORDERTHICK;
}

int positionFoodY()
{
   return randFoodY;
}

void randomFoodX()
{
   srand(time(NULL));
   randFoodX = rand() % (WIDTH - (2 * BORDERTHICK)) + BORDERTHICK;
}

int positionFoodX()
{
   return randFoodX;
}

