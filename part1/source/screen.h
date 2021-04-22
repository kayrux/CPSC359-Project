#ifndef screen
#define screen

typedef struct {
	int color;
	int x, y;
} Pixel;
struct fbs framebufferstruct;
void drawFrog(int xCellOff, int yCellOff, char *fBuffer);
//void drawFrog(int xCellOff, int yCellOff);
void drawCar1(int xCellOff, int yCellOff, int xOffset, int xStart, char *fBuffer, int id);
void drawPixel(Pixel *pixel);
void writePixel(Pixel *pixel, char *fBuffer);
void clear();

void drawStart();
void winDraw();
void mainMenuDrawStart();
void mainMenuDrawExit();
void levelOneLoadDraw();
void levelOnePlayDraw(char *gameMap);
void levelTwoLoadDraw();
void levelTwoPlayDraw(char *gameMap);
void levelThreeLoadDraw();
void levelThreePlayDraw(char *gameMap);
void levelFourLoadDraw();
void levelFourPlayDraw(char *gameMap);
void coverFrogLives(char *fBuffer, int frogLives);
void coverTimeBar(char *fBuffer, int time);
void renderScreen(char *gameMap);
void restartGamePause(char *fBuffer);
void exitGamePause(char *fBuffer);
void drawEndGame(int flag);

#endif