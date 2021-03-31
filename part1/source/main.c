//This project makes use of code from 359 lectures and tutorials.

#include <unistd.h>
#include <stdio.h>
#include <initGPIO.h>
#include <snes.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "framebuffer.h"
#include "alien.h"
#include "test.h"
#include "test3.h"
#include "selectStart.h"
#include "selectExit.h"
#include "levelOneLoad.h"
#include "levelOnePlay.h"
#include "YOUR_IMAGE.h"
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

/* Definitions */
typedef struct {
	short int color;
	int x, y;
} Pixel;

struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);

/* Draw a pixel */
void drawPixel(Pixel *pixel){
	long int location =(pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}

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
    int pause;
    int score;
    int lives;
    int win;
    int lose;
	int *buttons;
    int *buttonsPressed;
    int **gameMap;
	long time;
} g;

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
    for (int i = 0; i < 16; i ++) {
        g.buttons[i] = 1;
        g.buttonsPressed[i] = 1;
    }
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
* The game loop. Runs all the main processes.
* @param *p: a filler arguement
* @return: zero
*/
void *gameLoop(void *p) {
        while (g.run == 1) {
            while(g.pause == 1);

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
	/*printf("pointer address: %p\n", gpioPtr);
    printf("Created by: Sherriff Kadiri and Surya Kusjanto\n");
    printf("Please press a button...\n");*/

    /* initialize + get FBS */
	framebufferstruct = initFbInfo();
	
	short int *alienPtr=(short int *) startImage.pixel_data;
	
	/* initialize a pixel */
	Pixel *pixel;
	float res = framebufferstruct.screenSize;
	float length = framebufferstruct.lineLength;
	float width = framebufferstruct.screenSize/framebufferstruct.lineLength;
	int offsetY = (width-720)/2;
	int offsetX = (length-1280)/2;
	printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);
	pixel = malloc(sizeof(Pixel));
	int i=0;
	//unsigned int quarter,byte,word;
	for (int y = 0; y < 720; y++)//30 is the image height
	{
		for (int x = offsetX-1280; x < 1280; x++) // 30 is image width
		{	
				pixel->color = alienPtr[i]; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
		}
	}
	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);

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
    }
    pthread_exit(NULL);
}

void mainMenuDrawStart() {
	/* initialize + get FBS */
	framebufferstruct = initFbInfo();
	short int *alienPtr=(short int *) startImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	float res = framebufferstruct.screenSize;
	float length = framebufferstruct.lineLength;
	float width = framebufferstruct.screenSize/framebufferstruct.lineLength;
	int offsetY = (width-720)/2;
	int offsetX = (length-1280)/2;
	printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);
	pixel = malloc(sizeof(Pixel));
	int i=0;
	//unsigned int quarter,byte,word;
	for (int y = 0; y < 720; y++) {						//30 is the image height 
		for (int x = offsetX-1280; x < 1280; x++) {		// 30 is image width
			pixel->color = alienPtr[i]; 
			pixel->x = x;
			pixel->y = y;
			drawPixel(pixel);
			i++;
		}
	}
	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
}

void mainMenuDrawExit() {
	/* initialize + get FBS */
	framebufferstruct = initFbInfo();
	short int *alienPtr=(short int *) exitImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	float res = framebufferstruct.screenSize;
	float length = framebufferstruct.lineLength;
	float width = framebufferstruct.screenSize/framebufferstruct.lineLength;
	int offsetY = (width-720)/2;
	int offsetX = (length-1280)/2;
	printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);
	pixel = malloc(sizeof(Pixel));
	int i=0;
	//unsigned int quarter,byte,word;
	for (int y = 0; y < 720; y++) {						//30 is the image height 
		for (int x = offsetX-1280; x < 1280; x++) {		// 30 is image width
			pixel->color = alienPtr[i]; 
			pixel->x = x;
			pixel->y = y;
			drawPixel(pixel);
			i++;
		}
	}
	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
}

void levelOneLoadDraw() {
	/* initialize + get FBS */
	framebufferstruct = initFbInfo();
	short int *alienPtr=(short int *) levelOneImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	float res = framebufferstruct.screenSize;
	float length = framebufferstruct.lineLength;
	float width = framebufferstruct.screenSize/framebufferstruct.lineLength;
	int offsetY = (width-720)/2;
	int offsetX = (length-1280)/2;
	printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);
	pixel = malloc(sizeof(Pixel));
	int i=0;
	//unsigned int quarter,byte,word;
	for (int y = 0; y < 720; y++) {						//30 is the image height 
		for (int x = offsetX-1280; x < 1280; x++) {		// 30 is image width
			pixel->color = alienPtr[i]; 
			pixel->x = x;
			pixel->y = y;
			drawPixel(pixel);
			i++;
		}
	}
	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
}

void levelOnePlayDraw() {
	/* initialize + get FBS */
	framebufferstruct = initFbInfo();
	short int *alienPtr=(short int *) levelOnePlayImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	float res = framebufferstruct.screenSize;
	float length = framebufferstruct.lineLength;
	float width = framebufferstruct.screenSize/framebufferstruct.lineLength;
	int offsetY = (width-720)/2;
	int offsetX = (length-1280)/2;
	printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);
	pixel = malloc(sizeof(Pixel));
	int i=0;
	//unsigned int quarter,byte,word;
	for (int y = 0; y < 720; y++) {						//30 is the image height 
		for (int x = offsetX-1280; x < 1280; x++) {		// 30 is image width
			pixel->color = alienPtr[i]; 
			pixel->x = x;
			pixel->y = y;
			drawPixel(pixel);
			i++;
		}
	}
	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
	munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
}


void mainMenu() {
    int startSelect = 1;                    // Begins with the start option selected.
    int quitSelect = 0;
    g.pause = 1;                            // Pause game
    printf("Start: Selected\n");
    while (g.pause == 1) {
        if ((getButtonPress(11) == 0) || (getButtonPress(10) == 0)) {   // 'Up' or 'Down' button pressed
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
				sleep(2);
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