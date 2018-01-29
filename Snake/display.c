#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fsm.h"
#include "position.h"
#include "collision.h"
#include "macros.h"

char display[HEIGHT][WIDTH];                         // actual playing field in characters
int score = 0;
int snakeY[255];
int snakeX[255];
typedef char PIXELMAP[7][5];

void screenShot();

//-----------------------------------------------------------------------------------------------------//
// Basic screen functions

//Printing screen to terminal
void printField(void)
{
   int i,j;

   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         printf("%c", display[i][j]);                  // printing the playingfield
      }
      printf("\n");
   }
}

//Empty display with borders
void standardDisplay(void)
{
   int i,j;
   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         if(i < BORDERTHICK)                                       // top 2 lines are borders
         {
            display[i][j] = LEDBORDER;
         }
         if(i >= HEIGHT - BORDERTHICK && i < HEIGHT)               // bottom 2 lines are borders
         {
            display[i][j] = LEDBORDER;
         }
         if(j < BORDERTHICK)                                       // first 2 columns are borders
         {
            display[i][j] = LEDBORDER;
         }
         if(j >= WIDTH - BORDERTHICK && i < WIDTH)                 // last 2 borders are columns
         {
            display[i][j] = LEDBORDER;
         }
         if((i >= BORDERTHICK && i < HEIGHT - BORDERTHICK) && (j >= BORDERTHICK && j < WIDTH - BORDERTHICK))  // area between borders is playingfield
         {
            display[i][j] = LEDOFF;
         }
      }
   }
}

//String writing function
void writeString(int startY, char *string)
{
   int i;
   int lengthString  = strlen(string);
   int startX = (WIDTH/2) - (lengthString/2);

   for (i = 0; i < lengthString; i++)
   {
      display[startY][startX+i] = string[i];
   }
}
//Writing strings in pixel form
void writePixel(int startY, int startX, PIXELMAP string)
{
   int i,j;
   for(i = 0; i < 7; i++)
   {
      for (j = 0; j < 5; j++)
      {
         display[startY+i][startX+j] = string[i][j];
      }
   }
}


//end of basic screen functions
//-----------------------------------------------------------------------------------------------------//


//-----------------------------------------------------------------------------------------------------//
//Display States

void displayMenuPixel()
{

   PIXELMAP oneStart    =     PIXEL1;
   PIXELMAP colonStart  =     PIXELCOLON;
   PIXELMAP sStart      =     PIXELS;
   PIXELMAP tStart      =     PIXELT;
   PIXELMAP aStart      =     PIXELA;
   PIXELMAP rStart      =     PIXELR;
   PIXELMAP t2Start     =     PIXELT;

   PIXELMAP twoQuit     =     PIXEL2;
   PIXELMAP colonQuit   =     PIXELCOLON;
   PIXELMAP qQuit       =     PIXELQ;
   PIXELMAP uQuit       =     PIXELU;
   PIXELMAP iQuit       =     PIXELI;
   PIXELMAP tQuit       =     PIXELT;

   standardDisplay();

   writePixel(6,9,oneStart);
   writePixel(6,15,colonStart);
   writePixel(6,21,sStart);
   writePixel(6,27,tStart);
   writePixel(6,33,aStart);
   writePixel(6,39,rStart);
   writePixel(6,45,t2Start);

   writePixel(17,9,twoQuit);
   writePixel(17,15,colonQuit);
   writePixel(17,21,qQuit);
   writePixel(17,27,uQuit);
   writePixel(17,33,iQuit);
   writePixel(17,39,tQuit);
}

void displayPausePixel()
{
   PIXELMAP pPause      =     PIXELP;
   PIXELMAP aPause      =     PIXELA;
   PIXELMAP uPause      =     PIXELU;
   PIXELMAP sPause      =     PIXELS;
   PIXELMAP ePause      =     PIXELE;

   PIXELMAP pPressP     =     PIXELP;
   PIXELMAP rPressP     =     PIXELR;
   PIXELMAP ePressP     =     PIXELE;
   PIXELMAP sPressP     =     PIXELS;
   PIXELMAP s2PressP    =     PIXELS;
   PIXELMAP P2PressP    =     PIXELP;

   screenShot();

   writePixel(6,15,pPause);
   writePixel(6,21,aPause);
   writePixel(6,27,uPause);
   writePixel(6,33,sPause);
   writePixel(6,39,ePause);

   writePixel(17,9,pPressP);
   writePixel(17,15,rPressP);
   writePixel(17,21,ePressP);
   writePixel(17,27,sPressP);
   writePixel(17,33,s2PressP);

   writePixel(17,45,P2PressP);
}

