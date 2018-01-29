#include <stdio.h>

#include "display.h"
#include "fsm.h"
#include "position.h"
#include "macros.h"

int foodY;
int foodX;


EVENTS borderCollision()
{
   int Y = positionHeadY();
   int X = positionHeadX();

   if(Y < BORDERTHICK || Y >= (HEIGHT - BORDERTHICK))
   {
      return EVT_BORDER_COLLISION;
   }
   if(X < BORDERTHICK || X >= (WIDTH - BORDERTHICK))
   {
      return EVT_BORDER_COLLISION;
   }
   return EVT_NO_BORDER_COLLISION;
}

EVENTS selfCollision()
{
   int i;
   int Y = positionHeadY();
   int X = positionHeadX();

   for (i = 2; i < SNAKELENGTH + score; i++)
   {
      if(( Y == snakeY[i]) && ( X == snakeX[i]))
      {
         return EVT_SELF_COLLISION;
      }
   }
   return EVT_NO_SELF_COLLISION;
}

EVENTS foodSpawnCollision()
{
   int i;
   foodY = positionFoodY();
   foodX = positionFoodX();

   for (i = 0; i < SNAKELENGTH + score; i++)
   {
      if(( foodY == snakeY[i]) && ( foodX == snakeX[i]))
      {
           return EVT_FOOD_SPAWN_COLLISION;
      }
   }
   return EVT_FOOD_SPAWN_NO_COLLISION;
}

int foodNoCollisionY()
{
   return foodY;
}

int foodNoCollisionX()
{
   return foodX;
}

EVENTS foodCollision()
{
   if((foodY == snakeY[0]) && (foodX == snakeX[0]))
   {
      return EVT_FOOD_COLLISION;
   }
   return EVT_NO_FOOD_COLLISION;
}

EVENTS collisionChecker()
{
   if (borderCollision() == EVT_BORDER_COLLISION)
   {
      return EVT_COLLISION;
   }

   if(selfCollision() == EVT_SELF_COLLISION)
   {
      return EVT_COLLISION;
   }

   return EVT_NO_COLLISION;
}
