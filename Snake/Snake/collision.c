#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "display.h"
#include "fsm.h"
#include "position.h"
#include "display.h"
#include "macros.h"

int foodY = 0;
int foodX = 0;
int i;

int borderCollision()
{
   int Y = positionHeadY();
   int X = positionHeadX();

   if(Y <= (BORDERTHICK - 1) || Y >= (HEIGHT - BORDERTHICK))
   {
      return 1;
   }
   if(X <= (BORDERTHICK - 1) || X >= (WIDTH - BORDERTHICK))
   {
      return 1;
   }
   return 0;
}

int selfCollision()
{
   int Y = positionHeadY();
   int X = positionHeadX();

   for (i = 2; i < SNAKELENGTH + score; i++)
   {
      if(( Y == snakeY[i]) && ( X == snakeX[i]))
      {
         return 1;
      }
   }
   return 0;
}

void foodSpawnCollision()
{
   foodY = positionFoodY();
   foodX = positionFoodX();

   for (i = 0; i < SNAKELENGTH + score; i++)
   {
      if(( foodY == snakeY[i]) && ( foodX == snakeX[i]))
      {
         randomFoodY();
         randomFoodX();
         foodY = positionFoodY();
         foodX = positionFoodX();
         i = 0;
      }
   }
}

int foodNoCollisionY()
{
   return foodY;
}

int foodNoCollisionX()
{
   return foodX;
}

void foodCollision()
{
   if((foodY == snakeY[0]) && (foodX == snakeX[0]))
   {
      foodSpawnCollision();
      score++;
   }
}

int checkGameOver()
{
   if((selfCollision() == 1) || (borderCollision() == 1))
   {
      return 1;
   }
   return 0;
}
