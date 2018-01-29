#ifndef DISPLAY_H
#define DISPLAY_H

#include "fsm.h"

void displayScreen(STATES currentState);


extern int snakeY[255];
extern int snakeX[255];
extern int score;

#endif // DISPLAY_H
