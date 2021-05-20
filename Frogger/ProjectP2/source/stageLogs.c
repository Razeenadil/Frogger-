#include "drawFunctions.h"
#include "pixelStruct.h"
#include "gameOptions.h"
#include "SNESSController.h"
#include "pauseMenu.h"
#include "loseScreen.h"
#include "images/valuePack.c"
#include "images/stage4Text.c"
#include "images/froggySafe.c"
#include "images/score.c"
#include "images/lives.c"
#include "images/time.c"
#include "images/moves.c"
#include "images/keroppi.c"
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
#include "images/log1.c"
#include "images/frogOnLog.c"
#include "images/castle.c"
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>


#define clearConsole() printf("\e[1;1H\e[2J")

void *moveLogLeft(void *i);
void *moveLogRight(void *arguments);
void *updateTimeLogs(void *arguments);
void *updateScoreLogs(void *arguments); 

// Structure for the obstacles
struct obstacle {
    int obstacleX;
    int obstacleY;
    int speed;
    int paused;
    int exitCondition;
    bool leftColl;
};


/*
This function starts the first stage and returns apporite values depending on the players outcome 
@param pixel -> pixel used to draw
@param gpioPtr -> Base GPIO address
@param buttonArray -> an array of buttons used to see which button is pressed
@param gameValues -> structure for game values 
*/
int playStageLogs(Pixel *pixel, unsigned int *gpioPtr, int buttonArray[], GameOptions *gameValues) {

    int borderColor = 0x7E0;
    int black = 0x0000;
    int safeColor = 0x04B0;

    // Images
    short int *frogSafe = (short int*) froggySafeIMG.pixel_data;
    short int *frogLog = (short int *) frogOnLog.pixel_data;
    short int *logOne = (short int *) log1.pixel_data;
    short int *stage4Text1 = (short int *) stage4.pixel_data;
    short int *score = (short int *) scoreMsg.pixel_data;
    short int *lives = (short int *) livesMsg.pixel_data;
    short int *time = (short int *) timeMsg.pixel_data;
    short int *moves = (short int*) movesIMG.pixel_data;
    short int *frog = (short int *) froggy.pixel_data;
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
    short int *castleIMG = (short int*) castle.pixel_data;
    short int *valuePack = (short int*) valuePackIMG.pixel_data;

    // Initializing game values
    int numLives = gameValues -> lives;
    int numMoves = gameValues -> movesLeft;
    int currScore = gameValues -> score;
    int initTime = gameValues -> time;

    //initalize the structure for the obstacles
    struct obstacle logs[30];

    logs[0].obstacleX = 1111;
    logs[0].obstacleY = 572;
    logs[0].speed = 2000000;
    logs[0].paused = 0;
    logs[0].exitCondition = 0;
    logs[0].leftColl = false;

    logs[1].obstacleX = 1030;
    logs[1].obstacleY = 572;
    logs[1].speed = 1005000;
    logs[1].paused = 0;
    logs[1].exitCondition = 0;
    logs[1].leftColl = false;

    logs[2].obstacleX = 949;
    logs[2].obstacleY = 572;
    logs[2].speed = 1005000;
    logs[2].paused = 0;
    logs[2].exitCondition = 0;
    logs[2].leftColl = false;

    //third log
    logs[3].obstacleX = 537;
    logs[3].obstacleY = 508;
    logs[3].speed = 2000000;
    logs[3].paused = 0;
    logs[3].exitCondition = 0;
    logs[3].leftColl = false;

    //fourth log
    logs[4].obstacleX = 618;
    logs[4].obstacleY = 508;
    logs[4].speed = 1005000;
    logs[4].paused = 0;
    logs[4].exitCondition = 0;
    logs[4].leftColl = false;

    logs[5].obstacleX = 699;
    logs[5].obstacleY = 508;
    logs[5].speed = 1000000;
    logs[5].paused = 0;
    logs[5].exitCondition = 0;
    logs[5].leftColl = false;

    logs[6].obstacleX = 504;
    logs[6].obstacleY = 444;
    logs[6].speed = 3000000;
    logs[6].paused = 0;
    logs[6].exitCondition = 0;
    logs[6].leftColl = false;

    logs[7].obstacleX = 581;
    logs[7].obstacleY = 444;
    logs[7].speed = 3000000;
    logs[7].paused = 0;
    logs[7].exitCondition = 0;
    logs[7].leftColl = false;

    logs[8].obstacleX = 662;
    logs[8].obstacleY = 444;
    logs[8].speed = 3000000;
    logs[8].paused = 0;
    logs[8].exitCondition = 0;
    logs[8].leftColl = false;

    logs[9].obstacleX = 743;
    logs[9].obstacleY = 444;
    logs[9].speed = 3000000;
    logs[9].paused = 0;
    logs[9].exitCondition = 0;
    logs[9].leftColl = false;

    logs[10].obstacleX = 824;
    logs[10].obstacleY = 444;
    logs[10].speed = 3000000;
    logs[10].paused = 0;
    logs[10].exitCondition = 0;
    logs[10].leftColl = false;

    logs[11].obstacleX = 504;
    logs[11].obstacleY = 380;
    logs[11].speed = 3000000;
    logs[11].paused = 0;
    logs[11].exitCondition = 0;
    logs[11].leftColl = false;

    logs[12].obstacleX = 581;
    logs[12].obstacleY = 380;
    logs[12].speed = 3000000;
    logs[12].paused = 0;
    logs[12].exitCondition = 0;
    logs[12].leftColl = false;

    logs[13].obstacleX = 662;
    logs[13].obstacleY = 380;
    logs[13].speed = 3000000;
    logs[13].paused = 0;
    logs[13].exitCondition = 0;
    logs[13].leftColl = false;

    logs[14].obstacleX = 743;
    logs[14].obstacleY = 380;
    logs[14].speed = 3000000;
    logs[14].paused = 0;
    logs[14].exitCondition = 0;
    logs[14].leftColl = false;

    logs[15].obstacleX = 824;
    logs[15].obstacleY = 380;
    logs[15].speed = 3000000;
    logs[15].paused = 0;
    logs[15].exitCondition = 0;
    logs[15].leftColl = false;

    logs[16].obstacleX = 824;
    logs[16].obstacleY = 316;
    logs[16].speed = 2000000;
    logs[16].paused = 0;
    logs[16].exitCondition = 0;
    logs[16].leftColl = false;    

    logs[17].obstacleX = 824;
    logs[17].obstacleY = 316;
    logs[17].speed = 1005000;
    logs[17].paused = 0;
    logs[17].exitCondition = 0;
    logs[17].leftColl = false;    

    logs[18].obstacleX = 824;
    logs[18].obstacleY = 316;
    logs[18].speed = 1200000;
    logs[18].paused = 0;
    logs[18].exitCondition = 0;
    logs[18].leftColl = false;    

    logs[19].obstacleX = 824;
    logs[19].obstacleY = 316;
    logs[19].speed = 1000000;
    logs[19].paused = 0;
    logs[19].exitCondition = 0;
    logs[19].leftColl = false;    

    logs[20].obstacleX = 1111;
    logs[20].obstacleY = 252;
    logs[20].speed = 3000000;
    logs[20].paused = 0;
    logs[20].exitCondition = 0;
    logs[20].leftColl = false;    

    logs[21].obstacleX = 1030;
    logs[21].obstacleY = 252;
    logs[21].speed = 2000000;
    logs[21].paused = 0;
    logs[21].exitCondition = 0;
    logs[21].leftColl = false;    

    logs[22].obstacleX = 949;
    logs[22].obstacleY = 252;
    logs[22].speed = 2000000;
    logs[22].paused = 0;
    logs[22].exitCondition = 0;
    logs[22].leftColl = false;    

    logs[23].obstacleX = 868;
    logs[23].obstacleY = 252;
    logs[23].speed = 2000000;
    logs[23].paused = 0;
    logs[23].exitCondition = 0;
    logs[23].leftColl = false;    

    logs[24].obstacleX = 868;
    logs[24].obstacleY = 188;
    logs[24].speed = 2000000;
    logs[24].paused = 0;
    logs[24].exitCondition = 0;
    logs[24].leftColl = false;    

    logs[25].obstacleX = 868;
    logs[25].obstacleY = 188;
    logs[25].speed = 2000000;
    logs[25].paused = 0;
    logs[25].exitCondition = 0;
    logs[25].leftColl = false;    

    logs[26].obstacleX = 868;
    logs[26].obstacleY = 188;
    logs[26].speed = 2000000;
    logs[26].paused = 0;
    logs[26].exitCondition = 0;
    logs[26].leftColl = false;    

    logs[27].obstacleX = 868;
    logs[27].obstacleY = 188;
    logs[27].speed = 2000000;
    logs[27].paused = 0;
    logs[27].exitCondition = 0;
    logs[27].leftColl = false;    

    // Drawing the stage, lives and moves
    drawStageLogs(pixel);
    drawLivesLogs(numLives);
    drawMovesLogs(numMoves);

    drawImage(frog, pixel, 850, 633, 64, 64); 

    // Setting initial values
    int nextStageFlag = 0;
    int num = 0;
    int xPos = 850;
    int initXPos = xPos;
    int yPos = 633;
    int initYPos = yPos;

    // Initializing hte threads for the obstacles
    pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    int play = 1;

    pthread_t l0, l1, l2, l3, l4, l5, l6,l7,l8,l9,l10, l11,l12,l13,l14,l15, l16,l17,l18,l19,l20,l21,l22,l23,l24,l25,l26,l27,timeThread, scoreThread;
    pthread_attr_t attrMain;
    pthread_attr_init(&attrMain);

    //initlize time and score threads
    pthread_create(&timeThread, NULL, &updateTimeLogs, gameValues);
    pthread_create(&scoreThread, NULL, &updateScoreLogs, gameValues);

    //initalize obstacle threads
    pthread_create(&l0, NULL, &moveLogLeft, (void *)&logs[0]); 
    pthread_create(&l1, NULL, &moveLogLeft, (void *)&logs[1]); 
    pthread_create(&l2, NULL, &moveLogLeft, (void *)&logs[2]); 
    pthread_create(&l3, NULL, &moveLogRight, (void *)&logs[3]); 
    pthread_create(&l4, NULL, &moveLogRight, (void *)&logs[4]); 
    pthread_create(&l5, NULL, &moveLogRight, (void *)&logs[5]); 
    pthread_create(&l6, NULL, &moveLogRight, (void *)&logs[6]); 
    pthread_create(&l7, NULL, &moveLogRight, (void *)&logs[7]); 
    pthread_create(&l8, NULL, &moveLogRight, (void *)&logs[8]); 
    pthread_create(&l9, NULL, &moveLogRight, (void *)&logs[9]); 
    pthread_create(&l10, NULL, &moveLogRight, (void *)&logs[10]); 
    pthread_create(&l11, NULL, &moveLogRight, (void *)&logs[11]); 
    pthread_create(&l12, NULL, &moveLogRight, (void *)&logs[12]); 
    pthread_create(&l13, NULL, &moveLogRight, (void *)&logs[13]); 
    pthread_create(&l14, NULL, &moveLogRight, (void *)&logs[14]); 
    pthread_create(&l15, NULL, &moveLogRight, (void *)&logs[15]); 
    pthread_create(&l16, NULL, &moveLogRight, (void *)&logs[16]); 
    pthread_create(&l17, NULL, &moveLogRight, (void *)&logs[17]); 
    pthread_create(&l18, NULL, &moveLogRight, (void *)&logs[18]); 
    pthread_create(&l19, NULL, &moveLogRight, (void *)&logs[19]); 
    pthread_create(&l20, NULL, &moveLogLeft, (void *)&logs[20]); 
    pthread_create(&l21, NULL, &moveLogLeft, (void *)&logs[21]); 
    pthread_create(&l22, NULL, &moveLogLeft, (void *)&logs[22]); 
    pthread_create(&l23, NULL, &moveLogLeft, (void *)&logs[23]); 
    pthread_create(&l24, NULL, &moveLogLeft, (void *)&logs[24]); 
    pthread_create(&l25, NULL, &moveLogLeft, (void *)&logs[25]); 
    pthread_create(&l26, NULL, &moveLogLeft, (void *)&logs[26]); 
    pthread_create(&l27, NULL, &moveLogLeft, (void *)&logs[27]); 




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
            if(yPos == 636){
                // End Zone
                drawBlock(pixel, safeColor, 503, 60, 697, 100);
                drawImage(castleIMG, pixel, 831, 57, 100, 100);


                // Start Zone
                drawBlock(pixel, safeColor, 503, 636, 697, 64);


                drawImage(frogSafe, pixel, xPos, yPos, 64, 64);
            }

            if (yPos + 64 < 697) {
                yPos = yPos + 64;
                // End Zone
                drawBlock(pixel, safeColor, 503, 60, 697, 100);
                drawImage(castleIMG, pixel, 831, 57, 100, 100);


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
                drawMovesLogs(numMoves);
                gameValues -> movesLeft = numMoves;

            }
        }
        // Move Up
        if (num == 4) {
            if (yPos - 64 > 0) {
                yPos = yPos - 64;
                // End Zone
                drawBlock(pixel, safeColor, 503, 60, 697, 100);
                drawImage(castleIMG, pixel, 831, 57, 100, 100);

                // Start Zone
                drawBlock(pixel, safeColor, 503, 636, 697, 64);

                if (yPos == 60) {
                    drawImage(frogSafe, pixel, xPos, yPos, 64, 64);
                    drawBlock(pixel, black, xPos, yPos + 64, 64, 64);

                }


                else if (yPos == 636) {
                    drawImage(frogSafe, pixel, xPos, yPos, 64, 64);

                } 
                else {
                    //int yCheck = 0;
                    //int testCheck = 0;
                    //for (int i = 0; i < 20; i++) {
                    //    testCheck = collisionCheckLogs(logs[i], xPos, yPos, initXPos, initYPos);
                    //    if (testCheck == 1) {
                    //        yCheck = 1;
                    //    }
                    //}


                    //if (yCheck == 0) {
                    //    gameValues -> lives = numLives - 1;
                    //    drawLivesLogs(numLives-1);
                    //    xPos = initXPos;
                    //    yPos = initYPos;
                    //    drawImage(frog, pixel, xPos, yPos, 64, 64);
                    //}  else{ 

                        drawBlock(pixel, black, xPos, yPos + 64, 64, 64);
                        drawImage(frog, pixel, xPos, yPos, 64, 64);
                    //}
                }
                numMoves -= 1;
                drawMovesLogs(numMoves);
                gameValues -> movesLeft = numMoves;

            }
        }

        // Move Left
        if (num == 2) {
            if (xPos - 64 > 500) {
                xPos = xPos - 64;
                // End Zone
drawBlock(pixel, safeColor, 503, 60, 697, 100);
                drawImage(castleIMG, pixel, 831, 57, 100, 100);

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
                drawMovesLogs(numMoves);
                gameValues -> movesLeft = numMoves;


            }
        }

        // Move Right 
        if (num == 3) {
            if (xPos + 64 < 1136) {
                xPos = xPos + 64;
                // End Zone
drawBlock(pixel, safeColor, 503, 60, 697, 100);
                drawImage(castleIMG, pixel, 831, 57, 100, 100);

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
                drawMovesLogs(numMoves);
                gameValues -> movesLeft = numMoves;

            }
        }

        int check;
        int initalX;
        int initalY;
        // Check if collision has occurred
        for (int i = 0; i < 30; i++) {
            check = collisionCheckLogs(logs[i], xPos, yPos, initXPos, initYPos);
            initalX = xPos;
            initalY = yPos;
            if (check == 1) {   //collision

                logs[i].leftColl = true;
                usleep(10000);
                xPos = logs[i].obstacleX; // Setting new xPos
                yPos = logs[i].obstacleY; // Setting new yPos

                if(xPos < 500 || xPos > 1136){ //frog went off the map (left or right)
                    gameValues -> lives = numLives - 1;
                    drawLivesLogs(numLives-1);
                    xPos = initXPos;
                    yPos = initYPos;
                    drawImage(frog, pixel, xPos, yPos, 64, 64);
                }
                break;

            }else{              //no collision
                logs[i].leftColl = false;
            }
        }

        // End zone has been reached
        if ((yPos <= 121) && ((731 <= xPos) && (xPos <= 1000))){
            // Loop sthrough the obstacle threads and change the values
            for (int i = 0; i < 30; i++) {
                logs[i].paused = 1;
                logs[i].exitCondition = 1;
            }
            // Cancel all threads
            pthread_cancel(l0);
            pthread_cancel(l1);
            pthread_cancel(l2);
            pthread_cancel(l3);
            pthread_cancel(l4);
            pthread_cancel(l5);
            pthread_cancel(l6);
            pthread_cancel(l7);
            pthread_cancel(l8);
            pthread_cancel(l9);
            pthread_cancel(l10);
            pthread_cancel(l11);
            pthread_cancel(l12);
            pthread_cancel(l13);
            pthread_cancel(l14);
            pthread_cancel(l15);
            pthread_cancel(l16);
            pthread_cancel(l17);
            pthread_cancel(l18);
            pthread_cancel(l19);
            pthread_cancel(l20);
            pthread_cancel(l21);
            pthread_cancel(l22);
            pthread_cancel(l23);
            pthread_cancel(l24);
            pthread_cancel(l25);
            pthread_cancel(l26);
            pthread_cancel(l27);

            pthread_cancel(timeThread);
            pthread_cancel(scoreThread);

            return 3;



        }

        // If lives == 0 or time == 0 or moves == 0 
        if (numLives == 0 || currTime == 0 || currMoves == 0) {
            gameValues -> loseFlag = 1;
        }

        if (loseCheck == 1) { // Lose the game
            for (int i = 0; i < 30; i++) { // Loop through and change pause values
                logs[i].paused = 1;
                logs[i].exitCondition = 1;
            }
            // Cancel all threads
            pthread_cancel(l0);
            pthread_cancel(l1);
            pthread_cancel(l2);
            pthread_cancel(l3);
            pthread_cancel(l4);
            pthread_cancel(l5);
            pthread_cancel(l6);
            pthread_cancel(l7);
            pthread_cancel(l8);
            pthread_cancel(l9);
            pthread_cancel(l10);
            pthread_cancel(l11);
            pthread_cancel(l12);
            pthread_cancel(l13);
            pthread_cancel(l14);
            pthread_cancel(l15);
            pthread_cancel(l16);
            pthread_cancel(l17);
            pthread_cancel(l18);
            pthread_cancel(l19);
            pthread_cancel(l20);
            pthread_cancel(l21);
            pthread_cancel(l22);
            pthread_cancel(l23);
            pthread_cancel(l24);
            pthread_cancel(l25);
            pthread_cancel(l26);
            pthread_cancel(l27);

            pthread_cancel(timeThread);
            pthread_cancel(scoreThread);

            gameValues -> pauseButtonPressed = 1;
            gameValues -> loseFlag = 0;
            int loseNum = drawLoseScreen(gpioPtr, buttonArray);
            return 1;
        }

        // Value Pack, if reached + 10 moves 
        if (initTime - currTime == 30) {
            gameValues -> valueLogs = 1;
        }

        int value4Check = gameValues -> valueLogs;

        if (value4Check == 1) {
            drawImage(valuePack, pixel, 786, 633, 32, 32);
        }

        // If player obtains value pack, increase moves by 10
        if (value4Check == 1 && ((xPos == 786) && (yPos == 633))) {
            numMoves += 10;
            drawMovesLogs(numMoves);
            gameValues -> movesLeft = numMoves;
            gameValues -> valueLogs = 0;
        }

        // Pause Menu (Start Button)
        if (num == 6) {
            for (int i = 0; i < 30; i++) {
                logs[i].paused = 1;
            }
            gameValues -> pauseButtonPressed = 1;

            int option = pauseMenuPressed(pixel, gpioPtr, buttonArray);

            // Restart Game Pressed
            if (option == 0) {
                for (int i = 0; i < 30; i++) {
                    logs[i].exitCondition = 1;
                }

                // Cancel all threads
                pthread_cancel(l0);
                pthread_cancel(l1);
                pthread_cancel(l2);
                pthread_cancel(l3);
                pthread_cancel(l4);
                pthread_cancel(l5);
                pthread_cancel(l6);
                pthread_cancel(l7);
                pthread_cancel(l8);
                pthread_cancel(l9);
                pthread_cancel(l10);
                pthread_cancel(l11);
                pthread_cancel(l12);
                pthread_cancel(l13);
                pthread_cancel(l14);
                pthread_cancel(l15);
                pthread_cancel(l16);
                pthread_cancel(l17);
                pthread_cancel(l18);
                pthread_cancel(l19);
                pthread_cancel(l20);
                pthread_cancel(l21);
                pthread_cancel(l22);
                pthread_cancel(l23);
                pthread_cancel(l24);
                pthread_cancel(l25);
                pthread_cancel(l26);
                pthread_cancel(l27);

                pthread_cancel(timeThread);
                pthread_cancel(scoreThread);


                gameValues -> pauseButtonPressed = 0;

                return 0;
            } 
            // Quit Game Pressed 
            else if (option == 1) {
                for (int i = 0; i < 30; i++) {
                    logs[i].exitCondition = 1;
                }

                // Cancel all threads
                pthread_cancel(l0);
                pthread_cancel(l1);
                pthread_cancel(l2);
                pthread_cancel(l3);
                pthread_cancel(l4);
                pthread_cancel(l5);
                pthread_cancel(l6);
                pthread_cancel(l7);
                pthread_cancel(l8);
                pthread_cancel(l9);
                pthread_cancel(l10);
                pthread_cancel(l11);
                pthread_cancel(l12);
                pthread_cancel(l13);
                pthread_cancel(l14);
                pthread_cancel(l15);
                pthread_cancel(l16);
                pthread_cancel(l17);
                pthread_cancel(l18);
                pthread_cancel(l19);
                pthread_cancel(l20);
                pthread_cancel(l21);
                pthread_cancel(l22);
                pthread_cancel(l23);
                pthread_cancel(l24);
                pthread_cancel(l25);
                pthread_cancel(l26);
                pthread_cancel(l27);
                pthread_cancel(scoreThread);


                pthread_cancel(timeThread);
                gameValues -> pauseButtonPressed = 0;

                return 1;
            }
            // Continue Game
            if (option == 2) {
                drawStageLogs(pixel);
                numLives = gameValues -> lives;
                numMoves = gameValues -> movesLeft;

                drawImage(frog, pixel, xPos, yPos, 64, 64); 

                // Redraw lives and moves
                drawLivesLogs(numLives);
                drawMovesLogs(numMoves);

                drawLivesLogs(numLives);
                for (int i = 0; i < 30; i++) { // unpause threads
                    logs[i].paused = 0;
                }
                for (int i = 0; i < 30; i++) {
                    logs[i].paused = 0;
                }


                gameValues -> pauseButtonPressed = 0;
                continue;
            }

        }


    }
}



