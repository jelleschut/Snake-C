#include "fsm.h"
#include <dos.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

EVENTS keyboardInput(void)
{
   EVENTS event;
   char input, inputLowerCase;
   fflush(stdin);
   input = getch();

   inputLowerCase = tolower(input);

   switch(inputLowerCase)
   {
      case 'w':
         event = EVT_KEY_UP;
         break;
      case 'd':
         event = EVT_KEY_RIGHT;
         break;
      case 's':
         event = EVT_KEY_DOWN;
         break;
      case 'a':
         event = EVT_KEY_LEFT;
         break;
      case 'p':
         event = EVT_KEY_P;
         break;
      case 'm':
         event = EVT_KEY_M;
         break;
      case 'r':
         event = EVT_KEY_R;
         break;
      case 'x':
         event = EVT_KEY_X;
         break;
      case 'y':
         event = EVT_KEY_Y;
         break;
      case 'n':
         event = EVT_KEY_N;
         break;
      case '1':
         event = EVT_START_GAME;
         break;
      case '2':
         event = EVT_SHUT_DOWN;
         break;
      case ')':
         event = EVT_MODE_0;
         break;
      case '!':
         event = EVT_MODE_1;
         break;
      default:
         event = EVT_NO;
   }
   return event;
}


EVENTS keyboardMovement(void)
{
   EVENTS event;
   char input, inputLowerCase;

   fflush(stdin);
   if(kbhit())
   {
      input = getch();
   }

      inputLowerCase = tolower(input);

   switch(inputLowerCase)
   {
      case 'w':
         event = EVT_KEY_UP;
         break;
      case 'd':
         event = EVT_KEY_RIGHT;
         break;
      case 's':
         event = EVT_KEY_DOWN;
         break;
      case 'a':
         event = EVT_KEY_LEFT;
         break;
      case 'p':
         event = EVT_KEY_P;
         break;
      case 'm':
         event = EVT_KEY_M;
         break;
      case 'r':
         event = EVT_KEY_R;
         break;
      case 'x':
         event = EVT_KEY_X;
         break;
      case 'y':
         event = EVT_KEY_Y;
         break;
      case 'n':
         event = EVT_KEY_N;
         break;
      case '1':
         event = EVT_START_GAME;
         break;
      case '2':
         event = EVT_SHUT_DOWN;
         break;
      default:
         event = EVT_NO;
   }

   return event;
}