void displayconfirmMenuPixel()
{
   PIXELMAP mMenu       =     PIXELM;
   PIXELMAP eMenu       =     PIXELE;
   PIXELMAP nMenu       =     PIXELN;
   PIXELMAP uMenu       =     PIXELU;
   PIXELMAP questionMenu=     PIXELQUESTION;

   PIXELMAP yYesNO      =     PIXELY;
   PIXELMAP slashYesNO  =     PIXELSLASH;
   PIXELMAP nYesNO      =     PIXELN;

   screenShot();

   writePixel(6,15,mMenu);
   writePixel(6,21,eMenu);
   writePixel(6,27,nMenu);
   writePixel(6,33,uMenu);
   writePixel(6,39,questionMenu);

   writePixel(17,21,yYesNO);
   writePixel(17,27,slashYesNO);
   writePixel(17,33,nYesNO);

}

void displayConfirmResetPixel()
{
   PIXELMAP rReset      =     PIXELR;
   PIXELMAP eReset      =     PIXELE;
   PIXELMAP sReset      =     PIXELS;
   PIXELMAP e2Reset     =     PIXELE;
   PIXELMAP tReset      =     PIXELT;
   PIXELMAP questionReset=    PIXELQUESTION;

   PIXELMAP yYesNO      =     PIXELY;
   PIXELMAP slashYesNO  =     PIXELSLASH;
   PIXELMAP nYesNO      =     PIXELN;

   screenShot();

   writePixel(6,12,rReset);
   writePixel(6,18,eReset);
   writePixel(6,24,sReset);
   writePixel(6,30,e2Reset);
   writePixel(6,36,tReset);
   writePixel(6,42,questionReset);

   writePixel(17,21,yYesNO);
   writePixel(17,27,slashYesNO);
   writePixel(17,33,nYesNO);

}

void scorePixel()
{
   char charScore[5];
   int index, length, i;

   itoa(score, charScore, 10);
   length = strlen(charScore);

   static PIXELMAP matrixPixel[10]= {PIXEL0,PIXEL1,PIXEL2,PIXEL3,PIXEL4,PIXEL5,PIXEL6,PIXEL7,PIXEL8,PIXEL9};

   for(i = 0; i < length; i++)
   {
      switch(charScore[i])
      {
         case '0':
            index = 0;
            break;
         case '1':
            index = 1;
            break;
         case '2':
            index = 2;
            break;
         case '3':
            index = 3;
            break;
         case '4':
            index = 4;
            break;
         case '5':
            index = 5;
            break;
         case '6':
            index = 6;
            break;
         case '7':
            index = 7;
            break;
         case '8':
            index = 8;
            break;
         case '9':
            index = 9;
            break;
      }
      int xPos = (39 + (i * 6));
      writePixel(12, xPos, matrixPixel[index]);
   }

}

void displayGameOverPixel()
{
   PIXELMAP gGame       =     PIXELG;
   PIXELMAP aGame       =     PIXELA;
   PIXELMAP mGame       =     PIXELM;
   PIXELMAP eGame       =     PIXELE;
   PIXELMAP oOver       =     PIXELO;
   PIXELMAP vOver       =     PIXELV;
   PIXELMAP eOver       =     PIXELE;
   PIXELMAP rOver       =     PIXELR;

   PIXELMAP sScore      =     PIXELS;
   PIXELMAP cScore      =     PIXELC;
   PIXELMAP oScore      =     PIXELO;
   PIXELMAP rScore      =     PIXELR;
   PIXELMAP eScore      =     PIXELE;
   PIXELMAP colonScore  =     PIXELCOLON;

   PIXELMAP pPressY     =     PIXELP;
   PIXELMAP rPressY     =     PIXELR;
   PIXELMAP ePressY     =     PIXELE;
   PIXELMAP sPressY     =     PIXELS;
   PIXELMAP s2PressY    =     PIXELS;
   PIXELMAP yPressY     =     PIXELY;


   writePixel(4,3,gGame);
   writePixel(4,9,aGame);
   writePixel(4,15,mGame);
   writePixel(4,21,eGame);

   writePixel(4,33,oOver);
   writePixel(4,39,vOver);
   writePixel(4,45,eOver);
   writePixel(4,51,rOver);

   writePixel(12,3,sScore);
   writePixel(12,9,cScore);
   writePixel(12,15,oScore);
   writePixel(12,21,rScore);
   writePixel(12,27,eScore);
   writePixel(12,33,colonScore);

   scorePixel();

   writePixel(20,9,pPressY);
   writePixel(20,15,rPressY);
   writePixel(20,21,ePressY);
   writePixel(20,27,sPressY);
   writePixel(20,33,s2PressY);

   writePixel(20,45,yPressY);
}



