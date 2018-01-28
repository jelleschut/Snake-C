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

int foodPositionY = 0;
int foodPositionX = 0;
int i;

int borderCollision()
{
   int Y = positionHeadY();
   int X = positionHeadX();

   if(Y <= 1 || Y >= 38)
   {
      return 1;
   }
   if(X <= 1 || X >= 38)
   {
      return 1;
   }
   return 0;
}

void foodSpawnCollision()
{
   foodPositionY = positionFoodY();
   foodPositionX = positionFoodX();

   for (i = 0; i < SNAKELENGTH + score; i++)
   {
      if((foodPositionY == snakeY[i]) && (foodPositionX == snakeX[i]))
      {
         randomFoodY();
         randomFoodX();
         foodPositionY = positionFoodY();
         foodPositionX = positionFoodX();
         i = 0;

      }
   }
}

int foodNoCollisionY()
{
   return foodPositionY;
}

int foodNoCollisionX()
{
   return foodPositionX;
}

void foodCollision()
{
   if((foodPositionY == snakeY[0]) && (foodPositionX == snakeX[0]))
   {
      foodSpawnCollision();
      score++;
   }
}
