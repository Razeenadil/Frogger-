#include "drawFunctions.h"
#include "pixelStruct.h"
#include "gameOptions.h"
#include "SNESSController.h"
#include "pauseMenu.h"
#include "loseScreen.h"
#include "valuePacks.h"
#include "images/stage3Text.c"
#include "images/score.c"
#include "images/lives.c"
#include "images/time.c"
#include "images/moves.c"
#include "images/keroppi.c"
#include "images/froggySafe.c"
#include "images/carRight.c"
#include "images/carLeft.c"
#include "images/1.c"
#include "images/2.c"
#include "images/3.c"
#include "images/4.c"
#include "images/5.c"
#include "images/6.c"
#include "images/7.c"
#include "images/8.c"
#include "images/9.c"
#include "images/0.c"
#include <unistd.h>
#include <stdlib.h>
#include "winScreen.h"


#include <pthread.h>

#define clearConsole() printf("\e[1;1H\e[2J")

void *moveCarLeft(void *i);
void *moveCarRight(void *arguments);
void *updateTimeCars(void *arguments);
void *updateScoreCars(void *arguments); 

// Structure for the obstacles
struct obstacle {
    int obstacleX;
    int obstacleY;
    int speed;
    int paused;
    int exitCondition;
};

/*
This function starts the first stage and returns apporite values depending on the players outcome 
@param pixel -> pixel used to draw
@param gpioPtr -> Base GPIO address
@param buttonArray -> an array of buttons used to see which button is pressed
@param gameValues -> structure for game values 
*/
int playStageCar(Pixel *pixel, unsigned int *gpioPtr, int buttonArray[], GameOptions *gameValues) {

    int borderColor = 0x7E0;
    int black = 0x0000;
    int safeColor = 0x04B0;

    // Images
    short int *stage3Text1 = (short int *) stage3.pixel_data;
    short int *score = (short int *) scoreMsg.pixel_data;
    short int *lives = (short int *) livesMsg.pixel_data;
    short int *time = (short int *) timeMsg.pixel_data;
    short int *moves = (short int*) movesIMG.pixel_data;
    short int *frog = (short int *) froggy.pixel_data;
    short int *frogSafe = (short int*) froggySafeIMG.pixel_data;
    short int *one = (short int*) oneIMG.pixel_data;
    short int *two = (short int*) twoIMG.pixel_data;
    short int *three = (short int*) threeIMG.pixel_data;
    short int *four = (short int*) fourIMG.pixel_data;
    short int *five = (short int*) fiveIMG.pixel_data;
    short int *six = (short int*) sixIMG.pixel_data;
    short int *seven = (short int*) sevenIMG.pixel_data;
    short int *eight = (short int*) eightIMG.pixel_data;
    short int *nine = (short int*) nineIMG.pixel_data;
    short int *zero = (short int*) zeroIMG.pixel_data;

    // Initializing game values
    int numLives = gameValues -> lives;
    int numMoves = gameValues -> movesLeft;
    int currScore = gameValues -> score;
    int initTime = gameValues -> time;

    // Initializing the obstacles
    struct obstacle cars[15];
    cars[0].obstacleX = 1036;
    cars[0].obstacleY = 587;
    cars[0].speed = 1000000;
    cars[0].paused = 0;
    cars[0].exitCondition = 0;

    cars[1].obstacleX = 1100;
    cars[1].obstacleY = 587;
    cars[1].speed = 1000500;
    cars[1].paused = 0;
    cars[1].exitCondition = 0;

    cars[2].obstacleX = 537;
    cars[2].obstacleY = 523;
    cars[2].speed = 2000000;
    cars[2].paused = 0;
    cars[2].exitCondition = 0;

    cars[3].obstacleX = 665;
    cars[3].obstacleY = 523;
    cars[3].speed = 2000000;
    cars[3].paused = 0;
    cars[3].exitCondition = 0;

    cars[4].obstacleX = 1036;
    cars[4].obstacleY = 459;
    cars[4].speed = 1000000;
    cars[4].paused = 0;
    cars[4].exitCondition = 0;


    cars[5].obstacleX = 1100;
    cars[5].obstacleY = 459;
    cars[5].speed = 1000500;
    cars[5].paused = 0;
    cars[5].exitCondition = 0;


    cars[6].obstacleX = 1036;
    cars[6].obstacleY = 395;
    cars[6].speed = 1000000;
    cars[6].paused = 0;
    cars[6].exitCondition = 0;


    cars[7].obstacleX = 1100;
    cars[7].obstacleY = 395;
    cars[7].speed = 1000500;
    cars[7].paused = 0;
    cars[7].exitCondition = 0;


    cars[8].obstacleX = 601;
    cars[8].obstacleY = 331;
    cars[8].speed = 3000000;
    cars[8].paused = 0;
    cars[8].exitCondition = 0;


    cars[9].obstacleX = 665;
    cars[9].obstacleY = 331;
    cars[9].speed = 3000000;
    cars[9].paused = 0;
    cars[9].exitCondition = 0;


    cars[10].obstacleX = 665;
    cars[10].obstacleY = 267;
    cars[10].speed = 1000000;
    cars[10].paused = 0;
    cars[10].exitCondition = 0;

    cars[11].obstacleX = 665;
    cars[11].obstacleY = 203;
    cars[11].speed = 4000000;
    cars[11].paused = 0;
    cars[11].exitCondition = 0;

    cars[12].obstacleX = 729;
    cars[12].obstacleY = 203;
    cars[12].speed = 4000000;
    cars[12].paused = 0;
    cars[12].exitCondition = 0;


    cars[13].obstacleX = 1036;
    cars[13].obstacleY = 139;
    cars[13].speed = 1000000;
    cars[13].paused = 0;
    cars[13].exitCondition = 0;

    cars[14].obstacleX = 1100;
    cars[14].obstacleY = 139;
    cars[14].speed = 1000500;
    cars[14].paused = 0;
    cars[14].exitCondition = 0;

    // Drawing out the stage, lives and moves
    drawStageCars(pixel);
    drawLivesCars(numLives);
    drawMovesCars(numMoves);

    drawImage(frogSafe, pixel, 850, 636, 64, 64); 

    // Setting initial values
    int nextStageFlag = 0;
    int num = 0;
    int xPos = 850;
    int initXPos = xPos;
    int yPos = 636;
    int initYPos = yPos;

    /*Initializing the threads for the obstacles*/
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    int play = 1;

    pthread_t a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, timeThread, scoreThread;
    pthread_attr_t attrMain;
    pthread_attr_init(&attrMain);

    pthread_create(&timeThread, NULL, &updateTimeCars, gameValues);
    pthread_create(&scoreThread, NULL, &updateScoreCars, gameValues);

    pthread_create(&a1, NULL, &moveCarLeft, (void *)&cars[0]); 
    pthread_create(&a2, NULL, &moveCarLeft, (void *)&cars[1]); 

    pthread_create(&a3, NULL, &moveCarRight, (void *)&cars[2]);
    pthread_create(&a4, NULL, &moveCarRight, (void *)&cars[3]);
    pthread_create(&a5, NULL, &moveCarLeft, (void *)&cars[4]);
    pthread_create(&a6, NULL, &moveCarLeft, (void *)&cars[5]);
    pthread_create(&a7, NULL, &moveCarLeft, (void *)&cars[6]);
    pthread_create(&a8, NULL, &moveCarLeft, (void *)&cars[7]);
    pthread_create(&a9, NULL, &moveCarRight, (void *)&cars[8]);
    pthread_create(&a10, NULL, &moveCarRight, (void *)&cars[9]);
    pthread_create(&a11, NULL, &moveCarRight, (void *)&cars[10]);
    pthread_create(&a12, NULL, &moveCarRight, (void *)&cars[11]);
    pthread_create(&a13, NULL, &moveCarRight, (void *)&cars[12]);
    pthread_create(&a14, NULL, &moveCarLeft, (void *)&cars[13]); 
    pthread_create(&a15, NULL, &moveCarLeft, (void *)&cars[14]); 


    while (nextStageFlag == 0) {

        int numLives = gameValues -> lives;
        int currTime = gameValues -> time;
        int loseCheck = gameValues -> loseFlag;
        int currMoves = gameValues -> movesLeft;


        currScore = currTime + numMoves + (2 * numLives);
        gameValues -> score = currScore;

        num = Read_SNES(gpioPtr, buttonArray);

        // Move Down
        if (num == 1) {
            if (yPos == 636) {
                // End Zone
                drawBlock(pixel, safeColor, 503, 60, 697, 64);

                // Start Zone
                drawBlock(pixel, safeColor, 503, 636, 697, 64);
                drawImage(frogSafe, pixel, xPos, yPos, 64, 64);
            }


            if (yPos + 64 < 697) {
                yPos = yPos + 64;
                // End Zone
                drawBlock(pixel, safeColor, 503, 60, 697, 64);

                // Start Zone
                drawBlock(pixel, safeColor, 503, 636, 697, 64);

                if (yPos == 636) {
                    drawBlock(pixel, black, xPos, yPos - 64, 64, 64);
                    drawImage(frogSafe, pixel, xPos, yPos, 64, 64);


                } else {
                    drawBlock(pixel, black, xPos, yPos-64, 64, 64);
                    drawImage(frog, pixel, xPos, yPos, 64, 64);
                }
                numMoves -= 1;
                drawMovesCars(numMoves);
                gameValues -> movesLeft = numMoves;

            }
        }
        // Move Up
        if (num == 4) {
            if (yPos - 64 > 0) {
                yPos = yPos - 64;
                // End Zone
                drawBlock(pixel, safeColor, 503, 60, 697, 64);
                // Start Zone
                drawBlock(pixel, safeColor, 503, 636, 697, 64);

                if (yPos == 60) {
drawImage(frogSafe, pixel, xPos, yPos, 64, 64);
drawBlock(pixel, black, xPos, yPos + 64, 64, 64);

                }


                else if (yPos == 636) {
                    drawImage(frogSafe, pixel, xPos, yPos, 64, 64);

                } else {
                    drawBlock(pixel, black, xPos, yPos + 64, 64, 64);
                    drawImage(frog, pixel, xPos, yPos, 64, 64);
                }
                numMoves -= 1;
                drawMovesCars(numMoves);
                gameValues -> movesLeft = numMoves;

            }
        }

        // Move Left
        if (num == 2) {
            if (xPos - 64 > 500) {
                xPos = xPos - 64;
                // End Zone
                drawBlock(pixel, safeColor, 503, 60, 697, 64);
                // Start Zone
                drawBlock(pixel, safeColor, 503, 636, 697, 64);
                if (yPos == 60) {
                    drawImage(frogSafe, pixel, xPos, yPos, 64, 64);
                    drawBlock(pixel, black, xPos + 64, yPos, 64, 64);

                }

                else if (yPos == 636) {
                    drawImage(frogSafe, pixel, xPos, yPos, 64, 64);

                } else {
                    drawBlock(pixel, black, xPos + 64, yPos, 64, 64);
                    drawImage(frog, pixel, xPos, yPos, 64, 64);
                }
                numMoves -= 1;
                drawMovesCars(numMoves);
                gameValues -> movesLeft = numMoves;


            }
        }

        // Move Right 
        if (num == 3) {

            if (xPos + 64 < 1150) {
                xPos = xPos + 64;
                // End Zone
                drawBlock(pixel, safeColor, 503, 60, 697, 64);
                // Start Zone
                drawBlock(pixel, safeColor, 503, 636, 697, 64);

                if (yPos == 60) {
                    drawImage(frogSafe, pixel, xPos, yPos, 64, 64);
                    drawBlock(pixel, black, xPos - 64, yPos, 64, 64);

                }

                else if (yPos == 636) {
                    drawImage(frogSafe, pixel, xPos, yPos, 64, 64);

                } else {
                    drawBlock(pixel, black, xPos - 64, yPos, 64, 64);
                    drawImage(frog, pixel, xPos, yPos, 64, 64);
                }
                numMoves -= 1;
                drawMovesCars(numMoves);
                gameValues -> movesLeft = numMoves;

            }
        }

        // End zone has been reached
        if (yPos == 60) {
            // Loop through the obstacle threads and change the values
            for (int i = 0; i < 15; i++) {
                cars[i].paused = 1;
                cars[i].exitCondition = 1;
            }
            // Cancel all the threads
            pthread_cancel(a1);
            pthread_cancel(a2);
            pthread_cancel(a3);
            pthread_cancel(a4);
            pthread_cancel(a5);
            pthread_cancel(a6);
            pthread_cancel(a7);
            pthread_cancel(a8);
            pthread_cancel(a9);
            pthread_cancel(a10);
            pthread_cancel(a11);
            pthread_cancel(a12);
            pthread_cancel(a13);
            pthread_cancel(a14);
            pthread_cancel(a15);
            pthread_cancel(timeThread);
            pthread_cancel(scoreThread);

            return 3;
        }


        int check;
        // Check if collision has occurred
        for (int i = 0; i < 15; i++) {
            check = collisionCheckCars(cars[i], xPos, yPos, initXPos, initYPos);
            if (check == 1) {
                gameValues -> lives = numLives - 1;
                drawLivesCars(numLives-1);
                xPos = initXPos;
                yPos = initYPos;
            }
        }

        // If lives == 0 or time == 0 or moves == 0 
        if (numLives == 0 || currTime == 0 || currMoves == 0) {
            gameValues -> loseFlag = 1;
        }

        if (loseCheck == 1) { // If lose pause the threads
            for (int i = 0; i < 15; i++) { // Loop through and change pause values
                cars[i].paused = 1;
            }

            for (int i = 0; i < 15; i++) { // loop through and change exit values
                cars[i].exitCondition = 1;
            }
            // Cancel all threads
            pthread_cancel(a1);
            pthread_cancel(a2);
            pthread_cancel(a3);
            pthread_cancel(a4);
            pthread_cancel(a5);
            pthread_cancel(a6);
            pthread_cancel(a7);
            pthread_cancel(a8);
            pthread_cancel(a9);
            pthread_cancel(a10);
            pthread_cancel(a11);
            pthread_cancel(a12);
            pthread_cancel(a13);
            pthread_cancel(a14);
            pthread_cancel(a15);
            pthread_cancel(timeThread);
            pthread_cancel(scoreThread);

            gameValues -> pauseButtonPressed = 1;
            gameValues -> loseFlag = 0;
            int loseNum = drawLoseScreen(gpioPtr, buttonArray);
            return 1;
        }

        // Value Pack, if reached, + 10 moves
        if (initTime - currTime == 2) {
            gameValues -> valueCars = 1;
        }
        int value1Check = gameValues -> valueCars;
        if (value1Check == 1) {
            drawValuePack1();
        }
        // If player obtains value pack, increase lives by 5
        if (value1Check == 1 && ((xPos == 850) && (yPos == 252))){
            numLives += 5;
            drawLivesCars(numLives);
            gameValues -> lives = numLives;
            gameValues -> valueCars = 0;

        }


        // Pause Menu (Start Button)
        if (num == 6) {
            for (int i = 0; i < 15; i++) {
                cars[i].paused = 1;
            }


            gameValues -> pauseButtonPressed = 1;

            int option = pauseMenuPressed(pixel, gpioPtr, buttonArray);

            // Restart Game Pressed
            if (option == 0) {
                for (int i = 0; i < 15; i++) { // loop and change exit condiiton
                    cars[i].exitCondition = 1;
                }

                // Cancel all threads
                pthread_cancel(a1);
                pthread_cancel(a2);
                pthread_cancel(a3);
                pthread_cancel(a4);
                pthread_cancel(a5);
                pthread_cancel(a6);
                pthread_cancel(a7);
                pthread_cancel(a8);
                pthread_cancel(a9);
                pthread_cancel(a10);
                pthread_cancel(a11);
                pthread_cancel(a12);
                pthread_cancel(a13);
                pthread_cancel(a14);
                pthread_cancel(a15);
                pthread_cancel(timeThread);
                pthread_cancel(scoreThread);


                gameValues -> pauseButtonPressed = 0;

                return 0;
            } 
            // Quit Game Pressed 
            else if (option == 1) {
                for (int i = 0; i < 15; i++) {
                    cars[i].exitCondition = 1;
                }
                // Cancel threads
                pthread_cancel(a1);
                pthread_cancel(a2);
                pthread_cancel(a3);
                pthread_cancel(a4);
                pthread_cancel(a5);
                pthread_cancel(a6);
                pthread_cancel(a7);
                pthread_cancel(a8);
                pthread_cancel(a9);
                pthread_cancel(a10);
                pthread_cancel(a11);
                pthread_cancel(a12);
                pthread_cancel(a13);
                pthread_cancel(a14);
                pthread_cancel(a15);
                pthread_cancel(timeThread);
                pthread_cancel(scoreThread);
                gameValues -> pauseButtonPressed = 0;

                return 1;
            }
            // Continue Game
            if (option == 2) {
                // Redraw the stage
                drawStageCars(pixel);
                numLives = gameValues -> lives;
                numMoves = gameValues -> movesLeft;

                // Redraw frog
                drawImage(frog, pixel, xPos, yPos, 64, 64); 

                // Redraw lives and moves
                drawLivesCars(numLives);
                drawMovesCars(numMoves);
                for (int i = 0; i < 14; i++) { // unpause threads
                    cars[i].paused = 0;
                }
                for (int i = 0; i < 14; i++) { 
                    cars[i].paused = 0;
                }




                gameValues -> pauseButtonPressed = 0;
                continue;
            }

        }


    }
}


