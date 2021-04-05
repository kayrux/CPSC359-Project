#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <framebuffer.h>
#include <res/alien.h>
#include <res/selectStart.h>
#include <res/selectExit.h>
#include <res/levelOneLoad.h>
#include <res/levelOnePlay.h>

#define X_CELL_PIXEL_SCALE 32
#define Y_CELL_PIXEL_SCALE 32

// RESOLUTION: 1280x720

/* Definitions */
typedef struct {
	int color;
	int x, y;
} Pixel;

struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);

void clear() {
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	int i=0;
	//unsigned int quarter,byte,word;
	for (int y = 0; y < 720; y++)//30 is the image height
	{
		for (int x = 0; x < 1280; x++) // 30 is image width
		{	
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


void draw(int xCellOff, int yCellOff) {
/* initialize + get FBS */
	//framebufferstruct = initFbInfo();
    //framebufferstruct = f;
	
	int *alienPtr=(int *) alienImage.image_pixels;
	
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	int i=0;
	//unsigned int quarter,byte,word;
	for (int y = 0; y < 30; y++)//30 is the image height
	{
		for (int x = 0; x < 30; x++) // 30 is image width
		{	
				pixel->color = alienPtr[i]; 
				pixel->x = x + (xCellOff * X_CELL_PIXEL_SCALE);
				pixel->y = y + (yCellOff * Y_CELL_PIXEL_SCALE);
	
				drawPixel(pixel);
				i++;
				
		}
	}
	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
	//munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
}

void drawStart() {
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
		for (int x = 0; x < 1280; x++) // 30 is image width
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
}


void mainMenuDrawStart() {
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
		for (int x = 0; x < 1280; x++) {		// 30 is image width
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
		for (int x = 0; x < 1280; x++) {		// 30 is image width
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
		for (int x = 0; x < 1280; x++) {		// 30 is image width
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

void levelOnePlayDraw() {
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
		for (int x = 0; x < 1280; x++) {		// 30 is image width
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

/* Draw a pixel */
void drawPixel(Pixel *pixel){
	long int location =(pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}