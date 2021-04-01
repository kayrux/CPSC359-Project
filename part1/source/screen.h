#ifndef screen
#define screen

typedef struct {
	int color;
	int x, y;
} Pixel;
struct fbs framebufferstruct;
void draw(struct fbs f, int xCellOff, int yCellOff);
void drawPixel(Pixel *pixel);
void clear();

void drawStart();
void mainMenuDrawStart();
void mainMenuDrawExit();
void levelOneLoadDraw();
void levelOnePlayDraw();

#endif