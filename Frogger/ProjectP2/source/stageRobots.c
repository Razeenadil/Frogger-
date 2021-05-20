#include "drawFunctions.h"
#include "pixelStruct.h"
#include "gameOptions.h"
#include "SNESSController.h"
#include "pauseMenu.h"
#include "loseScreen.h"
#include "valuePacks.h"
#include "images/stage2Text.c"
#include "images/score.c"
#include "images/lives.c"
#include "images/time.c"
#include "images/moves.c"
#include "images/keroppi.c"
#include "images/froggySafe.c"
#include "images/robot.c"
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

void *moveRobotLeft(void *i);
void *moveRobotRight(void *arguments);
void *updateTimeRobot(void *arguments);
void *updateScoreRobot(void *arguments); 

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
int playStageRobot(Pixel *pixel, unsigned int *gpioPtr, int buttonArray[], GameOptions *gameValues) {

    int borderColor = 0x7E0;
    int black = 0x0000;
    int safeColor = 0x04B0;

    // Images
    short int *stage2Text1 = (short int *) stage2.pixel_data;
    short int *score = (short int *) scoreMsg.pixel_data;
    short int *lives = (short int *) livesMsg.pixel_data;
    short int *time = (short int *) timeMsg.pixel_data;
    short int *moves = (short int*) movesIMG.pixel_data;
    short int *frog = (short int *) froggy.pixel_data;
    short int *frogSafe = (short int*) froggySafeIMG.pixel_data;
    short int *robot1 = (short int*) robot.pixel_data;
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
    struct obstacle robots[15];
    robots[0].obstacleX = 1036;
    robots[0].obstacleY = 572;
    robots[0].speed = 1000000;
    robots[0].paused = 0;
    robots[0].exitCondition = 0;

    robots[1].obstacleX = 1100;
    robots[1].obstacleY = 572;
    robots[1].speed = 1000500;
    robots[1].paused = 0;
    robots[1].exitCondition = 0;

    robots[2].obstacleX = 537;
    robots[2].obstacleY = 507;
    robots[2].speed = 2000000;
    robots[2].paused = 0;
    robots[2].exitCondition = 0;

    robots[3].obstacleX = 665;
    robots[3].obstacleY = 507;
    robots[3].speed = 2000000;
    robots[3].paused = 0;
    robots[3].exitCondition = 0;

    robots[4].obstacleX = 1036;
    robots[4].obstacleY = 444;
    robots[4].speed = 1000000;
    robots[4].paused = 0;
    robots[4].exitCondition = 0;


    robots[5].obstacleX = 1100;
    robots[5].obstacleY = 444;
    robots[5].speed = 1000500;
    robots[5].paused = 0;
    robots[5].exitCondition = 0;


    robots[6].obstacleX = 1036;
    robots[6].obstacleY = 380;
    robots[6].speed = 1000000;
    robots[6].paused = 0;
    robots[6].exitCondition = 0;


    robots[7].obstacleX = 1100;
    robots[7].obstacleY = 380;
    robots[7].speed = 1000500;
    robots[7].paused = 0;
    robots[7].exitCondition = 0;


    robots[8].obstacleX = 601;
    robots[8].obstacleY = 316;
    robots[8].speed = 3000000;
    robots[8].paused = 0;
    robots[8].exitCondition = 0;


    robots[9].obstacleX = 665;
    robots[9].obstacleY = 316;
    robots[9].speed = 3000000;
    robots[9].paused = 0;
    robots[9].exitCondition = 0;


    robots[10].obstacleX = 665;
    robots[10].obstacleY = 252;
    robots[10].speed = 1000000;
    robots[10].paused = 0;
    robots[10].exitCondition = 0;

    robots[11].obstacleX = 665;
    robots[11].obstacleY = 188;
    robots[11].speed = 4000000;
    robots[11].paused = 0;
    robots[11].exitCondition = 0;

    robots[12].obstacleX = 729;
    robots[12].obstacleY = 188;
    robots[12].speed = 4000000;
    robots[12].paused = 0;
    robots[12].exitCondition = 0;


    robots[13].obstacleX = 1036;
    robots[13].obstacleY = 124;
    robots[13].speed = 1000000;
    robots[13].paused = 0;
    robots[13].exitCondition = 0;

    robots[14].obstacleX = 1100;
    robots[14].obstacleY = 124;
    robots[14].speed = 1000500;
    robots[14].paused = 0;
    robots[14].exitCondition = 0;

    // Drawing out the stage, lives and moves
    drawStageRobots(pixel);  
    drawLivesRobot(numLives);
    drawMovesRobot(numMoves);

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

    pthread_create(&timeThread, NULL, &updateTimeRobot, gameValues);
    pthread_create(&scoreThread, NULL, &updateScoreRobot, gameValues);

    pthread_create(&a1, NULL, &moveRobotLeft, (void *)&robots[0]); 
    pthread_create(&a2, NULL, &moveRobotLeft, (void *)&robots[1]); 

    pthread_create(&a3, NULL, &moveRobotRight, (void *)&robots[2]);
    pthread_create(&a4, NULL, &moveRobotRight, (void *)&robots[3]);
    pthread_create(&a5, NULL, &moveRobotLeft, (void *)&robots[4]);
    pthread_create(&a6, NULL, &moveRobotLeft, (void *)&robots[5]);
    pthread_create(&a7, NULL, &moveRobotLeft, (void *)&robots[6]);
    pthread_create(&a8, NULL, &moveRobotLeft, (void *)&robots[7]);
    pthread_create(&a9, NULL, &moveRobotRight, (void *)&robots[8]);
    pthread_create(&a10, NULL, &moveRobotRight, (void *)&robots[9]);
    pthread_create(&a11, NULL, &moveRobotRight, (void *)&robots[10]);
    pthread_create(&a12, NULL, &moveRobotRight, (void *)&robots[11]);
    pthread_create(&a13, NULL, &moveRobotRight, (void *)&robots[12]);
    pthread_create(&a14, NULL, &moveRobotLeft, (void *)&robots[13]); 
    pthread_create(&a15, NULL, &moveRobotLeft, (void *)&robots[14]); 


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
                drawMovesRobot(numMoves);
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
                drawMovesRobot(numMoves);
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
                drawMovesRobot(numMoves);
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
                drawMovesRobot(numMoves);
                gameValues -> movesLeft = numMoves;

            }
        }

        // End zone has been reached
        if (yPos == 60) { 
            // Loop through the obstacle threads and change the values
            for (int i = 0; i < 15; i++) {
                robots[i].paused = 1;
            }

            for (int i = 0; i < 15; i++) {
                robots[i].exitCondition = 1;
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
            check = collisionCheckRobots(robots[i], xPos, yPos, initXPos, initYPos);
            if (check == 1) {
                gameValues -> lives = numLives - 1;
                drawLivesRobot(numLives-1);
                xPos = initXPos;
                yPos = initYPos;
            }
        }

        // If lives == 0 or time == 0 or moves == 0 
        if (numLives == 0 || currTime == 0 || currMoves == 0) {
            gameValues -> loseFlag = 1;
        }

        if (loseCheck == 1) { // If lose pause the threads
            for (int i = 0; i < 15; i++) { // loop through and change pause values
                robots[i].paused = 1;
            }

            for (int i = 0; i < 15; i++) { // loop through and change exit values
                robots[i].exitCondition = 1;
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
            gameValues -> value1 = 1;
        }
        int value1Check = gameValues -> value1;
        if (value1Check == 1) {
            drawValuePack1();
        }
        // If player obtains value pack, increase moves by 10
        if (value1Check == 1 && ((xPos == 850) && (yPos == 252))){
            numMoves += 10;
            drawMovesRobot(numMoves);
            gameValues -> movesLeft = numMoves;
            gameValues -> value1 = 0;
        }

        // Pause Menu (Start Button)
        if (num == 6) {
            for (int i = 0; i < 15; i++) {
                robots[i].paused = 1;
            }


            gameValues -> pauseButtonPressed = 1;

            int option = pauseMenuPressed(pixel, gpioPtr, buttonArray);

            // Restart Game Pressed
            if (option == 0) { // loop and change exit condition
                for (int i = 0; i < 15; i++) {
                    robots[i].exitCondition = 1;
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
                    robots[i].exitCondition = 1;
                }
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
                drawStageRobots(pixel);
                numLives = gameValues -> lives;
                numMoves = gameValues -> movesLeft;

                drawImage(frog, pixel, xPos, yPos, 64, 64); 

                // Redraw lives and moves
                drawLivesRobot(numLives);
                drawMovesRobot(numMoves);
                for (int i = 0; i < 14; i++) { // unpause threads
                    robots[i].paused = 0;
                }
                for (int i = 0; i < 14; i++) {
                    robots[i].paused = 0;
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
void *moveRobotLeft(void *arguments) {
    struct obstacle *robots1 = (struct test *)arguments;
    int black = 0x0000;
    short int *robot1Image = (short int*) robot.pixel_data;
    int robot1X = robots1 -> obstacleX;
    int robot1Y = robots1 -> obstacleY;
    int initialX = robot1X;
    int robotSpeed = robots1 -> speed;
    int pausedPressed = robots1 -> paused;
    int exit = robots1 -> exitCondition;


    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));

    while(1) {
        pausedPressed = robots1 -> paused;
        exit = robots1 -> exitCondition;
        if (exit) {
            break;
        }
        if (pausedPressed) { // if paused
        } else {
            if (robot1X < 500) { // if obstacle reaches end of screen
                robot1X = initialX;
            } else { // if in screen, draw the obstacle
                drawImage(robot1Image, pixel, robot1X, robot1Y, 64, 64);
                usleep(robotSpeed);
                drawBlock(pixel, black, robot1X, robot1Y, 64, 64);
                robot1X -= 64; // move it left by 64
                robots1 -> obstacleX = robot1X;
            }
        }
    }
    pthread_exit(NULL);
}

/*
This thread function is used to move the obstacles right to left  
*/
void *moveRobotRight(void *arguments) {
    struct obstacle *robots1 = (struct test *)arguments;
    int black = 0x0000;
    short int *robot1Image = (short int*) robot.pixel_data;
    int robot1X = robots1 -> obstacleX;
    int robot1Y = robots1 -> obstacleY;
    int initialX = robot1X;
    int robotSpeed = robots1 -> speed;
    int pausedPressed = robots1 -> paused;
    int exit = robots1 -> exitCondition;


    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));

    while(1) {
        pausedPressed = robots1 -> paused;
        exit = robots1 -> exitCondition;
        if (exit) { // if exit
            break;
        }
        if (pausedPressed) { // if paused
        } else {
            if (robot1X > 1136) { // if the obstacle reaches the end of the screen reset
                robot1X = initialX;
            } else {
                drawImage(robot1Image, pixel, robot1X, robot1Y, 64, 64);
                usleep(robotSpeed);
                drawBlock(pixel, black, robot1X, robot1Y, 64, 64);
                robot1X += 64; // moving robot to the right by 64
                robots1 -> obstacleX = robot1X;
            }
        }
    }
    pthread_exit(NULL);
}

/*
This thread function updates the score as the game progresses 
*/
void *updateScoreRobot(void *arguments) {
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
            int numDigits = countNumDigitsRobots(currScore);
            if (numDigits == 1) { // draw first digit
                xStart = 150;
                yStart = 210;
                drawNumRobot(currScore, xStart, yStart);
                drawBlock(pixel, black, 190, 50, 32, 40);
                drawBlock(pixel, black, 230, 50, 32, 40);
                drawBlock(pixel, black, 270, 50, 32, 40); 

            }
            if (numDigits == 2) { //draw two digits
                int digit1 = currScore / 10;
                int digit2 = currScore % 10; 
                drawNumRobot(digit1, 150, 50);
                drawNumRobot(digit2, 190, 50);
                drawBlock(pixel, black, 230, 50, 32, 40); 
                drawBlock(pixel, black, 270, 50, 32, 40); 
            }
            if (numDigits == 3) { // draws three digits
                int digit3 = currScore % 10;
                int nextTime = currScore / 10;
                int digit2 = nextTime % 10;
                nextTime = nextTime / 10;
                int digit1 = nextTime % 10;
                drawNumRobot(digit1, 150, 50);
                drawNumRobot(digit2, 190, 50);
                drawNumRobot(digit3, 230, 50);
                drawBlock(pixel, black, 270, 50, 32, 40); 

            }
            if (numDigits == 4) { // draws four digits
                int digit4 = currScore % 10;
                int nextNum = currScore / 10;
                int digit3 = currScore % 10;
                nextNum = currScore / 10;
                int digit2 = nextNum % 10;
                nextNum /= 10;
                int digit1 = nextNum % 10;
                drawNumRobot(digit1, 150, 50);
                drawNumRobot(digit2, 190, 50);
                drawNumRobot(digit3, 230, 50);
                drawNumRobot(digit4, 270, 50);

            }
        }
        usleep(100000);

    }

}

