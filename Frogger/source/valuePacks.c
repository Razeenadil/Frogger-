#include "drawFunctions.h"
#include "images/valuePack.c"

/* 
 * This function draws out the value pack image 
 * Returns nothing
 * */
void drawValuePack1() {
    short int *valuePack = (short int*) valuePackIMG.pixel_data;
    Pixel *pixel;
    pixel = malloc(sizeof(Pixel));

    drawImage(valuePack, pixel, 866, 267, 32, 32);
    

}

