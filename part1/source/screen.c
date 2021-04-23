#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <framebuffer.h>
#include <string.h>

// res folder
#include <res/spaceOrb.h>
#include <res/spaceSnake.h>
#include <res/spaceCroc.h>
#include <res/spaceTurtle.h>
#include <res/spaceOtter.h>
#include <res/snakeImage.h>
#include <res/otterImage.h>
#include <res/crocImage.h>
#include <res/turtleLanding.h>
#include <res/turtleNotLanding.h>
#include <res/smallLog.h>
#include <res/mediumLog.h>
#include <res/largeLog.h>
#include <res/ultraLog.h>
#include <res/selectStart.h>
#include <res/selectExit.h>
#include <res/numberMap.h>
#include <res/LevelOne.h>
#include <res/LevelTwo.h>
#include <res/LevelThree.h>
#include <res/LevelFour.h>
#include <res/LevelOneIntro.h>
#include <res/LevelTwoIntro.h>
#include <res/LevelThreeIntro.h>
#include <res/LevelFourIntro.h>
#include <res/FrogUpBase.h>
#include <res/PauseRestart.h>
#include <res/PauseExit.h>
#include <res/WinnerScreen.h>
#include <res/GameOverScreen.h>
#include <res/Car1LeftBaseClear.h>
#include <res/Car2LeftBaseClear.h>
#include <res/Car3RightBaseClear.h>
#include <res/Car4RightBaseClear.h>
#include <res/Car5LeftBaseClear.h>
#include <res/Bonus.h>
#include <res/Flies1.h>
#include <res/Flies2.h>
#include <res/Flies3.h>
#include <res/Flies4.h>

#define X_CELL_PIXEL_SCALE 32
#define Y_CELL_PIXEL_SCALE 32
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
// RESOLUTION: 1280x720


// The coordinates of frog life images
#define FROG_LIFE_Y_COORD 670
#define FROG_LIFE_0_X_COORD 146
#define FROG_LIFE_1_X_COORD 114
#define FROG_LIFE_2_X_COORD 82
#define FROG_LIFE_3_X_COORD 50

// The coordinates for the time bar
#define TIME_BAR_Y_COORD 654
#define TIME_BAR_X_COORD 197
#define TIME_BAR_WIDTH 908
#define TIME_BAR_HEIGHT 36
#define TIME_LIMIT 180
#define TIME_SEGMENT (TIME_BAR_WIDTH / TIME_LIMIT)

// Display bar
#define DISPLAY_BAR_Y 670
#define TOP_LEFT_TIME_DIGIT_X 365
#define TOP_LEFT_SCORE_DIGIT_X 718
#define TOP_LEFT_MOVES_DIGIT_X 1168

/* Definitions */
typedef struct {
	int color;
	int x, y;
} Pixel;

/* Checks if the x-offset is out of the screen.
* @param xOffset: the x-offset.
* @return: 1 if the object is out of bounds. 0 otherwise.
*/
int outOfBounds(int xOffset) {
	if ((xOffset > SCREEN_WIDTH) || (xOffset < 0)) return 1;
	return 0;
}

struct fbs framebufferstruct;
void drawPixel(Pixel *pixel);
void writePixel(Pixel *pixel, char *fBuffer);

