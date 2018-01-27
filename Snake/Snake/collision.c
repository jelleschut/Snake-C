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