/* This function checks if a collision has occurred*/
int collisionCheckLogs(struct obstacle logs, int xPosition, int yPosition, int initXPosition, int initYPosition) {

    if ((logs.obstacleX  - 40<= xPosition) && (xPosition <= logs.obstacleX + 80)) {
        if((logs.obstacleY <= yPosition + 32) && (yPosition + 32 <= logs.obstacleY + 60)){
            return 1;
        }
    } else {

        return 0;
    }
}

/*
This thread function is used to move the obstacles right to left  
*/
void *moveLogRight(void *arguments) {
    struct obstacle *log1Struct = (struct test *)arguments;
    short int *logger = (short int *) frogOnLog.pixel_data;
    short int *logOneIMG = (short int *) log1.pixel_data;
    short int *frog = (short int *) froggy.pixel_data;
    int black = 0x0000;
    int log1X = log1Struct -> obstacleX;
    int log1Y = log1Struct -> obstacleY;
    int initialX = log1X;
    int logSpeed = log1Struct -> speed;
    int pausedPressed = log1Struct -> paused;
    int exit = log1Struct -> exitCondition;
    bool left = log1Struct -> leftColl;

    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));

    while(1) {
        left = log1Struct -> leftColl;
        pausedPressed = log1Struct -> paused;
        exit = log1Struct -> exitCondition;
        if (exit) {
            break;
        }

        if (pausedPressed) { // if paused
        }else{
            if (log1X > 1120) { // if obstacled reaches end of screen
                log1X = initialX;
                log1Struct -> leftColl = false;
            }else if(left == false){  // Checks if collision has been made
                drawImage(logOneIMG, pixel, log1X, log1Y, 80, 60);
                usleep(logSpeed);
                drawBlock(pixel, black, log1X, log1Y, 80, 60);
                log1X += 64; // move right by 64
                log1Struct -> obstacleX = log1X;


            } else if (left == true){ // draws frog on log if collision made
                drawImage(logger, pixel, log1X, log1Y, 80, 60); 
                usleep(logSpeed);
                drawBlock(pixel, black, log1X, log1Y, 80, 60);
                log1X += 64; // move right by 64
                log1Struct -> obstacleX = log1X;
            }
        }
    }
    pthread_exit(NULL);
}


