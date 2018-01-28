#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include "macros.h"
#include "fsm.h"
#include "keyboard.h"
#include "display.h"
#include "position.h"

STATES previousState;
STATES nextState;
STATES currentState = ST_INITIALISE;
EVENTS event = EVT_NO;

int direction;

void eventhandler(EVENTS event)
{
   nextState = ST_NO;

   switch(currentState)
   {
      case ST_NO:
         printf("error\n");
         break;


      case ST_INITIALISE:
         displayMenu();
         event = keyboardInput();
         switch(event)
         {
            case EVT_START_GAME:
               nextState = ST_GAME_START;
               break;
            case EVT_SHUT_DOWN:
               nextState = ST_SHUT_DOWN;
               break;
            default:
               nextState = ST_INITIALISE;
         }
         break;

      case ST_SHUT_DOWN:
         displayShutDown();
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_X:
               nextState = ST_INITIALISE;
               break;
         }
         break;

      case ST_GAME_START:
         printf("begin START: direction = %d\n", direction);
         move(START);
         displaySnake();
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_UP:
               nextState = ST_SNAKE_UP;
               direction = UP;
               break;
            case EVT_KEY_RIGHT:
               nextState = ST_SNAKE_RIGHT;
               direction = RIGHT;
               break;
            case EVT_KEY_DOWN:
               nextState = ST_SNAKE_DOWN;
               direction = DOWN;
               break;
            case EVT_KEY_LEFT:
               nextState = ST_SNAKE_RIGHT;
               direction = RIGHT;
               break;
            default:
               nextState = ST_GAME_START;
         }
         break;

      case ST_SNAKE_UP:
         move(UP);
         displaySnake();
         usleep(DELAY);
         event = keyboardMovement();
         switch(event)
         {
            case EVT_KEY_RIGHT:
               nextState = ST_SNAKE_RIGHT;
               direction = RIGHT;
               break;
            case EVT_KEY_LEFT:
               nextState = ST_SNAKE_LEFT;
               direction = LEFT;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               nextState = ST_PAUSE;
               break;
            default:
               nextState = ST_SNAKE_UP;
               event = keyboardMovement();
         }
         break;

      case ST_SNAKE_RIGHT:
         move(RIGHT);
         displaySnake();
         usleep(DELAY);
         event = keyboardMovement();
         switch(event)
         {
            case EVT_KEY_UP:
               nextState = ST_SNAKE_UP;
               direction = UP;
               break;
            case EVT_KEY_DOWN:
               nextState = ST_SNAKE_DOWN;
               direction = DOWN;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               nextState = ST_PAUSE;
               break;
            default:
               nextState = ST_SNAKE_RIGHT;
               event = keyboardMovement();
         }
         break;

      case ST_SNAKE_DOWN:
         move(DOWN);
         displaySnake();
         usleep(DELAY);
         event = keyboardMovement();
         switch(event)
         {
            case EVT_KEY_RIGHT:
               nextState = ST_SNAKE_RIGHT;
               direction = RIGHT;
               break;
            case EVT_KEY_LEFT:
               nextState = ST_SNAKE_LEFT;
               direction = LEFT;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               nextState = ST_PAUSE;
               break;
            default:
               nextState = ST_SNAKE_DOWN;
               event = keyboardMovement();
         }
         break;

      case ST_SNAKE_LEFT:
         move(LEFT);
         displaySnake();
         usleep(DELAY);
         event = keyboardMovement();
         switch(event)
         {
            case EVT_KEY_UP:
               nextState = ST_SNAKE_UP;
               direction = UP;
               break;
            case EVT_KEY_DOWN:
               nextState = ST_SNAKE_DOWN;
               direction = DOWN;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               nextState = ST_PAUSE;
               break;
            default:
               nextState = ST_SNAKE_LEFT;
               event = keyboardMovement();
         }
         break;

      case ST_CONFIRM_M:
         displayConfirmMenu();
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_N:
               nextState = ST_SNAKE_UP;
               break;
            case EVT_KEY_Y:
               nextState = ST_INITIALISE;
               break;
            default:
               nextState = ST_CONFIRM_M;
         }
         break;

      case ST_CONFIRM_R:

         displayConfirmReset();
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_N:
               nextState = ST_SNAKE_UP;
               break;
            case EVT_KEY_Y:
               nextState = ST_GAME_START;
               break;
            default:
               nextState = ST_CONFIRM_R;
         }
         break;


        case ST_GAME_OVER:
         nextState = ST_INITIALISE;
         break;

         /*case ST_PAUSE:
            displaySnake(none);
            switch(event)
            {
               case EVT_KEY_UP:
                  if(direction != DOWN)
                  {
                     nextState = ST_GAME_RUN;
                     direction = up;
                  }
                  else
                  {
                     nextState = ST_PAUSE;
                  }
                  break;
               case EVT_KEY_RIGHT:
                  if(direction != LEFT)
                  {
                     nextState = ST_GAME_RUN;
                     direction = RIGHT;
                  }
                  else
                  {
                     nextState = ST_PAUSE;
                  }
                  break;
               case EVT_KEY_DOWN:
                  if(direction != up)
                  {
                     nextState = ST_GAME_RUN;
                     direction = DOWN;
                  }
                  else
                  {
                     nextState = ST_PAUSE;
                  }
                  break;
               case EVT_KEY_LEFT :
                  if(direction != RIGHT)
                  {
                     nextState = ST_GAME_RUN;
                     direction = LEFT;
                  }
                  else
                  {
                     nextState = ST_PAUSE;
                  }
                  
                  
            }*/


   }
   printf("%d\n",currentState);
   currentState = nextState;
}


