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


char checkBorderCollision(int position[2])
{

   if(position[0] <= 1 || position[0] >= 38)
   {
      return '*';
   }
   if(position[1] <= 1 || position[1] >= 38)
   {
      return '*';
   }

   return 'G';
}

