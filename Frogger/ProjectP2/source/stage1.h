#ifndef stage1
#define stage1

#include "pixelStruct.h"

int playStage1(Pixel *pixel, unsigned int *gpioPtr, int buttonArray[], GameOptions *gameValues);

void *moveALligatorLeft(void *i);
void *moveAlligatorRight(void *arguments);


#endif
