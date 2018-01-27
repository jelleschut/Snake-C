#include "display.h"
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int snakeHeadY = 8;
int snakeHeadX = 20;

void positionHead(int movement[2])
{
   int position[2];

   snakeHeadY += movement[0];                             // Y coordinate updated for movement
   snakeHeadX += movement[1];

   position[0] = snakeHeadY;
   position[1] = snakeHeadX;

   printf("%d, %d\n", position[1], position[0]);

   displaySnake(position);

}

void move(int direction)
{
   int snakeHead[2] = {snakeHeadY, snakeHeadX};
   int movement[2];

   switch(direction)
   {
      case 0:
         movement[0] = 0;
         movement[1] = 0;
         positionHead(movement);
         break;
      case 1:
         movement[0] = -1;
         movement[1] = 0;
         positionHead(movement);
         break;
      case 2:
         movement[0] = 0;
         movement[1] = 1;
         positionHead(movement);
         break;
      case 3:
         movement[0] = 1;
         movement[1] = 0;
         positionHead(movement);
         break;
      case 4:
         movement[0] = 0;
         movement[1] = -1;
         positionHead(movement);
         break;
      case 5:
         snakeHead[0] = 8;
         snakeHead[1] = 20;
         displaySnake(snakeHead);
      default:
         movement[0] = 0;
         movement[1] = 0;
   }
}
