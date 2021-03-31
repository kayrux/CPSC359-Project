#ifndef FRAMEBUFF
#define FRAMEBUFF

/* definitions */
struct fbs {
	char *fptr;		// framebuffer pointer
	int xOff; 					// x offset
	int yOff;					// x offset
	int bits;					// bits per pixel
	int lineLength;				// Line Length
	float screenSize;			// Screen Size
};
	
struct fbs initFbInfo(void);


#endif