//Main Menu
void displayMenu(void)
{
   char newGame[20]  = "1: NEW GAME ";
   char shutDown[20] = "2: SHUT DOWN";

   standardDisplay();

   writeString(6, newGame);
   writeString(10, shutDown);
}

//Return to main menu
void displayPause(void)
{
   char gamePaused[40] = "GAME PAUSED";
   char pressP[40] = "PRESS P TO CONTINUE";

   screenShot();

   writeString(7, gamePaused);
   writeString(9, pressP);
}

//Return to main menu
void displayConfirmMenu(void)
{
   char areYouSureReturn[40] = "ARE YOU SURE YOU WANT TO RETURN";
   char toMainMenu[40] = "TO MAIN MENU?";
   char yesOrNo[20] = "Y / N";

   screenShot();

   writeString(7, areYouSureReturn);
   writeString(8, toMainMenu);
   writeString(9, yesOrNo);
}

//Reset menu
void displayConfirmReset(void)
{
   char areYouSureReset[40] = "ARE YOU SURE YOU WANT TO RESET?";
   char yesOrNo[20] = "Y / N";

   screenShot();

   writeString(7, areYouSureReset);
   writeString(9, yesOrNo);

}

//Reset menu
void displayGameOver(void)
{
   char gameOver[40] = "GAME OVER";
   char finalScore[20] = "FINAL SCORE: ";
   char pressContinue[20] = "PRESS Y TO CONTINUE";
   char charScore[5];
   itoa(score, charScore, 10);
   strcat(finalScore, charScore);

   writeString(5, gameOver);
   writeString(7, finalScore);
   writeString(9, pressContinue);

}

//Display Off
void displayShutDown(void)
{
   int i,j;
   for(i = 0; i < HEIGHT; i++)
   {
      for(j = 0; j < WIDTH; j++)
      {
         display[i][j] = LEDOFF;
      }
   }
}
//End of display states
//-----------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------//
//Display Snake

void displayCollision(int Y, int X)
{
   display[Y-2][X+2] = LEDCOLLISON;
   display[Y-2][X-2] = LEDCOLLISON;
   display[Y-1][X-1] = LEDCOLLISON;
   display[Y-1][X+1] = LEDCOLLISON;
   display[Y][X] = LEDCOLLISON;
   display[Y+1][X-1] = LEDCOLLISON;
   display[Y+1][X+1] = LEDCOLLISON;
   display[Y+2][X-2] = LEDCOLLISON;
   display[Y+2][X+2] = LEDCOLLISON;

}

void displayNewFood()
{
   randomFoodX();
   randomFoodY();

   EVENTS spawnChecker = foodSpawnCollision();

   while(spawnChecker == EVT_FOOD_SPAWN_COLLISION)
   {
      foodSpawnCollision();
   }

   int Y = foodNoCollisionY();
   int X = foodNoCollisionX();

   display[Y][X] = LEDFOOD;
}

void displayFood()
{
   int Y = foodNoCollisionY();
   int X = foodNoCollisionX();

   display[Y][X] = LEDFOOD;
}


void displaySnakeStartPosition()
{
   int i;

   snakeY[0] = STARTY;
   snakeX[0] = STARTX;

   for(i = 0; i < SNAKELENGTH; i++)
   {

      snakeY[i+1] = STARTY;
      snakeX[i+1] = STARTX-i;

      display[snakeY[i+1]][snakeX[i+1]] = LEDSNAKE;

   }
}

