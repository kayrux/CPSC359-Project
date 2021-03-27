//This project makes use of code from 359 lectures and tutorials.

#include <unistd.h>
#include <stdio.h>
#include <initGPIO.h>
#include <snes.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
//#define INP_GPIO(g) *(gpioPtr+((g)/10)) &= ~(7<<(((g)%10)*3))
//#define OUT_GPIO(g) *(gpioPtr+((g)/10)) |= (1<<(((g)%10)*3))
//#define SET_GPIO_ALT(g,a) *(gpioPtr+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define     CLK         11  //the clock line
#define     LAT         9   //the latch line
#define     DAT         10  //the data line

#define	GPLEV0	13          //read data line
#define	GPSET0	7           //write data line
#define GPCLR0	10          //clear data line


/*
* Initializes the given GPIO line based on the desired function
* @param lineNum: the GPIO line to be initialized.
* @param function: a value of 0 represents input, and 1 represents output.
* @return: none
*/
void init_GPIO(unsigned int *gpioPtr, int lineNum, int function) {
    if (function == 0) {
        INP_GPIO(gpioPtr, lineNum);
    } else if (function == 1) {
        OUT_GPIO(gpioPtr, lineNum);
    } else {
        printf("Invalid entry");
    }
}

//A structure containing variables which are shared between all threads
struct gameState {
	int run;
    int score;
    int lives;
    int win;
    int lose;
	int *buttons;
    int **gameMap;
	long time;
} g;

/*
* Initializes the game state.
* @param: none
* @return: none
*/
void initGameState() {
    g.win = 0;
    g.lose = 0;
    g.score = 0;
    g.lives = 4;
}

/*
* The game loop. Runs all the main processes.
* @param *p: a filler arguement
* @return: zero
*/
void *gameLoop(void *p) {
    initGameState();
    pthread_exit(NULL);
}

/*
* The input loop. Continuously updates the buttons the user has pressed.
* @param *p: a filler arguement
* @return: zero
*/
void *input(void *p) {
    g.buttons = malloc(16 * sizeof(int));
    for (int i = 0; i < 16; i ++) {
        g.buttons[i] = 1;
    }

    unsigned int *gpioPtr = getGPIOPtr();
	printf("pointer address: %p\n", gpioPtr);
    printf("Created by: Sherriff Kadiri and Surya Kusjanto\n");
    printf("Please press a button...\n");

    while(g.run) {
        read_SNES(gpioPtr, g.buttons);
        g.run = g.buttons[3];
    }
    pthread_exit(NULL);
}

/*
* Request the user input through text, initialize button array and run read_SNES.
* @param: none
* @return: zero
*/
int main() {
    pthread_t tidGameLoop;
    pthread_t tidInput;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
    g.run = 1;
	pthread_create(&tidGameLoop, &attr, gameLoop, NULL);
    pthread_create(&tidInput, &attr, input, NULL);
	pthread_join(tidGameLoop, NULL);
    pthread_join(tidInput, NULL);

    return 0;
}