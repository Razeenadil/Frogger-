#include "drawFunctions.h"
#include "pixelStruct.h"
#include "SNESSController.h"
#include "images/winMessage.c"
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

/* 
 * This function draws the win screen
 * @param gpioPtr -> Base GPIO address
 * @buttonArray[] -> An array of buttons used to see which butotn is pressed
 * @finalScore -> The final score 
 * Returns and integer (when a button is pressed)
 * */
int drawWinScreen(unsigned int *gpioPtr, int buttonArray [], int finalScore) {
    int borderColor = 0x7E0;
    int black = 0x0000;
    short int *winMSG = (short int *) winMessageIMG.pixel_data;

    Pixel *pixel;
    pixel =  malloc(sizeof(Pixel));

    drawBorder(pixel, borderColor, 1200, 700);
    drawInnerBackground(pixel, black);
    drawImage(winMSG, pixel, 300, 275, 600, 210);

    int numDigits = countNumDigitsWin(finalScore);

    if (numDigits == 1) {
        int xStart = 575;
        int yStart = 485;
        drawNumWin(finalScore, xStart, yStart);
    }
    if (numDigits == 2) {
        int digit1 = finalScore / 10;
        int digit2 = finalScore % 10;
        drawNumWin(digit1, 555, 485);
        drawNumWin(digit2, 595, 485);
    }
    if (numDigits == 3) {
    int digit3 = finalScore % 10;
    int nextValue = finalScore / 10;
    int digit2 = nextValue % 10;
    nextValue = nextValue / 10;
    int digit1 = nextValue % 10;
    drawNumWin(digit1, 535, 485);
    drawNumWin(digit2, 575, 485);
    drawNumWin(digit3, 615, 485); 

    }





    while (1) {

        int num = Read_SNES_anyInput(gpioPtr, buttonArray);

        if (num == 1) {
            return 1;
        }
    }


}

int countNumDigitsWin(int num) {
    int count = 0;
    while (num != 0) {
        num /= 10;
        ++count;
    }
    return count;
}

void drawNumWin(int num, int xPos, int yPos) {

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









