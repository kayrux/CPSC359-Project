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
#include "YOUR_IMAGE.h"

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


/*
* Request the user input through text, initialize button array and run read_SNES.
* @param: none
* @return: zero
*/
int main() {
    int buttons[16];
    for (int i = 0; i < 16; i ++) {
        buttons[i] = 1;
    }

    unsigned int *gpioPtr = getGPIOPtr();
	printf("pointer address: %p\n", gpioPtr);
    printf("Created by: Sherriff Kadiri and Surya Kusjanto\n");
    printf("Please press a button...\n");

    /* initialize + get FBS */
	framebufferstruct = initFbInfo();
	
	short int *alienPtr=(short int *) test3.pixel_data;
	
	/* initialize a pixel */
	Pixel *pixel;
	float res = framebufferstruct.screenSize;
	float length = framebufferstruct.lineLength;
	float width = framebufferstruct.screenSize/framebufferstruct.lineLength;
	int offsetY = (width-720)/(2);
	int offsetX = (length-1280)/2;
	printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);
	pixel = malloc(sizeof(Pixel));
	int i=0;
	//unsigned int quarter,byte,word;
	for (int y = offsetY; y < 720 + offsetY; y++)//30 is the image height
	{
		for (int x = offsetX; x < 1280 + offsetX; x++) // 30 is image width
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

    while(1) {
        read_SNES(gpioPtr, buttons);
    }
    return 0;
}