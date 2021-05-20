#include "drawFunctions.h"
#include "pixelStruct.h"
#include "SNESSController.h"
#include "pauseMenu.h"
#include "images/stage1Text.c"
#include "images/score.c"
#include "images/lives.c"
#include "images/time.c"
#include "images/keroppi.c"
#include "images/alligatorImage.c"
#include <unistd.h>

#include <pthread.h>


#define clearConsole() printf("\e[1;1H\e[2J")

void *moveAlligatorTest(void *i);

struct test {
    Pixel *pixel;
    int alligatorX;
    int alligatorY;
    int xoffset;
    int yoffset;
    int newRow; //make the other alligator on new row, each time a thread is created 

};

struct test alligatorStruct;


/*
This function generates a random num (1-5). This number is use see how long a horse thread should sleep for.
Parameters: none
return: @r - the generated random number
*/
int getRandom(){
    int r;
    r = rand() % 6;
    r = r + 1;
    return r;
}



int playStageTest1(Pixel *pixel, unsigned int *gpioPtr, int buttonArray[], int xoffset, int yoffset) {

    int borderColor = 0x7E0;
    int black = 0x0000;
    short int *stage1Text1 = (short int *) stage1.pixel_data;
    short int *score = (short int *) scoreMsg.pixel_data;
    short int *lives = (short int *) livesMsg.pixel_data;
    short int *time = (short int *) timeMsg.pixel_data;
    short int *frog = (short int *) froggy.pixel_data;
    short int *alligator = (short int*) alligatorIMG.pixel_data;

    //struct test *alligatorStruct = malloc(sizeof(struct test));
  //  struct test alligatorStruct;
    alligatorStruct.pixel = pixel;
    alligatorStruct.alligatorX = 1133;
    alligatorStruct.alligatorY = 603;
    alligatorStruct.xoffset = xoffset;
    alligatorStruct.yoffset = yoffset;
    alligatorStruct.newRow = 0;
    //alligatorStruct -> pixel = *pixel;
    //alligatorStruct -> alligatorX = 1133;
    //alligatorStruct -> alligatorY = 603;
    //alligatorStruct -> xoffset = xoffset;
    //alligatorStruct -> yoffset = yoffset;
    
    drawBorder(pixel, borderColor, 1200 + xoffset, 700 + yoffset);
    drawInnerBackground(pixel, black);
    drawBlock(pixel, borderColor, 500 + xoffset, 0 + yoffset, 3, 700);

    drawImage(stage1Text1, pixel, 10 + xoffset, 10 + yoffset, 80, 40);
    drawImage(score, pixel, 5 + xoffset, 70 + yoffset, 80, 20);
    drawImage(lives, pixel, 10 + xoffset, 100 + yoffset, 80, 20);
    drawImage(time, pixel, 13 + xoffset, 130 + yoffset, 80, 20);


    drawImage(frog, pixel, 850 + xoffset, 633 + yoffset, 64, 64); 

    int nextStageFlag = 0;
    int num = 0;
    int xPos = 850 + xoffset;
    int yPos = 633 + yoffset;
    int alligator1X = 1133;
    int alligator1Y = 603;

    pthread_t a1[5];
    pthread_attr_t attrMain;
    pthread_attr_init(&attrMain);
    int a1ID[5];

   // pthread_create(&a1, NULL, &moveAlligator, (void *)&alligatorStruct); 

    //assigning each thread an id and creating the threads
    //changed this up a bit 
    for(int i = 0; i < 5;i++){
        a1ID[i] = i;
        pthread_create(&a1[i],&attrMain, &moveAlligatorTest, (&a1ID[i]));
    }




    while (nextStageFlag == 0) {
        num = Read_SNES(gpioPtr, buttonArray);
        // Move Down
        if (num == 1) {
            drawBlock(pixel, black, xPos, yPos, 64, 64);
            yPos = yPos + 64;
            drawImage(frog, pixel, xPos, yPos, 64, 64);
        }
        // Move Up
        if (num == 4) {
            drawBlock(pixel, black, xPos, yPos, 64, 64);
            yPos = yPos - 64;
            drawImage(frog, pixel, xPos, yPos, 64, 64);
        }

        // Move Left
        if (num == 2) {
            drawBlock(pixel, black, xPos, yPos, 64, 64);
            xPos = xPos - 64;
            drawImage(frog, pixel, xPos, yPos, 64, 64);
        }

        // Move Right 
        if (num == 3) {
            drawBlock(pixel, black, xPos, yPos, 64, 64);
            xPos = xPos + 64;
            drawImage(frog, pixel, xPos, yPos, 64, 64);
        }

        // Moving Objects

//        drawImage(alligator, pixel, alligator1X + xoffset, alligator1Y + yoffset, 60, 30);
//        //// 0.5 seconds
//        usleep(500000);
//        drawBlock(pixel, black, alligator1X + xoffset, alligator1Y + yoffset, 60, 30);
//        alligator1X -= 60;


        // Pause Menu (Start Button)
        if (num == 6) {
            int option = pauseMenuPressed(pixel, gpioPtr, buttonArray, xoffset, yoffset);
            if (option == 0) {
                return 0;
            } else if (option == 1) {
                return 1;
            }
            if (option == 2) {
                // Continue Game
                drawBorder(pixel, borderColor, 1200 + xoffset, 700 + yoffset);
                drawInnerBackground(pixel, black);
                drawBlock(pixel, borderColor, 500 + xoffset, 0 + yoffset, 3, 700);

                drawImage(stage1Text1, pixel, 10 + xoffset, 10 + yoffset, 80, 40);
                drawImage(score, pixel, 5 + xoffset, 70 + yoffset, 80, 20);
                drawImage(lives, pixel, 10 + xoffset, 100 + yoffset, 80, 20);
                drawImage(time, pixel, 13 + xoffset, 130 + yoffset, 80, 20);
                drawImage(frog, pixel, xPos, yPos, 64, 64); 
                continue;
            }

        }


    }
}