/*
This thread function is used to move the obstacles left to right 
*/
void *moveCarLeft(void *arguments) {
    struct obstacle *car1 = (struct test *)arguments;
    int black = 0x0000;
    short int *carLeftImage = (short int*) carLeftIMG.pixel_data;
    int car1X = car1 -> obstacleX;
    int car1Y = car1 -> obstacleY;
    int initialX = car1X;
    int carSpeed = car1 -> speed;
    int pausedPressed = car1 -> paused;
    int exit = car1 -> exitCondition;


    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));

    while(1) {
        pausedPressed = car1 -> paused;
        exit = car1 -> exitCondition;
        if (exit) {
            break;
        }
        if (pausedPressed) { // if paused
        } else {
            if (car1X < 500) { //if obstacle reaches end of screen
                car1X = initialX;
            } else { // if in screen, draw the obstacle
                drawImage(carLeftImage, pixel, car1X, car1Y, 64, 32);
                usleep(carSpeed);
                drawBlock(pixel, black, car1X, car1Y, 64, 32);
                car1X -= 64; // move it left by 64
                car1 -> obstacleX = car1X;
            }
        }
    }
    pthread_exit(NULL);
}

/*
This thread function is used to move the obstacles right to left  
*/
void *moveCarRight(void *arguments) {
    struct obstacle *car1 = (struct test *)arguments;
    int black = 0x0000;
    short int *carRightImage = (short int*) carRightIMG.pixel_data;
    int car1X = car1 -> obstacleX;
    int car1Y = car1 -> obstacleY;
    int initialX = car1X;
    int carSpeed = car1 -> speed;
    int pausePressed = car1 -> paused;
    int exit = car1 -> exitCondition;

    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));

    while(1) {
        pausePressed = car1 -> paused;
        exit = car1 -> exitCondition;
        if (exit) { // if exit
            break;
        }
        if (pausePressed) { // if paused
        } else {

            if (car1X > 1136) { // If the obstacle reaches the end of the screen reset
                car1X = initialX;
            } else{
                drawImage(carRightImage, pixel, car1X, car1Y, 64, 32);
                usleep(carSpeed);
                drawBlock(pixel, black, car1X, car1Y, 64, 32);
                //usleep(carSpeed);
                car1X += 64;
                car1 -> obstacleX = car1X;
            }
        }
    }
    pthread_exit(NULL);
}

