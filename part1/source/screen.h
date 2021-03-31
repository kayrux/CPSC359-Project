#ifndef screen
#define screen

typedef struct {
	int color;
	int x, y;
} Pixel;
struct fbs framebufferstruct;
void draw(struct fbs f);
void drawPixel(Pixel *pixel);

#endif