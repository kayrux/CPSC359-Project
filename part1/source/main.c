//This project makes use of code from 359 lectures and tutorials.

#include <unistd.h>
#include <stdio.h>
#include <initGPIO.h>
#include <snes.h>
#include <screen.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "framebuffer.h"
#include <pthread.h>
#include <time.h>
#include "framebuffer.h"
#include <stdlib.h>
#include <sys/mman.h>


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

#define NUM_OBJECTS 20
#define GAME_CELL_WIDTH 20
#define GAME_CELL_HEIGHT 20
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

struct object {
    int collidable;
    int xCellOff;
    int yCellOff;
    int platform;
    int active;
    int id;
};

//A structure containing variables which are shared between all threads
struct gameState {
	int run;
    int pause;
    int score;
    int lives;
    int win;
    int lose;
	int *buttons;
    int *buttonsPressed;
    struct object *objects;
    int **gameMap;
	long time;
} g;

struct object initObject() {
    struct object o;
    o.collidable = 0;
    o.xCellOff = 0;
    o.yCellOff = 0;
    o.platform = 0;
    o.active = 0;
    o.id = 0;
    return o;
}
/*
* Initializes the game state.
* @param: none
* @return: none
*/
void initGameState() {
    g.pause = 0;
    g.win = 0;
    g.lose = 0;
    g.score = 0;
    g.lives = 4;
    g.buttons = malloc(16 * sizeof(int));
    g.buttonsPressed = malloc(16 * sizeof(int));
    g.objects = malloc(16 * sizeof(struct object));
    for (int i = 0; i < 16; i ++) {
        g.objects[i] = initObject();
        g.buttons[i] = 1;
        g.buttonsPressed[i] = 1;
    }
}


void render(struct fbs f) {
    levelOnePlayDraw();
    draw(f, g.objects[0].xCellOff, g.objects[0].yCellOff);      //draw frog
}

/*
* Checks whether the button at the given index was pressed.
* @param i: the index of the button.
* @return: returns 0 if the button was pressed. Returns 1 otherwise.
*/
int getButtonPress(int i) {
    if (g.buttonsPressed[i] == 0) {
        g.buttonsPressed[i] = 1;
        return 0;
    }
    return 1;
}

/*
* Updates the frog's position based on the arrow buttons.
* @param: none
* @return: none
*/
void updateFrog() {
    if (getButtonPress(4) == 0) g.objects[0].yCellOff -= 1;         // UP
    else if (getButtonPress(5) == 0) g.objects[0].yCellOff += 1;    // DOWN
    else if (getButtonPress(6) == 0) g.objects[0].xCellOff -= 1;    // LEFT
    else if (getButtonPress(7) == 0) g.objects[0].xCellOff += 1;    // RIGHT
}

/*
* The game loop. Runs all the main processes.
* @param *p: a filler arguement
* @return: zero
*/
void *gameLoop(void *p) {
    printf("Game start...\n");
    while (g.run == 1) {
        while(g.pause == 1);
        updateFrog();
		render(framebufferstruct);
    }
    pthread_exit(NULL);
}

/*
* The input loop. Continuously updates the buttons the user has pressed.
* @param *p: a filler arguement
* @return: zero
*/
void *input(void *p) {
    int oldButtons[16];
    for (int i = 0; i < 16; i ++) {
        oldButtons[i] = 1;
    }
    unsigned int *gpioPtr = getGPIOPtr();

    /* initialize + get FBS */
	framebufferstruct = initFbInfo();
	drawStart();
    while(g.run == 1) {
        read_SNES(gpioPtr, g.buttons);
        for (int i = 0; i < 16; i ++) {
            if ((oldButtons[i] == 1) && (g.buttons[i] == 0)) { // Button pressed.
                g.buttonsPressed[i] = 0;
            } else if ((oldButtons[i] == 0) && (g.buttons[i] == 1)) { // Button released.
                g.buttonsPressed[i] = 1;
            }
            oldButtons[i] = g.buttons[i];
        }
        //render(framebufferstruct);
        
    }
    munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
    pthread_exit(NULL);
}

void mainMenu() {
    int startSelect = 1;                    // Begins with the start option selected.
    int quitSelect = 0;
    g.pause = 1;                            // Pause game
    printf("Start: Selected\n");
    while (g.pause == 1) {
        if ((getButtonPress(4) == 0) || (getButtonPress(5) == 0)) {   // 'Up' or 'Down' button pressed
            startSelect = 1 - startSelect;
            quitSelect = 1 - quitSelect;
            if (startSelect == 1) {
				printf("Start Game: Selected\n");
				mainMenuDrawStart();
			} else {
				printf("Quit Game: Selected\n");
				mainMenuDrawExit();
			}
            
        }
        if (getButtonPress(8) == 0) {           // 'A' button pressed
            if (startSelect == 1) {             // Start game
                g.pause = 0;
                printf("Game Start!!!!!\n");
				sleep(1);
				levelOneLoadDraw();
				sleep(2);
				levelOnePlayDraw();
            } else {                            // Quit game
                printf("Game Quit!!!!!\n");
                g.run = 0;
                g.pause = 0;
            }
        }  
    }
}



/*
* Request the user input through text, initialize button array and run read_SNES.
* @param: none
* @return: zero
*/
int main() {
    initGameState();

    pthread_t tidGameLoop;
    pthread_t tidInput;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	
    pthread_create(&tidInput, &attr, input, NULL);          // Start input loop
    g.run = 1;
    mainMenu();                                             // Start Menu
	pthread_create(&tidGameLoop, &attr, gameLoop, NULL);    // Game loop starts after player selects 'Start Game' in the start menu
    
	pthread_join(tidGameLoop, NULL);
    pthread_join(tidInput, NULL);

    return 0;
}