/*
This thread function updates the score as the game progresses 
*/
void *updateScoreCars(void *arguments) {
    GameOptions *gameValues = (GameOptions *)arguments;
    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));
    int paused = gameValues -> pauseButtonPressed;
    int black = 0x0000;
    int xStart, yStart;

    while (1) {
        int currScore = gameValues -> score;
        paused = gameValues -> pauseButtonPressed;


        if (paused) {
        } else {
            int numDigits = countNumDigitsCars(currScore);
            if (numDigits == 1) { // draw first digit
                xStart = 150;
                yStart = 210;
                drawNumCars(currScore, xStart, yStart);
                drawBlock(pixel, black, 190, 50, 32, 40);
                drawBlock(pixel, black, 230, 50, 32, 40);
                drawBlock(pixel, black, 270, 50, 32, 40); 

            }
            if (numDigits == 2) { // draws two digits
                int digit1 = currScore / 10;
                int digit2 = currScore % 10; 
                drawNumCars(digit1, 150, 50);
                drawNumCars(digit2, 190, 50);
                drawBlock(pixel, black, 230, 50, 32, 40); 
                drawBlock(pixel, black, 270, 50, 32, 40); 


            }
            if (numDigits == 3) { // draws three digits
                int digit3 = currScore % 10;
                int nextTime = currScore / 10;
                int digit2 = nextTime % 10;
                nextTime = nextTime / 10;
                int digit1 = nextTime % 10;
                drawNumCars(digit1, 150, 50);
                drawNumCars(digit2, 190, 50);
                drawNumCars(digit3, 230, 50);
                drawBlock(pixel, black, 270, 50, 32, 40); 

            }
            if (numDigits == 4) { //draws four digits
                int digit4 = currScore % 10;
                int nextNum = currScore / 10;
                int digit3 = currScore % 10;
                nextNum = currScore / 10;
                int digit2 = nextNum % 10;
                nextNum /= 10;
                int digit1 = nextNum % 10;
                drawNumCars(digit1, 150, 50);
                drawNumCars(digit2, 190, 50);
                drawNumCars(digit3, 230, 50);
                drawNumCars(digit4, 270, 50);

            }
        }
        usleep(100000);

    }

}

