#include "drawFunctions.h"
#include "pixelStruct.h"
#include "gameOptions.h"
#include "SNESSController.h"
#include "pauseMenu.h"
#include "loseScreen.h"
#include "valuePacks.h"
#include "images/stage1Text.c"
#include "images/score.c"
#include "images/lives.c"
#include "images/time.c"
#include "images/moves.c"
#include "images/keroppi.c"
#include "images/froggySafe.c"
#include "images/alligatorImage.c"
#include "images/alligatorRight.c"
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


#include <pthread.h>

#define clearConsole() printf("\e[1;1H\e[2J")

void *moveAlligatorLeft(void *i);
void *moveAlligatorRight(void *arguments);
void *updateTime(void *arguments);
void *updateScore(void *arguments); 

//structure for the obstacles
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
int playStage1(Pixel *pixel, unsigned int *gpioPtr, int buttonArray[], GameOptions *gameValues) {

    int borderColor = 0x7E0;
    int black = 0x0000;
    int safeColor = 0x04B0;

    //for the images 
    short int *stage1Text1 = (short int *) stage1.pixel_data;
    short int *score = (short int *) scoreMsg.pixel_data;
    short int *lives = (short int *) livesMsg.pixel_data;
    short int *time = (short int *) timeMsg.pixel_data;
    short int *moves = (short int*) movesIMG.pixel_data;
    short int *frog = (short int *) froggy.pixel_data;
    short int *frogSafe = (short int*) froggySafeIMG.pixel_data;
    short int *alligatorLeftImage = (short int*) alligatorIMG.pixel_data;
    short int *alligatorRightImage = (short int*) alligatorIMGRight.pixel_data;
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

    //initlaize game value 
    int numLives = gameValues -> lives;
    int numMoves = gameValues -> movesLeft;
    int currScore = gameValues -> score;
    int initTime = gameValues -> time;

    //initialize the obstacles
    struct obstacle alligators[15];
    alligators[0].obstacleX = 1036;
    alligators[0].obstacleY = 587;
    alligators[0].speed = 1000000;
    alligators[0].paused = 0;
    alligators[0].exitCondition = 0;

    alligators[1].obstacleX = 1100;
    alligators[1].obstacleY = 587;
    alligators[1].speed = 1000500;
    alligators[1].paused = 0;
    alligators[1].exitCondition = 0;

    alligators[2].obstacleX = 537;
    alligators[2].obstacleY = 523;
    alligators[2].speed = 2000000;
    alligators[2].paused = 0;
    alligators[2].exitCondition = 0;

    alligators[3].obstacleX = 665;
    alligators[3].obstacleY = 523;
    alligators[3].speed = 2000000;
    alligators[3].paused = 0;
    alligators[3].exitCondition = 0;

    alligators[4].obstacleX = 1036;
    alligators[4].obstacleY = 459;
    alligators[4].speed = 1000000;
    alligators[4].paused = 0;
    alligators[4].exitCondition = 0;


    alligators[5].obstacleX = 1100;
    alligators[5].obstacleY = 459;
    alligators[5].speed = 1000500;
    alligators[5].paused = 0;
    alligators[5].exitCondition = 0;


    alligators[6].obstacleX = 1036;
    alligators[6].obstacleY = 395;
    alligators[6].speed = 1000000;
    alligators[6].paused = 0;
    alligators[6].exitCondition = 0;


    alligators[7].obstacleX = 1100;
    alligators[7].obstacleY = 395;
    alligators[7].speed = 1000500;
    alligators[7].paused = 0;
    alligators[7].exitCondition = 0;


    alligators[8].obstacleX = 601;
    alligators[8].obstacleY = 331;
    alligators[8].speed = 3000000;
    alligators[8].paused = 0;
    alligators[8].exitCondition = 0;


    alligators[9].obstacleX = 665;
    alligators[9].obstacleY = 331;
    alligators[9].speed = 3000000;
    alligators[9].paused = 0;
    alligators[9].exitCondition = 0;


    alligators[10].obstacleX = 665;
    alligators[10].obstacleY = 267;
    alligators[10].speed = 1000000;
    alligators[10].paused = 0;
    alligators[10].exitCondition = 0;

    alligators[11].obstacleX = 665;
    alligators[11].obstacleY = 203;
    alligators[11].speed = 4000000;
    alligators[11].paused = 0;
    alligators[11].exitCondition = 0;

    alligators[12].obstacleX = 729;
    alligators[12].obstacleY = 203;
    alligators[12].speed = 4000000;
    alligators[12].paused = 0;
    alligators[12].exitCondition = 0;


    alligators[13].obstacleX = 1036;
    alligators[13].obstacleY = 139;
    alligators[13].speed = 1000000;
    alligators[13].paused = 0;
    alligators[13].exitCondition = 0;

    alligators[14].obstacleX = 1100;
    alligators[14].obstacleY = 139;
    alligators[14].speed = 1000500;
    alligators[14].paused = 0;
    alligators[14].exitCondition = 0;

    //draw out the stage, lives and moves 
    drawStage1(pixel);
    drawLives(numLives);
    drawMoves(numMoves);

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

    pthread_create(&timeThread, NULL, &updateTime, gameValues);
    pthread_create(&scoreThread, NULL, &updateScore, gameValues);

    pthread_create(&a1, NULL, &moveAlligatorLeft, (void *)&alligators[0]); 
    pthread_create(&a2, NULL, &moveAlligatorLeft, (void *)&alligators[1]); 

    pthread_create(&a3, NULL, &moveAlligatorRight, (void *)&alligators[2]);
    pthread_create(&a4, NULL, &moveAlligatorRight, (void *)&alligators[3]);
    pthread_create(&a5, NULL, &moveAlligatorLeft, (void *)&alligators[4]);
    pthread_create(&a6, NULL, &moveAlligatorLeft, (void *)&alligators[5]);
    pthread_create(&a7, NULL, &moveAlligatorLeft, (void *)&alligators[6]);
    pthread_create(&a8, NULL, &moveAlligatorLeft, (void *)&alligators[7]);
    pthread_create(&a9, NULL, &moveAlligatorRight, (void *)&alligators[8]);
    pthread_create(&a10, NULL, &moveAlligatorRight, (void *)&alligators[9]);
    pthread_create(&a11, NULL, &moveAlligatorRight, (void *)&alligators[10]);
    pthread_create(&a12, NULL, &moveAlligatorRight, (void *)&alligators[11]);
    pthread_create(&a13, NULL, &moveAlligatorRight, (void *)&alligators[12]);
    pthread_create(&a14, NULL, &moveAlligatorLeft, (void *)&alligators[13]); 
    pthread_create(&a15, NULL, &moveAlligatorLeft, (void *)&alligators[14]); 


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
                drawMoves(numMoves);
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
                drawMoves(numMoves);
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
                drawMoves(numMoves);
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
                drawMoves(numMoves);
                gameValues -> movesLeft = numMoves;

            }
        }

        // End zone has been reached
        if (yPos == 60) { 
          //loop through the obstacle threads and change the values 
            for (int i = 0; i < 15; i++) {
                alligators[i].paused = 1;
            }

            for (int i = 0; i < 15; i++) {
                alligators[i].exitCondition = 1;
            }
            //cancel all the threads 
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
            check = collisionCheck(alligators[i], xPos, yPos, initXPos, initYPos);
            if (check == 1) {
                gameValues -> lives = numLives - 1;
                drawLives(numLives-1);
                xPos = initXPos;
                yPos = initYPos;
            }
        }

        // If lives == 0 or time == 0 or moves == 0 
        if (numLives == 0 || currTime == 0 || currMoves == 0) {
            gameValues -> loseFlag = 1;
        }

        if (loseCheck == 1) { //if lose pause the threads 
            for (int i = 0; i < 15; i++) {  //loop thru and change pause values 
                alligators[i].paused = 1;
            }

            for (int i = 0; i < 15; i++) {  //loop thru and change exit values 
                alligators[i].exitCondition = 1;
            }
            //cancel all threads 
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

            gameValues -> value1 = 1;
        }
        int value1Check = gameValues -> value1;
        if (value1Check == 1) {
            drawValuePack1(); //draw the pack
        }
        //if player obtains value pack, increase moves by 10 
        if (value1Check == 1 && ((xPos == 850) && (yPos == 252))){
            numMoves += 10;
            drawMoves(numMoves);
            gameValues -> movesLeft = numMoves;

            gameValues -> value1 = 0;

        }


        // Pause Menu (Start Button)
        if (num == 6) {
            for (int i = 0; i < 15; i++) {  //loop and pause threads 
                alligators[i].paused = 1;
            }


            gameValues -> pauseButtonPressed = 1;

            int option = pauseMenuPressed(pixel, gpioPtr, buttonArray);

            // Restart Game Pressed
            if (option == 0) {
                for (int i = 0; i < 15; i++) {  //loop and change exit condition 
                    alligators[i].exitCondition = 1;
                }

                //cancel all threads 
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
                    alligators[i].exitCondition = 1;
                }
                //cancel threads 
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
                //redraw the stage 
                drawStage1(pixel);
                numLives = gameValues -> lives;
                numMoves = gameValues -> movesLeft;

                //redraw frog 
                drawImage(frog, pixel, xPos, yPos, 64, 64); 
                //redraw lives and moves 
                drawLives(numLives);
                drawMoves(numMoves);
                for (int i = 0; i < 14; i++) {  //unpause threads 
                    alligators[i].paused = 0;
                }
                for (int i = 0; i < 14; i++) {
                    alligators[i].paused = 0;
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
void *moveAlligatorLeft(void *arguments) {
    struct obstacle *alligator1 = (struct test *)arguments;
    int black = 0x0000;
    short int *alligatorLeftImage = (short int*) alligatorIMG.pixel_data;
    int alligator1X = alligator1 -> obstacleX;
    int alligator1Y = alligator1 -> obstacleY;
    int initialX = alligator1X;
    int alligatorSpeed = alligator1 -> speed;
    int pausedPressed = alligator1 -> paused;
    int exit = alligator1 -> exitCondition;


    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));

    while(1) {
        pausedPressed = alligator1 -> paused;
        exit = alligator1 -> exitCondition;
        if (exit) { //if exit 
            break;
        }
        if (pausedPressed) {  //if paused 
        } else {
            if (alligator1X < 500) {  //if obstacle reaches end of screen 
                alligator1X = initialX;
            } else {  //if in screen draw obstacle
                drawImage(alligatorLeftImage, pixel, alligator1X, alligator1Y, 64, 32);
                usleep(alligatorSpeed);
                drawBlock(pixel, black, alligator1X, alligator1Y, 64, 32);
                alligator1X -= 64;  //move it left by 64
                alligator1 -> obstacleX = alligator1X;
            }
        }
    }
    pthread_exit(NULL);
}

