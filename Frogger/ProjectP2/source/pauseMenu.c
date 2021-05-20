#include "drawFunctions.h"
#include "pixelStruct.h"
#include "SNESSController.h"
#include "images/options.c"
#include "images/restartGame.c"
#include "images/quitGamePause.c"

/*
This function draws out the paused screen
@param pixel -> pixel used to draw
@param gpioPtr -> Base GPIO address
@param buttonArray -> an array of buttons used to see which button is pressed
*/
int pauseMenuPressed(Pixel *pixel, unsigned int* gpioPtr, int buttonArray[]) {

    int borderColor = 0x7E0;
    int test = 0xFFFF;
    int black = 0x0000;
    int *optionText = (int *) optionsMsg.pixel_data;
    int *restartGameText = (int *) restartMsg.pixel_data;
    int *quitGameText = (int *) quitMsg.pixel_data;

    //drawing out the screen
    drawBorder(pixel, test, 1200, 700);
    drawInnerBackground(pixel, black);
    drawImage(optionText, pixel, 525, 10, 150, 60);
    drawImage(quitGameText, pixel, 510, 450, 180, 30);
    drawRestartSelection(pixel);

    //Initializing variables
    int restartFlag = 0;
    int quitFlag = 0;
    int resumeFlag = 0;
    int restartSelection = 1;
    int quitSelection = 0;
    int resumeSelection = 0;

    //start loop to see what user selects
    while (restartFlag == 0 && quitFlag == 0 && resumeFlag == 0) {
        int num = Read_SNES(gpioPtr, buttonArray);
        // Move Down
        if (num == 1) { //moves to quit selection
            drawPauseQuitSelection(pixel);
            quitSelection = 1;
            restartSelection = 0;
        }

        // Move Up
        if (num == 4) { //moves to restart selection
            drawRestartSelection(pixel);
            restartSelection = 1;
            quitSelection = 0;
        }

        if (num == 5 && restartSelection == 1) {  //moves to restart and clicks it
            restartFlag = 1;
            return 0;
        }

        if (num == 5 && quitSelection == 1) { //moves to quit and clicks it
            quitFlag = 1;
            return 1;
        }

        if (num == 6) {   //game is resumed
            resumeFlag = 1;
            return 2;
        }





    }



}

/*
This function draws out the  restart section
@param pixel -> pixel used to draw
*/
void drawRestartSelection(Pixel *pixel) {
    int black = 0x0000;
    int selectionBoxColor = 0x7E0;
    int *restartGameText = (int *) restartMsg.pixel_data;
    int *quitGameText = (int *) quitMsg.pixel_data;

    drawBlock(pixel, selectionBoxColor, 506, 356, 188, 38);
    // Clearing Quit Game selection
    drawBlock(pixel, black, 506, 446, 188, 38);

    drawImage(restartGameText, pixel, 510, 360, 180, 30);
    drawImage(quitGameText, pixel, 510, 450, 180, 30);

}


/*
This function draws out the  quit section
@param pixel -> pixel used to draw
*/
void drawPauseQuitSelection(Pixel *pixel) {
    int black = 0x0000;
    int selectionBoxColor = 0x7E0;
    int *restartGameText = (int *) restartMsg.pixel_data;
    int *quitGameText = (int *) quitMsg.pixel_data;

    drawBlock(pixel, selectionBoxColor, 506, 446, 188, 38);
    // Clearing Quit Game selection
    drawBlock(pixel, black, 506, 356, 188, 38);

    drawImage(restartGameText, pixel, 510, 360, 180, 30);
    drawImage(quitGameText, pixel, 510, 450, 180, 30);

}

/*
This function draws out the paused menu
@param pixel -> pixel used to draw
*/
void drawPauseMenu(Pixel *pixel) {
    int borderColor = 0x7E0;
    int test = 0xFFFF;
    int black = 0x0000;
    int *optionText = (int *) optionsMsg.pixel_data;
    int *restartGameText = (int *) restartMsg.pixel_data;
    int *quitGameText = (int *) quitMsg.pixel_data;

    drawBorder(pixel, test, 1200, 700);
    drawInnerBackground(pixel, black);
    drawImage(optionText, pixel, 525, 10, 150, 60);
    drawImage(quitGameText, pixel, 510, 450, 180, 30);
    drawRestartSelection(pixel);
}