/*
This thread function is used to move the obstacles left to right 
*/
void *moveLogLeft(void *arguments) {
    struct obstacle *log1Struct = (struct test *)arguments;
    short int *logger = (short int *) frogOnLog.pixel_data;
    short int *logOneIMG = (short int *) log1.pixel_data;
    short int *frog = (short int *) froggy.pixel_data;
    int black = 0x0000;
    int log1X = log1Struct -> obstacleX;
    int log1Y = log1Struct -> obstacleY;
    int initialX = log1X;
    int logSpeed = log1Struct -> speed;
    int pausedPressed = log1Struct -> paused;
    int exit = log1Struct -> exitCondition;
    bool left = log1Struct -> leftColl;


    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));

    while(1) {
        left = log1Struct -> leftColl;
        pausedPressed = log1Struct -> paused;
        exit = log1Struct -> exitCondition;
        if (exit) {
            break;
        }

        if (pausedPressed) { // if paused
        }else{
            if (log1X < 520) { // if obstacle reaches end of screen
                log1X = initialX;
                log1Struct -> leftColl = false;

            }else if (left == false){ // checks if colliison occurs 
                drawImage(logOneIMG, pixel, log1X, log1Y, 80, 60);
                usleep(logSpeed);
                drawBlock(pixel, black, log1X, log1Y, 80, 60);
                log1X -= 64;
                log1Struct -> obstacleX = log1X;
            }else if (left == true){ // if collision occurs, draws frog on log
                drawImage(logger, pixel, log1X, log1Y, 80, 60); 
                usleep(logSpeed);
                drawBlock(pixel, black, log1X, log1Y, 80, 60);
                log1X -= 64;
                log1Struct -> obstacleX = log1X;
            }
        }
    }
    pthread_exit(NULL);
}