/*
This thread function is used to move the obstacles right to left  
*/
void *moveAlligatorRight(void *arguments) {
    struct obstacle *alligator1 = (struct test *)arguments;
    int black = 0x0000;
    short int *alligatorRightImage = (short int*) alligatorIMGRight.pixel_data;
    int alligator1X = alligator1 -> obstacleX;
    int alligator1Y = alligator1 -> obstacleY;
    int initialX = alligator1X;
    int alligatorSpeed = alligator1 -> speed;
    int pausePressed = alligator1 -> paused;
    int exit = alligator1 -> exitCondition;

    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));

    while(1) {
        pausePressed = alligator1 -> paused;
        exit = alligator1 -> exitCondition;
        if (exit) { //if exit 
            break;
        }
        if (pausePressed) { //if paused 
        } else {

            if (alligator1X > 1136) { //if the obstacle reaches end of screen reset 
                alligator1X = initialX;
            } else{
                drawImage(alligatorRightImage, pixel, alligator1X, alligator1Y, 64, 32);
                usleep(alligatorSpeed);
                drawBlock(pixel, black, alligator1X, alligator1Y, 64, 32);
                alligator1X += 64;  //move obstacle right by 64
                alligator1 -> obstacleX = alligator1X;
            }
        }
    }
    pthread_exit(NULL);
}