void displaySnakePosition()
{
   int i;

   snakeY[0] = positionHeadY();
   snakeX[0] = positionHeadX();

   for(i = SNAKELENGTH + score; i > 0; i--)
   {
      snakeY[i] = snakeY[i-1];
      snakeX[i] = snakeX[i-1];

      display[snakeY[i]][snakeX[i]] = LEDSNAKE;
   }



}

void screenShot()
{
   int i;

   standardDisplay();
   for(i = 0; i < SNAKELENGTH + score; i++)
   {
      display[snakeY[i]][snakeX[i]] = LEDSNAKE;
   }
   displayFood();
}


void displayStart()
{
   standardDisplay();
   displaySnakeStartPosition();
   displayNewFood();
}

void displaySnake()
{
   standardDisplay();                                 // using standarddisplay to set background
   displaySnakePosition();
   displayFood();
}

void displayScreen(STATES currentState)
{
   STATES displayState = ST_DISPLAY_STANDBY;

   switch(mode)
   {
      case ST_MODE_0:
         switch(currentState)
         {
            case ST_SHUT_DOWN:
               displayShutDown();
               displayState = ST_DISPLAY_SHUT_DOWN;
               break;

            case ST_INITIALISE:
               displayMenu();
               displayState = ST_DISPLAY_MAIN_MENU;
               break;

            case ST_CONFIRM_M:
               displayConfirmMenu();
               displayState = ST_DISPLAY_CONFIRM_MENU;
               break;

            case ST_CONFIRM_R:
               displayConfirmReset();
               displayState = ST_DISPLAY_CONFIRM_RESET;
               break;

            case ST_PAUSE:
               displayPause();
               displayState = ST_DISPLAY_PAUSE;
               break;

            case ST_GAME_OVER:
               displayGameOver();
               displayState = ST_DISPLAY_GAME_OVER;
               break;

            case ST_GAME_START:
               displayStart();
               displayState = ST_DISPLAY_GAME_START;
               break;

            case ST_SNAKE_UP:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case ST_SNAKE_DOWN:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case ST_SNAKE_LEFT:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case ST_SNAKE_RIGHT:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            default:
               printf("Something went wrong!\n");
               printf("Nothing to display!\n");
         }
         break;

      case ST_MODE_1:
         switch(currentState)
         {
            case ST_SHUT_DOWN:
               displayShutDown();
               displayState = ST_DISPLAY_SHUT_DOWN;
               break;

            case ST_INITIALISE:
               displayMenuPixel();
               displayState = ST_DISPLAY_MAIN_MENU;
               break;

            case ST_CONFIRM_M:
               displayconfirmMenuPixel();
               displayState = ST_DISPLAY_CONFIRM_MENU;
               break;

            case ST_CONFIRM_R:
               displayConfirmResetPixel();
               displayState = ST_DISPLAY_CONFIRM_RESET;
               break;

            case ST_PAUSE:
               displayPausePixel();
               displayState = ST_DISPLAY_PAUSE;
               break;

            case ST_GAME_OVER:
               displayGameOverPixel();
               displayState = ST_DISPLAY_GAME_OVER;
               break;

            case ST_GAME_START:
               displayStart();
               displayState = ST_DISPLAY_GAME_START;
               break;

            case ST_SNAKE_UP:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case ST_SNAKE_DOWN:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case ST_SNAKE_LEFT:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            case ST_SNAKE_RIGHT:
               displaySnake();
               displayState = ST_DISPLAY_SNAKE;
               break;

            default:
               printf("Something went wrong!\n");
               printf("Nothing to display!\n");
         }
         break;
      default:
         mode = ST_MODE_0;
   }

   if(displayState == ST_DISPLAY_SNAKE)
   {
      EVENTS food = foodCollision();
      EVENTS collision = collisionChecker();

      if(food == EVT_FOOD_COLLISION)
      {
         score++;
         displayNewFood();
      }

      if (collision == EVT_COLLISION)
      {
         displayCollision(snakeY[0], snakeX[0]);
      }
   }
   printField();

}








