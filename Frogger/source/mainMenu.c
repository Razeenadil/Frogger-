#include "drawFunctions.h"
#include "pixelStruct.h"
#include "SNESSController.h"
#include "images/mainMenuText.c"
#include "images/startGame.c"
#include "images/quitGame.c"
#include "images/frogLogo.c"

#define clearConsole() printf("\e[1;1H\e[2J")

/*
This function draws out the main menu screen
@param pixel -> pixel used to draw
@param gpioPtr -> Base GPIO address
@param buttonArray -> an array of buttons used to see which button is pressed
*/
int drawMainMenu(Pixel *pixel, unsigned int *gpioPtr, int buttonArray[]) {
    //Pixel *pixel;
    int black = 0x0000;
    short int *mainMenuName = (short int *) mainText.pixel_data;
    short int *frogLogo = (short int *) frogLogoMain.pixel_data;
    short int *startGameText = (short int *) startText.pixel_data;
    short int *quitGameText = (short int *) quitText.pixel_data;
    int selectionBoxColor = 0x7E0;

    //drawing out the main menu screen
    drawBorder(pixel, selectionBoxColor, 1200, 700);
    drawInnerBackground(pixel, black);
    drawImage(mainMenuName, pixel, 344, 100, 531, 68);

    drawImage(frogLogo, pixel, 472, 170, 256, 256);

    drawBlock(pixel, selectionBoxColor, 544, 398, 112, 24);

    drawImage(startGameText, pixel, 546, 400, 108, 20);
    drawImage(quitGameText, pixel, 546, 450, 108, 20);

    //Initializing variables
    int num = 0;
    int startFlag = 0;
    int endFlag = 0;
    int startSelection = 1;
    int quitSelection = 0;

    //loop to see which option user selected
    while (startFlag == 0 && endFlag == 0) {
        num = Read_SNES(gpioPtr, buttonArray);
        if (num == 1) { //moves controller to quit section
            drawQuitSelection(pixel);
            startSelection = 0;
            quitSelection = 1;
        }

        if (num == 4) { //moves contorller to start section
            drawStartSelection(pixel);
            startSelection = 1;
            quitSelection = 0;
        }

        if (num == 5 && startSelection == 1) {  //moves controller to start section and clicks start
            startFlag = 1;
            return 1;
        }

        if (num == 5 && quitSelection == 1) { //moves contorller to quit section and clicks quit
            endFlag = 1;
            return 0;
        }
    }
}


/*
This function draws out the box aorund the start section
@param pixel -> pixel used to draw
*/
void drawStartSelection(Pixel *pixel) {
    int black = 0x0000;
    int *mainMenuName = (int *) mainText.pixel_data;
    int *startGameText = (int *) startText.pixel_data;
    int *quitGameText = (int *) quitText.pixel_data;
    int selectionBoxColor = 0x7E0;


    drawBlock(pixel, selectionBoxColor, 544, 398, 112, 24);
    // Clearing Quit Game selection
    drawBlock(pixel, black, 544, 448, 112, 24);

    drawImage(startGameText, pixel, 546, 400, 108, 20);
    drawImage(quitGameText, pixel, 546, 450, 108, 20);

}

/*
This function draws out the draw box around quit section 
@param pixel -> pixel used to draw
*/
void drawQuitSelection(Pixel *pixel) {
    int black = 0x0000;
    int *mainMenuName = (int *) mainText.pixel_data;
    int *startGameText = (int *) startText.pixel_data;
    int *quitGameText = (int *) quitText.pixel_data;
    int selectionBoxColor = 0x7E0;

    drawBlock(pixel, selectionBoxColor, 544, 448, 112, 24);
    // Clearing start game selection
    drawBlock(pixel, black, 544, 398, 112, 24);

    drawImage(startGameText, pixel, 546, 400, 108, 20);
    drawImage(quitGameText, pixel, 546, 450, 108, 20);

}