/* Clears the screen by filling it with black pixels.
* @param: none
* @return: none
*/
void clear() {
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	int i=0;
	//unsigned int quarter,byte,word;
	for (int y = 0; y < 720; y++) {
		for (int x = 0; x < 1280; x++) {	
				pixel->color = 0; 
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

/* Draws the frog onto the frame buffer.
* @param xOffset: the x-pixel coordinate of the frog.
* @param yOffset: the y-pixel coordinate of the frog.
* @param fBuffer: the intermediate frame buffer for the game.
* @return: none
*/
void drawFrog(int xOffset, int yCellOff, char *fBuffer) {
	short int *imagePtr=(short int *) ImageFrogUpBase.pixel_data;
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));

	int i=0;
	for (int y = 0; y < ImageFrogUpBase.height; y++) {
		for (int x = 0; x < ImageFrogUpBase.width; x++) {	
				pixel->color = imagePtr[i]; 
				pixel->x = x + xOffset;
				pixel->y = y + (yCellOff * Y_CELL_PIXEL_SCALE);
	
				writePixel(pixel, fBuffer);
				i++;	
		}
	}
	free(pixel);
	pixel = NULL;
}

/* Draws an object onto the frame buffer. The object drawn is based on id.
* @param xCellOff: the x-cell coordinate of the object.
* @param yCellOff: the y-cell coordinate of the object.
* @param xOffset: the x-pixel coordinate of the object.
* @param xStart: the number of x-pixel offset into the out of bounds area.
* @param fBuffer: the intermediate frame buffer for the game.
* @param id: the object id.
* @return: none
*/
void drawCar1(int xCellOff, int yCellOff, int xOffset, int xStart, char *fBuffer, int id) {
	short int *imagePtr=(short int *) ImageCar3RightBaseClear.pixel_data;
	int height = 32;
	int width = 32;
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
	} else if(id == 6) {
		imagePtr=(short int *) smallLogImage.pixel_data;
		height = smallLogImage.height;
		width = smallLogImage.width;
	} else if(id == 7) {
		imagePtr=(short int *) mediumLogImage.pixel_data;
		height = mediumLogImage.height;
		width = mediumLogImage.width;
	} else if(id == 8) {
		imagePtr=(short int *) largeLogImage.pixel_data;
		height = largeLogImage.height;
		width = largeLogImage.width;
	} else if(id == 9) {
		imagePtr=(short int *) ultraLogImage.pixel_data;
		height = ultraLogImage.height;
		width = ultraLogImage.width;
	} else if(id == 10) {
		imagePtr=(short int *) turtleLandingImage.pixel_data;
		height = turtleLandingImage.height;
		width = turtleLandingImage.width;
	} else if(id == 11) {
		imagePtr=(short int *) spaceTurtleImage.pixel_data;
		height = spaceTurtleImage.height;
		width = spaceTurtleImage.width;
	} else if(id == 12) {
		imagePtr=(short int *) spaceSnakeImage.pixel_data;
		height = spaceSnakeImage.height;
		width = spaceSnakeImage.width;
	} else if(id == 13) {
		imagePtr=(short int *) spaceOtterImage.pixel_data;
		height = spaceOtterImage.height;
		width = spaceOtterImage.width;
	} else if(id == 14) {
		imagePtr=(short int *) spaceCrocImage.pixel_data;
		height = spaceCrocImage.height;
		width = spaceCrocImage.width;
	} else if(id == 15) {
		imagePtr=(short int *) spaceOrbImage.pixel_data;
		height = spaceOrbImage.height;
		width = spaceOrbImage.width;
	}  else if (id == 16) {
		imagePtr=(short int *) fliesOneImage.pixel_data;
		height = fliesOneImage.height;
		width = fliesOneImage.width;
	}  else if (id == 17) {
		imagePtr=(short int *) fliesTwoImage.pixel_data;
		height = fliesTwoImage.height;
		width = fliesTwoImage.width;
	}  else if (id == 18) {
		imagePtr=(short int *) fliesThreeImage.pixel_data;
		height = fliesThreeImage.height;
		width = fliesThreeImage.width;
	}  else if (id == 19) {
		imagePtr=(short int *) fliesFourImage.pixel_data;
		height = fliesFourImage.height;
		width = fliesFourImage.width;
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

/* Draws the start screen
* @param: none
* @return: none
*/
void drawStart() {
	short int *imagePtr=(short int *) startImage.pixel_data;
	
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));

	int i=0;
	for (int y = 0; y < 720; y++) {
		for (int x = 0; x < 1280; x++) {	
				pixel->color = imagePtr[i]; 
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

/* Draws the menu screen with the "start" button highlighted.
* @param: none
* @return: none
*/
void mainMenuDrawStart() {
	short int *imagePtr=(short int *) startImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));

	int i=0;
	for (int y = 0; y < 720; y++) { 
		for (int x = 0; x < 1280; x++) {
			pixel->color = imagePtr[i]; 
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

/* Draws the menu screen with the "Exit" button highlighted.
* @param: none
* @return: none
*/
void mainMenuDrawExit() {
	short int *imagePtr=(short int *) exitImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));

	int i=0;
	for (int y = 0; y < 720; y++) { 
		for (int x = 0; x < 1280; x++) {
			pixel->color = imagePtr[i];
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

/* Draws either the "Game Over" or the "Game Won" screen based on the flag.
* @param flag: The flag is set to 0 for game over. 1 otherwise.
* @return: none
*/
void drawEndGame(int flag) {
	short int *imagePtr;
	if (flag == 0) imagePtr = (short int *) gameOverImage.pixel_data;
	else imagePtr = (short int *) winnerImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	int i=0;
	for (int y = 0; y < SCREEN_HEIGHT - 80; y++) { 
		for (int x = 0; x < SCREEN_WIDTH; x++) {
			pixel->color = imagePtr[i]; 
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

/* Draws the level one transition image onto the screen.
* @param: none
* @return: none
*/
void levelOneLoadDraw() {
	short int *imagePtr=(short int *) levelOneIntroImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	int i=0;
	for (int y = 0; y < 720; y++) { 
		for (int x = 0; x < 1280; x++) {
			pixel->color = imagePtr[i]; 
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

/* Draws the level one background image onto the screen.
* @param fBuffer: the intermediate frame buffer.
* @return: none
*/
void levelOnePlayDraw(char *fBuffer) {
	short int *imagePtr=(short int *) levelOneImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	int i=0;
	for (int y = 0; y < 720; y++) {
		for (int x = 0; x < 1280; x++) {
			pixel->color = imagePtr[i]; 
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

/* Draws the level two transition image onto the screen.
* @param: none
* @return: none
*/
void levelTwoLoadDraw() {
	short int *imagePtr=(short int *) levelTwoIntroImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	int i=0;
	for (int y = 0; y < 720; y++) { 
		for (int x = 0; x < 1280; x++) {
			pixel->color = imagePtr[i]; 
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

/* Draws the level two background image onto the screen.
* @param fBuffer: the intermediate frame buffer.
* @return: none
*/
void levelTwoPlayDraw(char *fBuffer) {
	short int *imagePtr=(short int *) levelTwoImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	int i=0;
	for (int y = 0; y < 720; y++) {
		for (int x = 0; x < 1280; x++) {
			pixel->color = imagePtr[i]; 
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

/* Draws the level three transition image onto the screen.
* @param: none
* @return: none
*/
void levelThreeLoadDraw() {
	short int *imagePtr=(short int *) levelThreeIntroImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	int i=0;
	for (int y = 0; y < 720; y++) { 
		for (int x = 0; x < 1280; x++) {
			pixel->color = imagePtr[i]; 
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

/* Draws the level three background image onto the screen.
* @param fBuffer: the intermediate frame buffer.
* @return: none
*/
void levelThreePlayDraw(char *fBuffer) {
	short int *imagePtr=(short int *) levelThreeImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	int i=0;
	for (int y = 0; y < 720; y++) {
		for (int x = 0; x < 1280; x++) {
			pixel->color = imagePtr[i]; 
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

/* Draws the level four transition image onto the screen.
* @param: none
* @return: none
*/
void levelFourLoadDraw() {
	short int *imagePtr=(short int *) levelFourIntroImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	int i=0;
	for (int y = 0; y < 720; y++) { 
		for (int x = 0; x < 1280; x++) {
			pixel->color = imagePtr[i]; 
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

/* Draws the level four background image onto the screen.
* @param fBuffer: the intermediate frame buffer.
* @return: none
*/
void levelFourPlayDraw(char *fBuffer) {
	short int *imagePtr=(short int *) levelFourImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	int i=0;
	for (int y = 0; y < 720; y++) {
		for (int x = 0; x < 1280; x++) {
			pixel->color = imagePtr[i]; 
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

/* void coverTimeBar(char *fBuffer, int time) {
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	if (time < 0) time = 0;
	int time_segment = (TIME_SEGMENT * time) + 1;
	int width = time_segment + TIME_BAR_X_COORD;
	int i=0;
	for (int y = 0; y < TIME_BAR_HEIGHT; y++) {
		for (int x = TIME_BAR_X_COORD; x < width; x++) {	
				pixel->color = 0; 
				pixel->x = x;
				pixel->y = y + TIME_BAR_Y_COORD;
	
				writePixel(pixel, fBuffer);
				i++;	
		}
	}
} */

/* Draws the pause menu with the restart button highlighted.
* @param fBuffer: the intermediate frame buffer.
* @return: none
*/
void restartGamePause(char *fBuffer) {
	short int *imagePtr=(short int *) pauseRestartImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	int i=0;
	for (int y = 160; y < 560; y++) {
		for (int x = 490; x < 790; x++) {
			pixel->color = imagePtr[i]; 
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

/* Draws the pause menu with the exit button highlighted.
* @param fBuffer: the intermediate frame buffer.
* @return: none
*/
void exitGamePause(char *fBuffer) {
	short int *imagePtr=(short int *) pauseExitImage.pixel_data;
	/* initialize a pixel */
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	
	int i=0;
	for (int y = 160; y < 560; y++) {
		for (int x = 490; x < 790; x++) {
			pixel->color = imagePtr[i]; 
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

/* Covers up the frog lives images based on number of remaining lives.
* @param fBuffer: the intermediate frame buffer.
* @param ffrogLives: the number of remaining lives left.
* @return: none
*/
void coverFrogLives(char *fBuffer, int frogLives) {
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	int width = 0;
	switch(frogLives) {
		case 3:
			width = FROG_LIFE_3_X_COORD + X_CELL_PIXEL_SCALE;
			break;
		case 2:
			width = FROG_LIFE_2_X_COORD + X_CELL_PIXEL_SCALE;
			break;
		case 1:
			width = FROG_LIFE_1_X_COORD + X_CELL_PIXEL_SCALE;
			break;
		case 0:
			width = FROG_LIFE_0_X_COORD + X_CELL_PIXEL_SCALE;
			break;
	}
	int i=0;
	for (int y = 0; y < Y_CELL_PIXEL_SCALE; y++) {
		for (int x = 0; x <  width; x++) {
				pixel->color = 0; 
				pixel->x = x;
				pixel->y = y + FROG_LIFE_Y_COORD;
				writePixel(pixel, fBuffer);
				i++;	
		}
	}
}

/* Draws a digit onto the frame buffer.
* Colour id: Yellow = 0, Blue = 1, Red = 2
* @param xOffset: the x-pixel coordinate of the digit
* @param yOffset: the y-pixel coordinate of the digit
* @param n: the digit to draw.
* @param colour: the id of the colour to draw.
* @param fBuffer: the intermediate frame buffer.
* @return: none
*/
void drawDigit(int xOffset, int yOffset, int n, int colour, char *fBuffer) {
	short int *imagePtr=(short int *) numberMapImage.pixel_data;
	Pixel *pixel;
	pixel = malloc(sizeof(Pixel));
	int numCol = 10 * X_CELL_PIXEL_SCALE;
	int row = 0;
	int col = 0;

	int i= 0;
	for (int y = 0; y < Y_CELL_PIXEL_SCALE; y++) {
		row = colour * Y_CELL_PIXEL_SCALE + y;
		for (int x = 0; x < X_CELL_PIXEL_SCALE; x++) {
			col = n * X_CELL_PIXEL_SCALE + x;
			i = row * numCol + col;
			pixel->color = imagePtr[i];
			pixel->x = x + xOffset;
			pixel->y = y + yOffset;

			writePixel(pixel, fBuffer);
			i++;	
		}
	}
	free(pixel);
	pixel = NULL;
}

/* Gets the digits of a given number and stores them in reverse order into an array.
* @param number: the number to get the digits from.
* @param *digits: the int array which stores the digits.
* @return: none
*/
void getDigits(int number, int *digits) {
	// Stores digits with the one's unit at index 0.
	for (int i = 0; i < 5; i ++) {
		digits[i] = number % 10;
		number = number / 10;
	}
}

/* Draws one of time, score or moves onto the frame buffer based on
* Display id: Time = 0, Score = 1, Moves = 2
* @param displayId: the id of the desired display drawn. 
* @param number: the score, time or moves left.
* @param fBuffer: the intermediate frame buffer.
* @return: none
*/
void drawDisplay(int displayId, int number, char *fBuffer) {
	int digits[5];
	int cellOffset;
	getDigits(number, digits);
	switch (displayId) {
		case 0:
			cellOffset = 2;
			for (int i = 0; i < 3; i ++) {
				drawDigit(TOP_LEFT_TIME_DIGIT_X + (cellOffset * X_CELL_PIXEL_SCALE), DISPLAY_BAR_Y, digits[i], displayId, fBuffer);
				cellOffset --;
			}
			break;
		case 1:
			cellOffset = 4;
			for (int i = 0; i < 5; i ++) {
				drawDigit(TOP_LEFT_SCORE_DIGIT_X + (cellOffset * X_CELL_PIXEL_SCALE), DISPLAY_BAR_Y, digits[i], displayId, fBuffer);
				cellOffset --;
			}
			break;
		case 2:
			cellOffset = 1;
			for (int i = 0; i < 3; i ++) {
				drawDigit(TOP_LEFT_MOVES_DIGIT_X + (cellOffset * X_CELL_PIXEL_SCALE), DISPLAY_BAR_Y, digits[i], displayId, fBuffer);
				cellOffset --;
			}
			break;
	}
}

/* Writes a pixel onto the intermediate frame buffer.
* @param *pixel: a pointer to the pixel. 
* @param fBuffer: the intermediate frame buffer.
* @return: none
*/
void writePixel(Pixel *pixel, char *fBuffer) {
	long int location =(pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(fBuffer + location)) = pixel->color;
}

/* Draws a pixel onto the screen.
* @param *pixel: a pointer to the pixel. 
* @return: none
*/
void drawPixel(Pixel *pixel) {
	long int location =(pixel->x +framebufferstruct.xOff) * (framebufferstruct.bits/8) +
                       (pixel->y+framebufferstruct.yOff) * framebufferstruct.lineLength;
	*((unsigned short int*)(framebufferstruct.fptr + location)) = pixel->color;
}

/* Copies the frame buffer onto the screen.
* @param fBuffer: the intermediate frame buffer.
* @return: none
*/
void renderScreen(char *fBuffer) {
	memcpy(framebufferstruct.fptr, fBuffer, 1280 * 720 * 2);
}
