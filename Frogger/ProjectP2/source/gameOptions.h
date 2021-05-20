#ifndef gameOptions
#define gameOptions

/*
structure for the main game options, need to implement the logic.
*/
typedef struct {
    int score;  //player score
    int lives;  //player lives
    int time;   //time left
    int pauseButtonPressed; //pause button
    int movesLeft;  //number of moves left 
    int loseFlag;   //tiggered if player loses
    int value1;   //for the value pack
    int valueCars;  //value pack for cars
    int valueLogs;  //value pack for logs
} GameOptions;

#endif