/*
This thread function is used to update the time 
*/
void *updateTimeCars(void *arguments) {
    GameOptions *gameValues = (GameOptions *)arguments;
    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));
    int numDigits;
    int xStart;
    int yStart;
    int totalTime = gameValues -> time;
    int paused = gameValues -> pauseButtonPressed;
    int black = 0x0000;

    while (1) {
        paused = gameValues -> pauseButtonPressed;

        if (paused) {
        } else {
            numDigits = countNumDigitsCars(totalTime);
            if (numDigits == 1) { // draws one digit
                xStart = 150;
                yStart = 210;
                drawNumCars(totalTime, xStart, yStart);
                drawBlock(pixel, black, 190, 210, 32, 40);
                drawBlock(pixel, black, 230, 210, 32, 40);

            }
            if (numDigits == 2) { // draws two digits
                int digit1 = totalTime / 10;
                int digit2 = totalTime % 10; 
                drawNumCars(digit1, 150, 210);
                drawNumCars(digit2, 190, 210);
                drawBlock(pixel, black, 230, 210, 32, 40); 

            }
            if (numDigits == 3) { // draws three digits
                int digit3 = totalTime % 10;
                int nextTime = totalTime / 10;
                int digit2 = nextTime % 10;
                nextTime = nextTime / 10;
                int digit1 = nextTime % 10;
                drawNumCars(digit1, 150, 210);
                drawNumCars(digit2, 190, 210);
                drawNumCars(digit3, 230, 210);

            }

            // Changes the time value
            usleep(1000000);
            totalTime -=1;
            gameValues -> time = totalTime;
        }
    }
    pthread_exit(NULL);
}

