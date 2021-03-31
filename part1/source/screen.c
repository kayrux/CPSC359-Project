#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "framebuffer.h"
#include "res/alien.h"

/* Definitions */
typedef struct {
	int color;
	int x, y;
} Pixel;

struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);

void draw(struct fbs f) {
/* initialize + get FBS */
	//framebufferstruct = initFbInfo();
    framebufferstruct = f;
	
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
				pixel->x = x;
				pixel->y = y;
	
				drawPixel(pixel);
				i++;
				
		}
	}
	/* free pixel's allocated memory */
	free(pixel);
	pixel = NULL;
	//munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
}



/* Draw a pixel */
void drawPixel(Pixel *pixel){
	long int location =(pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}