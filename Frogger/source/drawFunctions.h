#ifndef drawFunctions
#define drawFunctions

#include "pixelStruct.h"
#include "framebuffer.h"

void drawBackground(Pixel *pixel, int colourValue);
void drawBorder(Pixel *pixel, int colorValue, int xwidth, int yheight);
void drawInnerBackground(Pixel *pixel, int colourValue);
void drawBlock(Pixel *pixel, int colourValue, int xstart, int ystart, int xsize, int ysize);
void drawImage(short int *alienPtr, Pixel *pixel, int xstart, int ystart, int height, int width);
void drawPixel(Pixel *pixel);

#endif