/*
Gets the digits needed 
@param num -> the digit that is needed 
*/
int countNumDigitsCars(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        ++count;
    }
    return count;

}

/*
Checks to see if a collision happens with any obstacle 
@param car -> the alligator structure 
@param xPosition -> frogs x pos 
@param yPosition -> frogs y pos 
@param initXPosition -> the frogs original start x postion 
@param initYPosition -> the frogs original start y postion 
*/
int collisionCheckCars(struct obstacle car, int xPosition, int yPosition, int initXPosition, int initYPosition) {
    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));
    short int *frog = (short int *) froggy.pixel_data;

    int black = 0x0000;

    // Checking to see if a collision happens
    if ((car.obstacleX <= xPosition) && (xPosition <= car.obstacleX + 64)) {
        if((car.obstacleY <= yPosition + 32) && (yPosition + 32 <= car.obstacleY + 32)){
            // If collision occurs, black out the frog and draw it at the start
            drawBlock(pixel, black, xPosition-6, yPosition, 70, 64);
            drawImage(frog, pixel, initXPosition, initYPosition, 64, 64);
            return 1;
        }
    } else {
        return 0;
    }


}

/*
Draws out the moves left.
@param numMoves -> the moves left 
*/
void drawMovesCars(int numMoves) {
    short int *one = (short int*) oneIMG.pixel_data;
    short int *two = (short int*) twoIMG.pixel_data;
    short int *three = (short int*) threeIMG.pixel_data;
    short int *four = (short int*) fourIMG.pixel_data;
    short int *five = (short int*) fiveIMG.pixel_data;
    short int *six = (short int*) sixIMG.pixel_data;
    short int *seven = (short int*) sevenIMG.pixel_data;
    short int *eight = (short int*) eightIMG.pixel_data;
    short int *nine = (short int*) nineIMG.pixel_data;
    short int *zero = (short int*) zeroIMG.pixel_data;
    int xStart, yStart;
    int black = 0x0000;
    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));



    int numDigits = countNumDigitsCars(numMoves);
    if (numDigits == 1) { // Draws one digit
        xStart = 150;
        yStart = 290;
        drawNumCars(numMoves, xStart, yStart);
        drawBlock(pixel, black, 190, 290, 32, 40);
        drawBlock(pixel, black, 230, 290, 32, 40);
    }
    if (numDigits == 2) { // draws two digits
        int digit1 = numMoves / 10;
        int digit2 = numMoves % 10; 
        drawNumCars(digit1, 150, 290);
        drawNumCars(digit2, 190, 290);
        drawBlock(pixel, black, 230, 290, 32, 40); 
    }
    if (numDigits == 3) { // draws three digits
        int digit3 = numMoves % 10;
        int nextTime = numMoves / 10;
        int digit2 = nextTime % 10;
        nextTime = nextTime / 10;
        int digit1 = nextTime % 10;
        drawNumCars(digit1, 150, 290);
        drawNumCars(digit2, 190, 290);
        drawNumCars(digit3, 230, 290);
    }

}


