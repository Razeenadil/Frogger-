#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "initGPIO.h"
#include <sys/mman.h>
#include "framebuffer.h"
#include "SNESSController.h"
#include "drawFunctions.h"
#include "pixelStruct.h"
#include "gameOptions.h"
#include "mainMenu.h"
#include "stage1.h"
#include "stageCars.h"
#include "stageLogs.h"
#include "stageRobots.h"
#include "winScreen.h"



#define clearConsole() printf("\e[1;1H\e[2J")

struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);


/* Main function. This function controlls how the game works.
 	 Calls the levels and keeps track of score, time, moves
	 and all other game values.
*/
int main(){

    /* initialize + get FBS */
    framebufferstruct = initFbInfo();

    // Initializing gameOptions struct
    GameOptions gameValues;
    gameValues.score = 0;
    gameValues.lives = 8;
    gameValues.time = 80;
    gameValues.pauseButtonPressed = 0;
    gameValues.movesLeft = 120;
    gameValues.loseFlag = 0;
    gameValues.value1 = 0;
    gameValues.valueCars = 0;
    GameOptions *gameValuesPtr = &gameValues;




    /* initialize a pixel */
    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));
    int i=0;
    unsigned int quarter,byte,word;
    int height = 16;
    int width = 16;
    int ystart = 0;
    int xstart = 0;

    int initLives = gameValues.lives;
    int initTime = gameValues.time;
    int initMoves = gameValues.movesLeft;

    unsigned int *gpioPtr = getGPIOPtr();
    int buttonArray[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    int num = 0;
    initSNES(gpioPtr);
    int gray = 0x7BEF;
    int endGame = 0;


    clearConsole();


    //loop to play the game and reach differnt levels. Check if the game is
    //paused, reset, or quit every time.
    while (1) {
        int mainMenuScreen = drawMainMenu(pixel, gpioPtr, buttonArray);

        while (mainMenuScreen == 1) {
            int stage1Result = playStage1(pixel, gpioPtr, buttonArray, gameValuesPtr);	//the first stage

            // Restart Game
            if (stage1Result == 0) {
                gameValues.lives = initLives;
                gameValues.time = initTime;
                gameValues.movesLeft = initMoves;
                gameValues.pauseButtonPressed = 0;

            }
            // Quit Game
            if (stage1Result == 1) {
                gameValues.lives = initLives;
                gameValues.time = initTime;
                gameValues.movesLeft = initMoves;
                gameValues.pauseButtonPressed = 0;
                mainMenuScreen = 2;
            }

            if (stage1Result == 3) {
                while (stage1Result == 3) {
                    int stageRobotResult = playStageRobot(pixel, gpioPtr, buttonArray, gameValuesPtr);	//second stage
                    // Restart Game
                    if (stageRobotResult == 0) {
                        stage1Result = 4;
                        gameValues.lives = initLives;
                        gameValues.time = initTime;
                        gameValues.movesLeft = initMoves;
                        gameValues.pauseButtonPressed = 0;
                    }

                    // Quit Game
                    if (stageRobotResult == 1) {
                        gameValues.lives = initLives;
                        gameValues.time = initTime;
                        gameValues.movesLeft = initMoves;
                        gameValues.pauseButtonPressed = 0;
                        stage1Result = 4;
                        mainMenuScreen = 2;
                    }
                    if (stageRobotResult == 3) {
                        while (stageRobotResult == 3) {
                            int stageCarResult = playStageCar(pixel, gpioPtr, buttonArray, gameValuesPtr);	//thrid stage
                            // Restart Game
                            if (stageCarResult == 0) {
                                stage1Result = 4;
                                stageRobotResult = 4;
                                gameValues.lives = initLives;
                                gameValues.time = initTime;
                                gameValues.movesLeft = initMoves;
                                gameValues.pauseButtonPressed = 0;
                            }

                            // Quit Game
                            if (stageCarResult == 1) {
                                gameValues.lives = initLives;
                                gameValues.time = initTime;
                                gameValues.movesLeft = initMoves;
                                gameValues.pauseButtonPressed = 0;
                                stage1Result = 4;
                                stageRobotResult = 4;
                                mainMenuScreen = 2;
                            }

                            if (stageCarResult == 3) {
                                while (stageCarResult == 3) {
                                    int stageLogResult = playStageLogs(pixel, gpioPtr, buttonArray, gameValuesPtr); //final stage
                                    // Restart Game
                                    if (stageLogResult == 0) {
                                        stage1Result = 4;
                                        stageRobotResult = 4;
                                        stageCarResult = 4;
                                        gameValues.lives = initLives;
                                        gameValues.time = initTime;
                                        gameValues.movesLeft = initMoves;
                                        gameValues.pauseButtonPressed = 0;
                                    }

                                    // Quit Game
                                    if (stageLogResult == 1) {
                                        gameValues.lives = initLives;
                                        gameValues.time = initTime;
                                        gameValues.movesLeft = initMoves;
                                        gameValues.pauseButtonPressed = 0;
                                        stage1Result = 4;
                                        stageRobotResult = 4;
                                        stageCarResult = 4;
                                        mainMenuScreen = 2;
                                    }
                                    //final part of the game has been reached and the game is won
                                    if (stageLogResult == 3) {

                                        int finalScore = gameValues.score;
                                        int input = drawWinScreen(gpioPtr, buttonArray, finalScore);
                                        if (input == 1) {
                                            gameValues.lives = initLives;
                                            gameValues.time = initTime;
                                            gameValues.movesLeft = initMoves;
                                            gameValues.pauseButtonPressed = 0;

                                            stage1Result = 4;
                                            stageRobotResult = 4;
                                            stageCarResult = 4;
                                            mainMenuScreen = 2;
                                        }

                                    }


                                }

                            }
                        }
                    }

                }
            }
        }
        if (mainMenuScreen == 0) {
            break;
        }
    }
    printf("Exited Game Successfully\n");

    /* free pixel's allocated memory */
    free(pixel);
    pixel = NULL;
    munmap(framebufferstruct.fptr, framebufferstruct.screenSize);

    return 0;
}


/* Draw a pixel */
void drawPixel(Pixel *pixel){
    long int location =(pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
        (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
    *((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}
