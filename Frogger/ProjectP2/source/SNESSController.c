#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "initGPIO.h"

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


void INP_GPIO(unsigned int *gpioptr, int pin) {
    *(gpioptr+((pin)/10)) &= ~(7<<(((pin)%10)*3));
}

void OUT_GPIO(unsigned int *gpioptr, int pin) {
    *(gpioptr+((pin)/10)) |= (1<<(((pin)%10)*3));
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

                if (v == 0 && counter != 17) {   //user doesn't press start. Any other button is pressed.
			int n = checkArray(counter, buttonArray);   //calling checkArray to see which button exactly is pressed

			//a button is pressed
			if (n == 1) {  
				if (counter == 6) {
					Wait(200000);
					resetArray(buttonArray);
					return 1;
				} else if (counter == 7) {
					Wait(200000);
					resetArray(buttonArray);
					return 2;
				} else if (counter == 8) {
					Wait(200000);
					resetArray(buttonArray);
					return 3;
				} else if (counter == 5) {
					Wait(200000);
					resetArray(buttonArray);
					return 4;
				}

                                if (counter == 9) {
                                    Wait(200000);
                                    resetArray(buttonArray);
                                    return 5;

                                }

                                if (counter == 4) {
                                    Wait(200000);
                                    resetArray(buttonArray);
                                    return 6;
                                }

				Wait(200000);
				resetArray(buttonArray);
			}
			return 0;
		}
		Write_Clock(gpioPtr, 1);       //setting pin 11
		counter++;
	}
	return 0;
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
   This function loops throught the array of buttons to see which button is pressed exactly. It also resets all
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

/*
 * This function checks if any button is pressed on the SNES controller
Patameters: @gpioPtr - base GPIO address
@buttonArray[] - Array of 16 "1's" 0 means a button is pressed.
Return:    1 if a button is pressed 
*/

int Read_SNES_anyInput(unsigned int *gpioPtr, int buttonArray[]) {

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

                if (v == 0 && counter != 17) {   //user doesn't press start. Any other button is pressed.
			int n = checkArray(counter, buttonArray);   //calling checkArray to see which button exactly is pressed

			//a button is pressed
			if (n == 1) {  
				
				Wait(200000);
				resetArray(buttonArray);
                                return 1;
				//printf("Please press a button...\n");
			}
			return 0;
		}
		Write_Clock(gpioPtr, 1);       //setting pin 11
		counter++;
	}
	return 0;
}