/*
This thread function updates the score as the game progresses 
*/
void *updateScore(void *arguments) {
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
            int numDigits = countNumDigits(currScore);
            if (numDigits == 1) { //draw first digit 
                xStart = 150;
                yStart = 210;
                drawNum(currScore, xStart, yStart);
                drawBlock(pixel, black, 190, 50, 32, 40);
                drawBlock(pixel, black, 230, 50, 32, 40);
                drawBlock(pixel, black, 270, 50, 32, 40); 

            }
            if (numDigits == 2) { //draws two digits
                int digit1 = currScore / 10;
                int digit2 = currScore % 10; 
                drawNum(digit1, 150, 50);
                drawNum(digit2, 190, 50);
                drawBlock(pixel, black, 230, 50, 32, 40); 
                drawBlock(pixel, black, 270, 50, 32, 40); 


            }
            if (numDigits == 3) { //draws three digits 
                int digit3 = currScore % 10;
                int nextTime = currScore / 10;
                int digit2 = nextTime % 10;
                nextTime = nextTime / 10;
                int digit1 = nextTime % 10;
                drawNum(digit1, 150, 50);
                drawNum(digit2, 190, 50);
                drawNum(digit3, 230, 50);
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
                drawNum(digit1, 150, 50);
                drawNum(digit2, 190, 50);
                drawNum(digit3, 230, 50);
                drawNum(digit4, 270, 50);

            }
        }
        usleep(100000);

    }

}
/*
This thread function is used to update the time 
*/
void *updateTime(void *arguments) {
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
            numDigits = countNumDigits(totalTime);
            if (numDigits == 1) { //draw first digit 
                xStart = 150;
                yStart = 210;
                drawNum(totalTime, xStart, yStart);
                drawBlock(pixel, black, 190, 210, 32, 40);
                drawBlock(pixel, black, 230, 210, 32, 40);

            }
            if (numDigits == 2) { //draws two digits
                int digit1 = totalTime / 10;
                int digit2 = totalTime % 10; 
                drawNum(digit1, 150, 210);
                drawNum(digit2, 190, 210);
                drawBlock(pixel, black, 230, 210, 32, 40); 

            }
            if (numDigits == 3) { //draws three digits
                int digit3 = totalTime % 10;
                int nextTime = totalTime / 10;
                int digit2 = nextTime % 10;
                nextTime = nextTime / 10;
                int digit1 = nextTime % 10;
                drawNum(digit1, 150, 210);
                drawNum(digit2, 190, 210);
                drawNum(digit3, 230, 210);

            }

            //change the time value
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
int countNumDigits(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        ++count;
    }
    return count;

}

