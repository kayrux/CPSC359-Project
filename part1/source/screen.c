#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <framebuffer.h>
#include <string.h>

// res folder
#include <res/selectStart.h>
#include <res/selectExit.h>
#include <res/levelOneLoad.h>
#include <res/levelOnePlay.h>
#include <res/FrogUpBase.h>
#include <res/PauseRestart.h>
#include <res/PauseExit.h>
#include <res/Car1LeftBaseClear.h>
#include <res/Car2LeftBaseClear.h>
#include <res/Car3RightBaseClear.h>
#include <res/Car4RightBaseClear.h>
#include <res/Car5LeftBaseClear.h>

#define X_CELL_PIXEL_SCALE 32
#define Y_CELL_PIXEL_SCALE 32
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
// RESOLUTION: 1280x720

/* Definitions */
typedef struct {
	int color;
	int x, y;
} Pixel;


int outOfBounds(int xOffset) {
	if ((xOffset > SCREEN_WIDTH) || (xOffset < 0)) return 1;
	return 0;
}

struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);
void writePixel(Pixel *pixel, char *fBuffer);

void clear() {
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	int i=0;
	//unsigned int quarter,byte,word;
	for (int y = 0; y < 720; y++) {
		for (int x = 0; x < 1280; x++) {	
				pixel->color = 256; 
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;			
		}
	}
	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
}

void drawFrog(int xOffset, int yCellOff, char *fBuffer) {
	short int *alienPtr=(short int *) ImageFrogUpBase.pixel_data;
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));

	int i=0;
	for (int y = 0; y < ImageFrogUpBase.height; y++) {
		for (int x = 0; x < ImageFrogUpBase.width; x++) {	
				pixel->color = alienPtr[i]; 
				pixel->x = x + xOffset;
				pixel->y = y + (yCellOff * Y_CELL_PIXEL_SCALE);
	
				writePixel(pixel, fBuffer);
				i++;	
		}
	}
	free(pixel);
	pixel = NULL;
}

void drawCar1(int xCellOff, int yCellOff, int xOffset, int xStart, char *fBuffer, int id) {
	short int *imagePtr=(short int *) ImageCar3RightBaseClear.pixel_data;
	int height = ImageCar3RightBaseClear.height;
	int width = ImageCar3RightBaseClear.width;
	if(id == 1) {
		imagePtr=(short int *) ImageCar1LeftBaseClear.pixel_data;
		height = ImageCar1LeftBaseClear.height;
		width = ImageCar1LeftBaseClear.width;
	} else if(id == 2) {
		imagePtr=(short int *) ImageCar2LeftBaseClear.pixel_data;
		height = ImageCar2LeftBaseClear.height;
		width = ImageCar2LeftBaseClear.width;
	} else if(id == 3) {
		imagePtr=(short int *) ImageCar3RightBaseClear.pixel_data;
		height = ImageCar3RightBaseClear.height;
		width = ImageCar3RightBaseClear.width;
	} else if(id == 4) {
		imagePtr=(short int *) ImageCar4RightBaseClear.pixel_data;
		height = ImageCar4RightBaseClear.height;
		width = ImageCar4RightBaseClear.width;
	} else if(id == 5) {
		imagePtr=(short int *) ImageCar5LeftBaseClear.pixel_data;
		height = ImageCar5LeftBaseClear.height;
		width = ImageCar5LeftBaseClear.width;
	}
	 

	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	if (xOffset < 0) xOffset = 0;
	int i = 0;							// Accounts for images partway off the screen
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {	
			if ((outOfBounds(x + xOffset) != 1)) { 
				pixel->color = imagePtr[i];
				pixel->x = x + xOffset;
				pixel->y = y + (yCellOff * Y_CELL_PIXEL_SCALE);
				writePixel(pixel, fBuffer);
			}	
				
			i++;

		}
	}
	free(pixel);
	pixel = NULL;
}

void drawStart() {
	short int *alienPtr=(short int *) startImage.pixel_data;
	
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	//printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);

	int i=0;
	printf("Work 1\n");
	for (int y = 0; y < 720; y++) {
		for (int x = 0; x < 1280; x++) {	
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
}


void mainMenuDrawStart() {
	short int *alienPtr=(short int *) startImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	//printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);

	int i=0;
	for (int y = 0; y < 720; y++) { 
		for (int x = 0; x < 1280; x++) {
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
}

void mainMenuDrawExit() {
	short int *alienPtr=(short int *) exitImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	//printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);

	int i=0;
	for (int y = 0; y < 720; y++) { 
		for (int x = 0; x < 1280; x++) {
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
}

void levelOneLoadDraw() {
	short int *alienPtr=(short int *) levelOneImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	//printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);
	int i=0;
	for (int y = 0; y < 720; y++) { 
		for (int x = 0; x < 1280; x++) {
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
}

void levelOnePlayDraw(char *fBuffer) {
	short int *alienPtr=(short int *) levelOnePlayImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	//printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);
	
	int i=0;
	for (int y = 0; y < 720; y++) {
		for (int x = 0; x < 1280; x++) {
			pixel->color = alienPtr[i]; 
			pixel->x = x;
			pixel->y = y;
			writePixel(pixel, fBuffer);
			i++;
		}
	}
	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
}

void restartGamePause(char *fBuffer) {
	short int *alienPtr=(short int *) pauseRestartImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	//printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);
	
	int i=0;
	for (int y = 160; y < 560; y++) {
		for (int x = 490; x < 790; x++) {
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
}

void exitGamePause(char *fBuffer) {
	short int *alienPtr=(short int *) pauseExitImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	//printf("%f | %f | %f | %d | %d\n", res, length, width, offsetX, offsetY);
	
	int i=0;
	for (int y = 160; y < 560; y++) {
		for (int x = 490; x < 790; x++) {
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
}

void writePixel(Pixel *pixel, char *fBuffer) {
	long int location =(pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(fBuffer + location)) = pixel->color;
}

/* Draw a pixel */
void drawPixel(Pixel *pixel) {
	long int location =(pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}

void renderScreen(char *fBuffer) {
	memcpy(framebufferstruct.fptr, fBuffer, 1280 * 720 * 2);
}