/*
Draws out the lives left.
@param numLives -> the lives  left 
*/
void drawLivesCars(int numLives) {
    // Number images
    short int *one = (short int*) oneIMG.pixel_data;
    short int *two = (short int*) twoIMG.pixel_data;
    short int *three = (short int*) threeIMG.pixel_data;
    short int *four = (short int*) fourIMG.pixel_data;
    short int *five = (short int*) fiveIMG.pixel_data;
    short int *six = (short int*) sixIMG.pixel_data;
    short int *seven = (short int*) sevenIMG.pixel_data;
    short int *eight = (short int*) eightIMG.pixel_data;
    short int *nine = (short int*) nineIMG.pixel_data;
    short int *zero = (short int*) zeroIMG.pixel_data;

    int black = 0x0000;

    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));

    // Draws out lives
    int numDigits = countNumDigitsCars(numLives);
    if (numDigits == 1) { // one digit
        int xStart = 150;
        int yStart = 120;
        drawNumCars(numLives, xStart, yStart);
        drawBlock(pixel, black, 190, 120, 32, 40);
        drawBlock(pixel, black, 230, 120, 32, 40);
    }
    if (numDigits == 2) { // two digits
        int digit1 = numLives / 10;
        int digit2 = numLives % 10; 
        drawNumCars(digit1, 150, 120);
        drawNumCars(digit2, 190, 120);
        drawBlock(pixel, black, 230, 120, 32, 40); 
    }
    if (numDigits == 3) { // three digits1
        int digit3 = numLives % 10;
        int nextTime = numLives / 10;
        int digit2 = nextTime % 10;
        nextTime = nextTime / 10;
        int digit1 = nextTime % 10;
        drawNumCars(digit1, 150, 120);
        drawNumCars(digit2, 190, 120);
        drawNumCars(digit3, 230, 120);
    }
}

