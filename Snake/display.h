#ifndef DISPLAY_H
#define DISPLAY_H

void displaySnake();
void displayMenu(void);
void displayShutDown(void);
void displayConfirmReset(void);
void displayConfirmMenu(void);
void addToDisplay(int Y, int X, char LED);

extern int snakeY[255];
extern int snakeX[255];
extern int score;

#endif // DISPLAY_H
