#include <stdio.h>
#include "macros.h"
#include "position.h"
#include "display.h"

int i;

void startSnake()
{
   for(i = 0; i < SNAKELENGTH; i++)
   {
      int snakeStartX[SNAKELENGTH];
      snakeStartX[i] = positionHeadX() - i;
      addToDisplay(STARTY, snakeStartX[i], LEDSNAKE);
   }
}
/*
for(i = 0; i < SNAKELENGTH + score; i++)
{
   int snakePositionY[255];
   int snakePositionX[255];
   positionHeadY();
}*/
