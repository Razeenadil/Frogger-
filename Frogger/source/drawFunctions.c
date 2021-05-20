#include "pixelStruct.h"

/*
This class is contains all that functions related to drawing the map.
*/

/*
This funtion is used to draw vairous different drawBackgrounds.
@param pixel -> the pixel used to draw
@param colorValue -> the color of the background
*/
void drawBackground(Pixel *pixel, int colorValue) {
    //loop through the size of the background
    for (int y = 0; y < 700; y++) {
        for (int x = 0; x < 1200; x++) {
            //pixel -> color = 0xBDF7;
            pixel -> color = colorValue;
            pixel -> x = x;
            pixel -> y = y;
            drawPixel(pixel);
        }
    }
}

/*
This function is used to draw the borders of the map.
@param pixel -> the pixel used to draw
@param colorValue -> color of border
@param xwidth -> the width of the border
@param yheight -> the  height of the border
*/
void drawBorder(Pixel *pixel, int colorValue, int xwidth, int yheight) {
    // Top Border
    drawBlock(pixel, colorValue, 0, 0, xwidth, 3);
    // Left Border
    drawBlock(pixel, colorValue, 0, 0, 3, yheight);
    // Right Border
    drawBlock(pixel, colorValue, xwidth, 0, 3, yheight);
    // Bottom Border
    drawBlock(pixel, colorValue, 0, yheight, xwidth, 3);
}

/*
This function is used to draw the inner background of the map.
@param pixel -> the pixel used to draw
@param colorValue -> color of border
*/
void drawInnerBackground(Pixel *pixel, int colorValue) {
    //loop through the size of the background
     for (int y = 3; y < 700; y++) {
        for (int x = 3; x < 1200; x++) {
            //pixel -> color = 0xBDF7;
            pixel -> color = colorValue;
            pixel -> x = x;
            pixel -> y = y;
            drawPixel(pixel);
        }
    }
}


/*
This function is used to draw blocks where every needed.
@param pixel -> the pixel used to draw
@param colorValue -> color of border
@param xstart -> start point of the block x
@param ystart -> start point of block y
@param xsize -> the width of the block
@param ysize -> the  height of the block
*/
void drawBlock(Pixel *pixel, int colorValue, int xstart, int ystart, int xsize, int ysize) {
    //loop through the size of the block
    for (int y = ystart; y < (ystart+ysize); y++) {
        for (int x = xstart; x < (xstart+xsize); x++) {
            //pixel -> color = 0xBDF7;
            pixel -> color = colorValue;
            pixel -> x = x;
            pixel -> y = y;
            drawPixel(pixel);
        }
    }
}

/*
This function is used to draw any pixel image if the size of the image is known.
@param pixel -> the pixel used to draw
@param alienPtr -> color of image 
@param xstart -> start point of the block x
@param ystart -> start point of block y
@param xsize -> the width of the image
@param ysize -> the height of the image
*/
void drawImage (short int *alienPtr, Pixel *pixel, int xstart, int ystart, int width, int height) {
    int i = 0;
    //loop through the size of the image
    for (int y = ystart; y < (ystart + height); y++) {
        for (int x = xstart; x < (xstart + width); x++) {
            pixel -> color = alienPtr[i];
            pixel -> x = x;
            pixel -> y = y;

            drawPixel(pixel);
            i++;
        }
    }
}