/*
This thread function updates the score as the game progresses 
*/
void *updateScoreLogs(void *arguments) {
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
            int numDigits = countNumDigitsLogs(currScore);
            if (numDigits == 1) { // draw first digit
                xStart = 150;
                yStart = 210;
                drawNumLogs(currScore, xStart, yStart);
                drawBlock(pixel, black, 190, 50, 32, 40);
                drawBlock(pixel, black, 230, 50, 32, 40);
                drawBlock(pixel, black, 270, 50, 32, 40); 

            }
            if (numDigits == 2) { // draw two digits
                int digit1 = currScore / 10;
                int digit2 = currScore % 10; 
                drawNumLogs(digit1, 150, 50);
                drawNumLogs(digit2, 190, 50);
                drawBlock(pixel, black, 230, 50, 32, 40); 
                drawBlock(pixel, black, 270, 50, 32, 40); 


            }
            if (numDigits == 3) { // draw three digits
                int digit3 = currScore % 10;
                int nextTime = currScore / 10;
                int digit2 = nextTime % 10;
                nextTime = nextTime / 10;
                int digit1 = nextTime % 10;
                drawNumLogs(digit1, 150, 50);
                drawNumLogs(digit2, 190, 50);
                drawNumLogs(digit3, 230, 50);
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
                drawNumLogs(digit1, 150, 50);
                drawNumLogs(digit2, 190, 50);
                drawNumLogs(digit3, 230, 50);
                drawNumLogs(digit4, 270, 50);

            }
        }
        usleep(100000);

    }

}