/*
This thread function is used to update the time 
*/
void *updateTimeRobot(void *arguments) {
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
            numDigits = countNumDigitsRobots(totalTime);
            if (numDigits == 1) { // draws one digit
                xStart = 150;
                yStart = 210;
                drawNumRobot(totalTime, xStart, yStart);
                drawBlock(pixel, black, 190, 210, 32, 40);
                drawBlock(pixel, black, 230, 210, 32, 40);

            }
            if (numDigits == 2) { // draws two digits
                int digit1 = totalTime / 10;
                int digit2 = totalTime % 10; 
                drawNumRobot(digit1, 150, 210);
                drawNumRobot(digit2, 190, 210);
                drawBlock(pixel, black, 230, 210, 32, 40); 

            }
            if (numDigits == 3) { // draws three digits
                int digit3 = totalTime % 10;
                int nextTime = totalTime / 10;
                int digit2 = nextTime % 10;
                nextTime = nextTime / 10;
                int digit1 = nextTime % 10;
                drawNumRobot(digit1, 150, 210);
                drawNumRobot(digit2, 190, 210);
                drawNumRobot(digit3, 230, 210);

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
int countNumDigitsRobots(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        ++count;
    }
    return count;

}

/*
Checks to see if a collision happens with any obstacle 
@param alligator -> the car structure 
@param xPosition -> frogs x pos 
@param yPosition -> frogs y pos 
@param initXPosition -> the frogs original start x postion 
@param initYPosition -> the frogs original start y postion 
*/
int collisionCheckRobots(struct obstacle alligator, int xPosition, int yPosition, int initXPosition, int initYPosition) {
    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));
    short int *frog = (short int *) froggy.pixel_data;

    int black = 0x0000;

    // Checking to see if a collision happens
    if ((alligator.obstacleX <= xPosition) && (xPosition <= alligator.obstacleX + 64)) {
        if((alligator.obstacleY <= yPosition + 64) && (yPosition + 32 <= alligator.obstacleY + 64)){
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
void drawMovesRobot(int numMoves) {
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



    int numDigits = countNumDigitsRobots(numMoves);
    if (numDigits == 1) { // draws one digit
        xStart = 150;
        yStart = 290;
        drawNumRobot(numMoves, xStart, yStart);
        drawBlock(pixel, black, 190, 290, 32, 40);
        drawBlock(pixel, black, 230, 290, 32, 40);
    }
    if (numDigits == 2) { // draws two digits
        int digit1 = numMoves / 10;
        int digit2 = numMoves % 10; 
        drawNumRobot(digit1, 150, 290);
        drawNumRobot(digit2, 190, 290);
        drawBlock(pixel, black, 230, 290, 32, 40); 
    }
    if (numDigits == 3) { // draws three digits
        int digit3 = numMoves % 10;
        int nextTime = numMoves / 10;
        int digit2 = nextTime % 10;
        nextTime = nextTime / 10;
        int digit1 = nextTime % 10;
        drawNumRobot(digit1, 150, 290);
        drawNumRobot(digit2, 190, 290);
        drawNumRobot(digit3, 230, 290);
    }

}


/*
Draws out the lives left.
@param numLives -> the lives  left 
*/
void drawLivesRobot(int numLives) {
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
    drawBlock(pixel, black, 190, 110, 32, 40);
    drawNumRobot(numLives, 190,120);


}

/*
Draws out numbers .
@param num -> the number itself
@param xPos -> x position of number
@param yPos -> y position of number  
*/
void drawNumRobot(int num, int xPos, int yPos) {
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
void drawStageRobots(Pixel *pixel) {

    int borderColor = 0x7E0;
    int black = 0x0000;
    int safeColor = 0x04B0;
    short int *stage2Text1 = (short int *) stage2.pixel_data;
    short int *score = (short int *) scoreMsg.pixel_data;
    short int *lives = (short int *) livesMsg.pixel_data;
    short int *time = (short int *) timeMsg.pixel_data;
    short int *moves = (short int*) movesIMG.pixel_data;


    drawBorder(pixel, borderColor, 1200, 700);
    drawInnerBackground(pixel, black);
    drawBlock(pixel, borderColor, 500, 0, 3, 700);

    drawBlock(pixel, borderColor, 500, 54, 700, 3);

    drawImage(stage2Text1, pixel, 10, 10, 80, 40);
    drawImage(score, pixel, 5, 70, 80, 20);
    drawImage(lives, pixel, 10, 130, 80, 20);
    drawImage(time, pixel, 13, 220, 80, 20);
    drawImage(moves, pixel, 10, 300, 80, 20);

    // End Zone
    drawBlock(pixel, safeColor, 503, 60, 697, 64);

    // Start Zone
    drawBlock(pixel, safeColor, 503, 636, 697, 64);




}
