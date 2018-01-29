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
#include "fsm.h"

int snakeHeadY = STARTY;
int snakeHeadX = STARTX;
int randFoodY;
int randFoodX;
int movement[2] = {0,0};
STATES posState;

void positionStart()
{
   snakeHeadY = STARTY;
   snakeHeadX = STARTX;
   movement[0] = 0;
   movement[1] = 0;
}

void positionHead()
{
   if(posState == ST_START_POSITION)
   {
      positionStart();
   }

   snakeHeadY += movement[0];                             // Y coordinate updated for movement
   snakeHeadX += movement[1];
}

void move(EVENTS event)
{

   switch(event)
   {
      case EVT_PAUSE_POSITION:
         movement[0] = 0;
         movement[1] = 0;
         posState = ST_MOVE_STOP;
         break;
      case EVT_CHANGE_DIRECTION_UP:
         movement[0] = -1;
         movement[1] = 0;
         posState = ST_MOVE_UP;
         break;
      case EVT_CHANGE_DIRECTION_RIGHT:
         movement[0] = 0;
         movement[1] = 1;
         posState = ST_MOVE_RIGHT;
         break;
      case EVT_CHANGE_DIRECTION_DOWN:
         movement[0] = 1;
         movement[1] = 0;
         posState = ST_MOVE_DOWN;
         break;
      case EVT_CHANGE_DIRECTION_LEFT:
         movement[0] = 0;
         movement[1] = -1;
         posState = ST_MOVE_LEFT;
         break;
      case EVT_START_POSITION:
         posState = ST_START_POSITION;
         break;
      default:
         movement[0] = 0;
         movement[1] = 0;
         posState = ST_MOVE_STOP;
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

