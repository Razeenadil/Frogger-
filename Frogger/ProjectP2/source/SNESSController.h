#ifndef SNESSController
#define SNESSController

void initSNES(unsigned int *gpioPtr);
int Read_SNES(unsigned int *gpioPtr, int buttonArray[]);
int Read_SNES_anyInput(unsigned int *gpioPtr, int buttonArray[]);


void Wait(int time);
void Write_Latch(unsigned int *gpioPtr, int i);
void Write_Clock(unsigned int *gpioPtr, int i);
int Read_Data(unsigned int *gpioPtr);
void Print_Message(int v);

#endif
