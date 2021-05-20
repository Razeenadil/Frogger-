/*
Project Part 1
By: William Ho & Muhammad Adil
UCID: 10173837 & 30069315

This part of the project is just setting on all the lines on the SNES and setting inupt/output macros 
that will be used for all pins during poject part 2. Right now the program tells the user to press a button,
user can keep pressign buttons and if they hit the start button the program is terminated.
*/

//import
#include <unistd.h>
#include <stdio.h>
#include "initGPIO.h"
#include <time.h>

//important macros
#define GPFSEL0 0
#define GPFSEL1 1
#define GPFSEL2 2
#define GPSET0 7 // 28/4
#define GPCLR0 10 // 40/4
#define GPLEV0 13 

//GPIO lines for the controller 
#define CLK 11
#define LAT 9
#define DAT 10

void initSNES(unsigned int *gpioPtr);
int Read_SNES(unsigned int *gpioPtr, int buttonArray[]);
void Wait(int time);
void Write_Latch(unsigned int *gpioPtr, int i);
void Write_Clock(unsigned int *gpioPtr, int i);
int Read_Data(unsigned int *gpioPtr);
void Print_Message(int v);


/*
This function clears the bits for any pin (pin). In turn clearing the bits (000) sets the pin function to input.
Parameters: @*gpioptr - Base GPIO address
            @pin - Desired pin number.
Return:     none
*/
void INP_GPIO(unsigned int *gpioptr, int pin) {
    *(gpioptr+((pin)/10)) &= ~(7<<(((pin)%10)*3));
}


/*
This function sets the bits for any pin (pin) to 001. Thus, the pin function is set to output.
Parameters: @*gpioptr - Base GPIO address
            @pin - Desired pin number.
Return:     none
*/
void OUT_GPIO(unsigned int *gpioptr, int pin) {
    *(gpioptr+((pin)/10)) |= (1<<(((pin)%10)*3));
}