void *moveAlligatorTest(void *arguments) {
   // struct test *alligatorStruct = (struct test *)arguments;
    int black = 0x0000;
    short int *alligator = (short int*) alligatorIMG.pixel_data;
   // Pixel *pixel = alligatorStruct -> pixel;
   // int alligator1X = alligatorStruct -> alligatorX;
   // int xoffset = alligatorStruct -> xoffset;
   // int alligator1Y = alligatorStruct -> alligatorY;
  //  int yoffset = alligatorStruct -> yoffset;
   
    while(1) {
        //get a random number so all the alligators dont start at the same time 
        int ranSleep = getRandom();
        ranSleep = ranSleep * 10000;

        if(ranSleep % 2 == 0){  //alligator moves right to left 
            
        usleep(ranSleep);
        drawImage(alligator, alligatorStruct.pixel, alligatorStruct.alligatorX + alligatorStruct.xoffset, alligatorStruct.newRow + alligatorStruct.yoffset + alligatorStruct.newRow, 60, 30);
        usleep(500000);
        drawBlock(alligatorStruct.pixel, black, alligatorStruct.alligatorX + alligatorStruct.xoffset, alligatorStruct.newRow + alligatorStruct.yoffset + alligatorStruct.newRow, 60, 30);
        alligatorStruct.alligatorX -= 60;
        alligatorStruct.newRow = alligatorStruct.newRow - 150;

        }else{ //alligator moves left to right 


            //im not too sure what to make the start x. I was thinking 0, but it should be the left side of the border 
            //but the y position decreases by 150 everytime and gets added to (alligatorStruct.alligator1Y + alligatorStruct.yoffset + alligatorStruct.newRow)
            usleep(ranSleep);
            drawImage(alligator, alligatorStruct.pixel, alligatorStruct.alligatorX + alligatorStruct.xoffset, alligatorStruct.alligatorY + alligatorStruct.yoffset + alligatorStruct.newRow, 60, 30);
            usleep(500000);
            drawBlock(alligatorStruct.pixel, black, alligatorStruct.alligatorX + alligatorStruct.xoffset, alligatorStruct.alligatorY + alligatorStruct.yoffset + alligatorStruct.newRow, 60, 30);
            alligatorStruct.alligatorX -= 60;  //this would be alligatorStruct.alligator1X += 60 cause we're moving in opposite direction
            alligatorStruct.newRow = alligatorStruct.newRow - 150;

        }

       // usleep(ranSleep);
        //drawImage(alligator, alligatorStruct.pixel, alligatorStruct.alligator1X + alligatorStruct.xoffset, alligatorStruct.alligator1Y + alligatorStruct.yoffset + alligatorStruct.newRow, 60, 30);
        //usleep(500000);
        //drawBlock(alligatorStruct.pixel, black, alligatorStruct.alligator1X + alligatorStruct.xoffset, alligatorStruct.alligator1Y + alligatorStruct.yoffset + alligatorStruct.newRow, 60, 30);
        //alligatorStruct.alligator1X -= 60;
      //  alligatorStruct.newRow = alligatorStruct.newRow - 150;
        }


}
