#ifndef screen
#define screen

typedef struct {
	int color;
	int x, y;
} Pixel;
struct fbs framebufferstruct;
void drawFrog(int xCellOff, int yCellOff);
void drawCar1(int xCellOff, int yCellOff, int xOffset, int xStart);
void drawPixel(Pixel *pixel);
void clear();

void drawStart();
void mainMenuDrawStart();
void mainMenuDrawExit();
void levelOneLoadDraw();
void levelOnePlayDraw();

#endif