/*
This is the main function where the need variables and functions are initalized. This function calls other functions. 
Also initalizes the controller.
Parameters: none
Return:     0
*/
int main()
{
    unsigned int *gpioPtr = getGPIOPtr();  // get gpio pointer
    int buttonArray[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  //initalizing array for buttons
    int num = 0;

    printf("Created by: Muhammad Adil and William Ho\n");

    initSNES(gpioPtr);  //initalizing SNES lines

    printf("Please press a button...\n");
    num = Read_SNES(gpioPtr, buttonArray);
    while (num == 18) {
        num = Read_SNES(gpioPtr, buttonArray);
    }
    return 0;
}


/*
This funtion initalizes the SNES lines.
Parameters: @*gpioptr - Base GPIO address
Return:     none
*/
void initSNES(unsigned int *gpioPtr) {

    //initalize clock line
    INP_GPIO(gpioPtr, CLK);
    INP_GPIO(gpioPtr, CLK);
    OUT_GPIO(gpioPtr, CLK);

    //initalize latch line
    INP_GPIO(gpioPtr, LAT);
    OUT_GPIO(gpioPtr, LAT);

    //initalize data line
    INP_GPIO(gpioPtr, DAT);
}

/*
This functions is like the main fucntion for the controller. When a button is pressed, this fucntion then 
reads the button press. This funtion checks to see if the user hit start.
Parameters: @*gpioptr - Base GPIO address
            @buttonArray[] - Array of 16 "1's" 0 means a button is pressed.
Return:     18
*/
int Read_SNES(unsigned int *gpioPtr, int buttonArray[]) {

    Write_Clock(gpioPtr, 1);    //setting pin 11
    Write_Latch(gpioPtr, 1);    //setting pin 9
    Wait(12);   //signal controller to sample buttons pressed
    Write_Latch(gpioPtr, 0);    //clearing pin 9
    int counter = 1; 

    while (counter < 18) {
        Wait(6);
        Write_Clock(gpioPtr, 0);    //clearing pin 11
        Wait(6);
        int v = Read_Data(gpioPtr);     //reading value of GPIO 10

        if (v == 0 && counter == 4) {   //checking to see if user pressed start 
            printf("\nProgram is terminating...\n");
            return counter;
        } else if (v == 0 && counter != 17) {   //user doesn't press start. Any other button is pressed.
            int n = checkArray(counter, buttonArray);   //calling checkArray to see which button exactly is pressed

            //a button is pressed
            if (n == 1) {  
                Print_Message(counter);     //get the actual name of the button
                Wait(200000);
                resetArray(buttonArray);
                printf("Please press a button...\n");
            }
            return 18;
        }
        Write_Clock(gpioPtr, 1);       //setting pin 11
        counter++;
    }
    return counter;
}

/*
This fucntion resets the array of buttons, so a button can be pressed repeatedly.
Parameters: @buttonArray[] - Array of 16 "1's" 0 means a button is pressed.
Return:     18
*/
void resetArray(int buttonArray[]){
    for(int i = 0; i < 16; i++){
        buttonArray[i] = 1;
    }

}


/*
This fucntion loops throught the array of buttons to see which button is pressed exactly. It also resets all
other buttons too.
Parameters: @buttonArray[] - Array of 16 "1's" 0 means a button is pressed.
            @i - indicated which button is passed through the function
Return:     1 - button is pressed
            0 - button is not pressed
*/
int checkArray (int i, int buttonArray[]) {
    if (buttonArray[i] == 1) {
        buttonArray[i] = 0;
        for (int j = 0; j < 16; j++) {
            if (j != i) {
                buttonArray[j] = 1;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

/*
This fucntion is used to make the program sleep for an x (time) amount of time using delayMicroseconds(). Note time is in microseconds.
Parameters: @time - time to wait for
Return:     none
*/
void Wait (int time) {
    delayMicroseconds(time); 
}

/*
This function writes a bit to to the GPIO latch line using GPCLR0 and GPSET0. If i is equal to 0 then write 0 to latch line. else write 1 to latch line.
Parameters: @*gpioPtr - Base GPIO address
            @i - the button, but an integer value 
Return:     none
*/
void Write_Latch (unsigned int *gpioPtr, int i) {
    if (i == 0) {
        gpioPtr[GPCLR0] = 1 << LAT;
    } else {
        gpioPtr[GPSET0] = 1 << LAT;
    }
}

/*
This function writes a bit to to the GPIO clock line using GPCLR0 and GPSET0. If i is equal to 0 then write 0 to clock line. else write 1 to clock line.
Parameters: @*gpioPtr - Base GPIO address
            @i - the button, but an integer value 
Return:     none
*/
void Write_Clock (unsigned int *gpioPtr, int i) {
    if (i == 0) {
        gpioPtr[GPCLR0] = 1 << CLK;
    } else {
        gpioPtr[GPSET0] = 1 << CLK;
    }
}

/*
This function reads a bit from the GPIO data line using GPLEV0. The data read is then stored as an interger and returned.
Parameters: @*gpioPtr - Base GPIO address
            @i - the button, but an integer value 
Return:     v - Bit read from data line
*/
int Read_Data (unsigned int *gpioPtr) {
    int v = (gpioPtr[GPLEV0] >> DAT) & 1;
    return v;
}

/*
This function takes an integer value of a button, and displays an apporaite message on which button is pressed.
Patameters: @i - the button, but an integer value 
Return:     none
*/
void Print_Message (int i) {
    switch (i) {
        case 1:
            printf("You have pressed B\n");
            break;
        case 2:
            printf("You have pressed Y \n");
            break;
        case 3:
            printf("You have pressed Select \n");
            break;
        case 4:
            printf("You have pressed Start \n");
            break;
        case 5:
            printf("You have pressed Joy-pad UP \n");
            break;
        case 6:
            printf("You have pressed Joy-pad DOWN \n");
            break;
        case 7:
            printf("You have pressed Joy-pad LEFT \n");
            break;
        case 8:
            printf("You have pressed Joy-pad RIGHT \n");
            break;
        case 9:
            printf("You have pressed A \n");
            break;
        case 10:
            printf("You have pressed X \n");
            break;
        case 11: 
            printf("You have pressed Left \n");
            break;
        case 12:
            printf("You have pressed Right \n");
            break;
    }
}
