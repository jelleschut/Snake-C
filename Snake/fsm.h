#ifndef SNAKE_H
#define SNAKE_H

typedef enum
{
   ST_NO,
   ST_SHUT_DOWN,
   ST_INITIALISE,
   ST_MENU,
   ST_GAME_START,
   ST_GAME_RUN,
   ST_GAME_OVER,
   ST_SNAKE_UP,
   ST_SNAKE_RIGHT,
   ST_SNAKE_DOWN,
   ST_SNAKE_LEFT,
   ST_CONFIRM_M,
   ST_CONFIRM_R,
   ST_CONFIRM_Q,
   ST_PAUSE
}  STATES;

typedef enum
{
   EVT_NO,
   EVT_START_GAME,
   EVT_SHUT_DOWN,
   EVT_KEY_UP,
   EVT_KEY_DOWN,
   EVT_KEY_LEFT,
   EVT_KEY_RIGHT,
   EVT_KEY_M,
   EVT_KEY_R,
   EVT_KEY_P,
   EVT_KEY_X,
   EVT_KEY_Y,
   EVT_KEY_N,
}  EVENTS;

void eventhandler(EVENTS event);

#endif // SNAKE_H