/*
This thread function is used to update the time 
*/
void *updateTimeLogs(void *arguments) {
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
            numDigits = countNumDigitsLogs(totalTime);
            if (numDigits == 1) { // draws one digit
                xStart = 150;
                yStart = 210;
                drawNumLogs(totalTime, xStart, yStart);
                drawBlock(pixel, black, 190, 210, 32, 40);
                drawBlock(pixel, black, 230, 210, 32, 40);

            }
            if (numDigits == 2) { // draws two digits
                int digit1 = totalTime / 10;
                int digit2 = totalTime % 10; 
                drawNumLogs(digit1, 150, 210);
                drawNumLogs(digit2, 190, 210);
                drawBlock(pixel, black, 230, 210, 32, 40); 

            }
            if (numDigits == 3) { // draws three digits
                int digit3 = totalTime % 10;
                int nextTime = totalTime / 10;
                int digit2 = nextTime % 10;
                nextTime = nextTime / 10;
                int digit1 = nextTime % 10;
                drawNumLogs(digit1, 150, 210);
                drawNumLogs(digit2, 190, 210);
                drawNumLogs(digit3, 230, 210);

            }

            // Update time
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
int countNumDigitsLogs(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        ++count;
    }
    return count;
}


/*
Draws out the moves left.
@param numMoves -> the moves left 
*/
void drawMovesLogs(int numMoves) {
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

    int numDigits = countNumDigitsLogs(numMoves);
    if (numDigits == 1) { // draws one digit
        xStart = 150;
        yStart = 290;
        drawNumLogs(numMoves, xStart, yStart);
        drawBlock(pixel, black, 190, 290, 32, 40);
        drawBlock(pixel, black, 230, 290, 32, 40);
    }
    if (numDigits == 2) { // draws two digits
        int digit1 = numMoves / 10;
        int digit2 = numMoves % 10; 
        drawNumLogs(digit1, 150, 290);
        drawNumLogs(digit2, 190, 290);
        drawBlock(pixel, black, 230, 290, 32, 40); 
    }
    if (numDigits == 3) { // draws three digits
        int digit3 = numMoves % 10;
        int nextTime = numMoves / 10;
        int digit2 = nextTime % 10;
        nextTime = nextTime / 10;
        int digit1 = nextTime % 10;
        drawNumLogs(digit1, 150, 290);
        drawNumLogs(digit2, 190, 290);
        drawNumLogs(digit3, 230, 290);
    }

}



