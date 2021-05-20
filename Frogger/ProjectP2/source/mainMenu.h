#ifndef mainMenu 
#define mainMenu 

#include "pixelStruct.h"

int drawMainMenu(Pixel *pixel, unsigned int *gpioPtr, int buttonArray[]);
void drawQuitSelection(Pixel *pixel);
void drawStartSelection(Pixel *pixel);

#endif

