#include "drawFunctions.h"
#include "pixelStruct.h"
#include "SNESSController.h"
#include "images/loseMessage.c"

/*
This function draws out the lose screen
@param gpioPtr -> Base GPIO address
@param buttonArray -> an array of buttons used to see which button is pressed
*/

int drawLoseScreen(unsigned int *gpioPtr, int buttonArray[]) {
    int borderColor = 0xF800;
    int black = 0x0000;
    short int *loseMSG = (short int *) loseIMG.pixel_data;  //lose text

    //setting the pixels and allocating memory
    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));


    //drawing out the lose screen
    drawBorder(pixel, borderColor, 1200, 700);
    drawInnerBackground(pixel, black);
    drawImage(loseMSG, pixel, 300, 275, 600, 150);

    
    while (1) {
    int num = Read_SNES_anyInput(gpioPtr, buttonArray);
        if (num == 1) {
    return 1;
    }
    }




}