/*
Draws out the lives left.
@param numLives -> the lives  left 
*/
void drawLivesLogs(int numLives) {
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
    drawNumLogs(numLives, 190,120);


}

/*
Draws out numbers .
@param num -> the number itself
@param xPos -> x position of number
@param yPos -> y position of number  
*/
void drawNumLogs(int num, int xPos, int yPos) {
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
void drawStageLogs(Pixel *pixel) {

    int borderColor = 0x7E0;
    int blue = 0x000000;
    int safeColor = 0x04B0;
    short int *stage4Text1 = (short int *) stage4.pixel_data;
    short int *score = (short int *) scoreMsg.pixel_data;
    short int *lives = (short int *) livesMsg.pixel_data;
    short int *time = (short int *) timeMsg.pixel_data;
    short int *moves = (short int*) movesIMG.pixel_data;
    short int *castleIMG = (short int*) castle.pixel_data;


    drawBorder(pixel, borderColor, 1200, 700);
    drawInnerBackground(pixel, blue);
    drawBlock(pixel, borderColor, 500, 0, 3, 700);

    drawBlock(pixel, borderColor, 500, 54, 700, 3);

    drawImage(stage4Text1, pixel, 10, 10, 80, 40);
    drawImage(score, pixel, 5, 70, 80, 20);
    drawImage(lives, pixel, 10, 130, 80, 20);
    drawImage(time, pixel, 13, 220, 80, 20);
    drawImage(moves, pixel, 10, 300, 80, 20);

    // End Zone
    drawBlock(pixel, safeColor, 503, 60, 697, 100);
    drawImage(castleIMG, pixel, 831, 57, 100, 100);

    // Castle
    drawImage(castleIMG, pixel, 831, 57, 100, 100);

    // Start Zone
    drawBlock(pixel, safeColor, 503, 636, 697, 64);
}
