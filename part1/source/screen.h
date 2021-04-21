#ifndef screen
#define screen

typedef struct {
	int color;
	int x, y;
} Pixel;
struct fbs framebufferstruct;
void drawFrog(int xCellOff, int yCellOff, char *fBuffer);
//void drawFrog(int xCellOff, int yCellOff);
void drawCar1(int xCellOff, int yCellOff, int xOffset, int xStart, char *fBuffer);
void drawPixel(Pixel *pixel);
void writePixel(Pixel *pixel, char *fBuffer);
void clear();

void drawStart();
void mainMenuDrawStart();
void mainMenuDrawExit();
void levelOneLoadDraw();
void levelOnePlayDraw(char *gameMap);
void coverFrogLives(char *fBuffer, int frogLives);
void coverTimeBar(char *fBuffer, int time);
void renderScreen(char *gameMap);

#endif