/*
Checks to see if a collision happens with any obstacle 
@param alligator -> the alligator structure 
@param xPosition -> frogs x pos 
@param yPosition -> frogs y pos 
@param initXPosition -> the frogs original start x postion 
@param initYPosition -> the frogs original start y postion 
*/
int collisionCheck(struct obstacle alligator, int xPosition, int yPosition, int initXPosition, int initYPosition) {
    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));
    short int *frog = (short int *) froggy.pixel_data;

    int black = 0x0000;

    //checking to see if a collision happens 
    if ((alligator.obstacleX <= xPosition) && (xPosition <= alligator.obstacleX + 64)) {
        if((alligator.obstacleY <= yPosition + 32) && (yPosition + 32 <= alligator.obstacleY + 32)){
            //if collison happens black out frog and draw it at the start 
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
void drawMoves(int numMoves) {
    //images for the numbers 
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



    int numDigits = countNumDigits(numMoves);
    if (numDigits == 1) { //first num 
        xStart = 150;
        yStart = 290;
        drawNum(numMoves, xStart, yStart);
        drawBlock(pixel, black, 190, 290, 32, 40);
        drawBlock(pixel, black, 230, 290, 32, 40);
    }
    if (numDigits == 2) { //two nums
        int digit1 = numMoves / 10;
        int digit2 = numMoves % 10; 
        drawNum(digit1, 150, 290);
        drawNum(digit2, 190, 290);
        drawBlock(pixel, black, 230, 290, 32, 40); 
    }
    if (numDigits == 3) { //three nums
        int digit3 = numMoves % 10;
        int nextTime = numMoves / 10;
        int digit2 = nextTime % 10;
        nextTime = nextTime / 10;
        int digit1 = nextTime % 10;
        drawNum(digit1, 150, 290);
        drawNum(digit2, 190, 290);
        drawNum(digit3, 230, 290);
    }

}



/*
Draws out the lives left.
@param numLives -> the lives  left 
*/
void drawLives(int numLives) {
    //number images 
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

    //draw out the lives 
    drawBlock(pixel, black, 190, 110, 32, 40);
    drawNum(numLives, 190,120);


}

/*
Draws out numbers .
@param num -> the number itself
@param xPos -> x position of number
@param yPos -> y position of number  
*/
void drawNum(int num, int xPos, int yPos) {
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
void drawStage1(Pixel *pixel) {

    int borderColor = 0x7E0;
    int black = 0x0000;
    int safeColor = 0x04B0;
    short int *stage1Text1 = (short int *) stage1.pixel_data;
    short int *score = (short int *) scoreMsg.pixel_data;
    short int *lives = (short int *) livesMsg.pixel_data;
    short int *time = (short int *) timeMsg.pixel_data;
    short int *moves = (short int*) movesIMG.pixel_data;


    drawBorder(pixel, borderColor, 1200, 700);
    drawInnerBackground(pixel, black);
    drawBlock(pixel, borderColor, 500, 0, 3, 700);

    drawBlock(pixel, borderColor, 500, 54, 700, 3);

    drawImage(stage1Text1, pixel, 10, 10, 80, 40);
    drawImage(score, pixel, 5, 70, 80, 20);
    drawImage(lives, pixel, 10, 130, 80, 20);
    drawImage(time, pixel, 13, 220, 80, 20);
    drawImage(moves, pixel, 10, 300, 80, 20);

    // End Zone
    drawBlock(pixel, safeColor, 503, 60, 697, 64);

    // Start Zone
    drawBlock(pixel, safeColor, 503, 636, 697, 64);




}
