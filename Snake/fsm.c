#include <stdio.h>
#include <unistd.h>

#include "macros.h"
#include "keyboard.h"
#include "display.h"
#include "position.h"
#include "collision.h"

STATES previousState;
STATES returnState = 0;
STATES nextState;
STATES currentState = ST_INITIALISE;
STATES mode;

EVENTS event = EVT_NO;


EVENTS nextEvent();

void eventhandler(EVENTS event)
{
   nextState = ST_NO;

   switch(currentState)
   {
      case ST_NO:
         printf("error\n");
         break;


      case ST_INITIALISE:
         score = 0;
         displayScreen(currentState);
         event = keyboardInput();
         switch(event)
         {
            case EVT_START_GAME:
               nextState = ST_GAME_START;
               break;
            case EVT_SHUT_DOWN:
               nextState = ST_SHUT_DOWN;
               break;
            case EVT_MODE_0:
               mode = ST_MODE_0;
               nextState = ST_INITIALISE;
               break;
            case EVT_MODE_1:
               mode = ST_MODE_1;
               nextState = ST_INITIALISE;
               break;
            default:
               nextState = ST_INITIALISE;
         }
         break;

      case ST_SHUT_DOWN:
         displayScreen(currentState);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_X:
               nextState = ST_INITIALISE;
               break;
            default:
               nextState = ST_SHUT_DOWN;
         }
         break;

      case ST_GAME_START:
         move(EVT_START_POSITION);
         displayScreen(currentState);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_UP:
               nextState = ST_SNAKE_UP;
               break;
            case EVT_KEY_RIGHT:
               nextState = ST_SNAKE_RIGHT;
               break;
            case EVT_KEY_DOWN:
               nextState = ST_SNAKE_DOWN;
               break;
            case EVT_KEY_LEFT:
               nextState = ST_SNAKE_RIGHT;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            default:
               nextState = ST_GAME_START;
         }
         break;

      case ST_SNAKE_UP:
         move(EVT_CHANGE_DIRECTION_UP);
         displayScreen(currentState);
         usleep(DELAY);
         event = nextEvent();
         switch(event)
         {
            case EVT_KEY_RIGHT:
               nextState = ST_SNAKE_RIGHT;
               break;
            case EVT_KEY_LEFT:
               returnState = currentState;
               nextState = ST_SNAKE_LEFT;
               break;
            case EVT_KEY_M:
               returnState = currentState;
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               returnState = currentState;
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               returnState = currentState;
               nextState = ST_PAUSE;
               break;
            case EVT_COLLISION:
               nextState = ST_GAME_OVER;
               break;
            default:
               nextState = ST_SNAKE_UP;
               event = keyboardMovement();
         }
         break;

      case ST_SNAKE_RIGHT:
         move(EVT_CHANGE_DIRECTION_RIGHT);
         displayScreen(currentState);
         usleep(DELAY);
         event = nextEvent();
         switch(event)
         {
            case EVT_KEY_UP:
               nextState = ST_SNAKE_UP;
               break;
            case EVT_KEY_DOWN:
               nextState = ST_SNAKE_DOWN;
               break;
            case EVT_KEY_M:
               returnState = currentState;
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               returnState = currentState;
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               returnState = currentState;
               nextState = ST_PAUSE;
               break;
            case EVT_COLLISION:
               nextState = ST_GAME_OVER;
               break;
            default:
               nextState = ST_SNAKE_RIGHT;
               event = keyboardMovement();
         }
         break;

      case ST_SNAKE_DOWN:
         move(EVT_CHANGE_DIRECTION_DOWN);
         displayScreen(currentState);
         usleep(DELAY);
         event = nextEvent();
         switch(event)
         {
            case EVT_KEY_RIGHT:
               nextState = ST_SNAKE_RIGHT;
               break;
            case EVT_KEY_LEFT:
               nextState = ST_SNAKE_LEFT;
               break;
            case EVT_KEY_M:
               returnState = currentState;
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               returnState = currentState;
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               returnState = currentState;
               nextState = ST_PAUSE;
               break;
            case EVT_COLLISION:
               nextState = ST_GAME_OVER;
               break;
            default:
               nextState = ST_SNAKE_DOWN;
               event = keyboardMovement();
         }
         break;

      case ST_SNAKE_LEFT:
         move(EVT_CHANGE_DIRECTION_LEFT);
         displayScreen(currentState);
         usleep(DELAY);
         event = nextEvent();
         switch(event)
         {
            case EVT_KEY_UP:
               nextState = ST_SNAKE_UP;
               break;
            case EVT_KEY_DOWN:
               nextState = ST_SNAKE_DOWN;
               break;
            case EVT_KEY_M:
               returnState = currentState;
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               returnState = currentState;
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               returnState = currentState;
               nextState = ST_PAUSE;
               break;
            case EVT_COLLISION:
               nextState = ST_GAME_OVER;
               break;
            default:
               nextState = ST_SNAKE_LEFT;
               event = keyboardMovement();
         }
         break;

      case ST_CONFIRM_M:
         displayScreen(currentState);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_N:
               nextState = ST_PAUSE;
               break;
            case EVT_KEY_Y:
               nextState = ST_INITIALISE;
               break;
            default:
               nextState = ST_CONFIRM_M;
         }
         break;

      case ST_CONFIRM_R:
         displayScreen(currentState);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_N:
               nextState = ST_PAUSE;
               break;
            case EVT_KEY_Y:
               nextState = ST_GAME_START;
               break;
            default:
               nextState = ST_CONFIRM_R;
         }
         break;

      case ST_GAME_OVER:
         displayScreen(currentState);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_Y:
               nextState = ST_INITIALISE;
               break;
            default:
               nextState = ST_GAME_OVER;
         }
         break;

      case ST_PAUSE:
         move(EVT_PAUSE_POSITION);
         displayScreen(currentState);
         event = keyboardInput();
         switch(event)
         {
            case EVT_KEY_M:
               nextState = ST_CONFIRM_M;
               break;
            case EVT_KEY_R:
               nextState = ST_CONFIRM_R;
               break;
            case EVT_KEY_P:
               nextState = returnState;
               break;
            default:
               nextState = ST_PAUSE;
         }
         break;
      default:
         printf("default");
         nextState = ST_NO;

   }
   printf("score: %d\n", score);
   currentState = nextState;
}




EVENTS nextEvent()
{
   EVENTS next = keyboardMovement();
   if(collisionChecker() == EVT_COLLISION)
   {
      next = EVT_COLLISION;
   }

   return next;
}