/*
Draws out numbers .
@param num -> the number itself
@param xPos -> x position of number
@param yPos -> y position of number  
*/
void drawNumCars(int num, int xPos, int yPos) {
    short int *one = (short int*) oneIMG.pixel_data;
    short int *two = (short int*) twoIMG.pixel_data;
    short int *three = (short int*) threeIMG.pixel_data;
    short int *four = (short int*) fourIMG.pixel_data;
    short int *five = (short int*) fiveIMG.pixel_data;
    short int *six = (short int*) sixIMG.pixel_data;
    short int *seven = (short int*) sevenIMG.pixel_data;
    short int *eight = (short int*) eightIMG.pixel_data;
    short int *nine = (short int*) nineIMG.pixel_data;
    short int *zero = (short int*) zeroIMG.pixel_data;

    int black = 0x0000;

    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));

    drawBlock(pixel, black, xPos, yPos, 32, 40);


    switch (num) {
        case 0: 
            drawImage(zero, pixel, xPos, yPos, 32, 40);
            break;
        case 1:
            drawImage(one, pixel, xPos, yPos, 32, 40);
            break;
        case 2:
            drawImage(two, pixel, xPos, yPos, 32, 40);
            break;
        case 3:
            drawImage(three, pixel, xPos, yPos, 32, 40);
            break;
        case 4:
            drawImage(four, pixel, xPos, yPos, 32, 40);
            break;
        case 5:
            drawImage(five, pixel, xPos, yPos, 32, 40);
            break;
        case 6:
            drawImage(six, pixel, xPos, yPos, 32, 40);
            break;
        case 7:
            drawImage(seven, pixel, xPos, yPos, 32, 40);
            break;
        case 8:
            drawImage(eight, pixel, xPos, yPos, 32, 40);
            break;
        case 9:
            drawImage(nine, pixel, xPos, yPos, 32, 40);
            break;
    }
}

