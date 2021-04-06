#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define NUM_OBJECTS 16
#define GAME_GRID_WIDTH 40
#define GAME_GRID_HEIGHT 20
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

struct object {
    int collidable;
    int xStart;
    int xCellOff;
    int yCellOff;
    int xOffset;
    int yOffset;
    int platform;
    int active;
    int id;
    int direction;
};

//A structure containing variables which are shared between all threads
struct gameState {
	int run;
    int pause;
    int score;
    int lives;
    int win;
    int lose;
	int *buttons;
    int *buttonsPressed;
    struct object *objects;
    int **gameMap;
	long time;
    char* fBuffer;
};




void updateObjects(struct gameState *g) {
    for (int i = 0; i < NUM_OBJECTS; i++)
    {
        if (g->objects[i].active == 1)
        {
            if (g->objects[i].direction == 0)
            {
                g->objects[i].xOffset -= 1;
                if (g->objects[i].xOffset < 0)
                {
                    g->objects[i].xOffset = 0;
                    g->objects[i].xStart++;
                    if (g->objects[i].xStart == 32)
                    {
                        g->objects[i].xStart = 0;
                        g->objects[i].active = 0;
                    }
                }
            }
            else
            {
                g->objects[i].xOffset += 1;
                if (g->objects[i].xOffset > SCREEN_WIDTH)
                {
                    g->objects[i].xOffset = SCREEN_WIDTH;
                    g->objects[i].active = 0;
                }
            }
        }
    }
}

void updateLocation(struct object *o) {
    if (o->direction == 0) {
        o->xOffset -= 1;
        if (o->xOffset < 0) {
            o->xOffset = 0;
            o->xStart ++;
            if (o->xStart == 32) {
                o->xStart = 0;
                o->active = 0;
            }
        }
    } else {
        o->xOffset += 1;
        if (o->xOffset > SCREEN_WIDTH) {
            o->xOffset = SCREEN_WIDTH;
            o->active = 0;
        }
    }
}