/*
This function draws out the first stage 
@param pixel -> pixel need to draw 
*/
void drawStageCars(Pixel *pixel) {

    int borderColor = 0x7E0;
    int black = 0x0000;
    int safeColor = 0x04B0;
    short int *stage3Text1 = (short int *) stage3.pixel_data;
    short int *score = (short int *) scoreMsg.pixel_data;
    short int *lives = (short int *) livesMsg.pixel_data;
    short int *time = (short int *) timeMsg.pixel_data;
    short int *moves = (short int*) movesIMG.pixel_data;


    drawBorder(pixel, borderColor, 1200, 700);
    drawInnerBackground(pixel, black);
    drawBlock(pixel, borderColor, 500, 0, 3, 700);

    drawBlock(pixel, borderColor, 500, 54, 700, 3);

    drawImage(stage3Text1, pixel, 10, 10, 80, 40);
    drawImage(score, pixel, 5, 70, 80, 20);
    drawImage(lives, pixel, 10, 130, 80, 20);
    drawImage(time, pixel, 13, 220, 80, 20);
    drawImage(moves, pixel, 10, 300, 80, 20);

    // End Zone
    drawBlock(pixel, safeColor, 503, 60, 697, 64);

    // Start Zone
    drawBlock(pixel, safeColor, 503, 636, 697, 64);

}
