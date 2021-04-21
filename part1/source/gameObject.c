#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define NUM_OBJECTS 14
#define GAME_GRID_WIDTH 40
#define GAME_GRID_HEIGHT 20
#define X_CELL_PIXEL_SCALE 32
#define Y_CELL_PIXEL_SCALE 32
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

struct object {
    int collidable;
    int xStart;
    int xCellOff;
    int yCellOff;
    int xOffset;
    int yOffset;
    int width;
    int height;
    int platform;
    int active;
    int id;
    int direction;
    int speed;
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

struct object initObject() {
    struct object o;
    o.collidable = 0;           // 0 = not collidable. 1 = collidable 
    o.xStart = 0;               // Used for objects partway through the screen
    o.xCellOff = 0;             // X cell position of object
    o.yCellOff = 0;             // Y Cell position of object
    o.xOffset = 0;              // X pixel position of object
    o.yOffset = 0;              // Y pixel position of object
    o.width = 32;                // Width of object
    o.height = 32;               // Height of object
    o.platform = 0;             // 0 = not a platform. 1 = platform
    o.active = 0;               // 0 = not active. 1 = active
    o.id = 0;                   // [frog, Car3RightBaseClear]
    o.direction = 0;            // 0 = left. 1 = right. 2 = up. 3 = down.
    o.speed = 3;                // Speed of the object
    return o;
}

struct object initFrog() {
    struct object o;
    o.collidable = 1;           // 0 = not collidable. 1 = collidable 
    o.xStart = 0;               // Used for objects partway through the screen
    o.xCellOff = 10;             // X cell position of object
    o.yCellOff = 19;             // Y Cell position of object
    o.xOffset = 320;              // X pixel position of object
    o.yOffset = 640;              // Y pixel position of object
    o.width = 32;                // Width of object
    o.height = 32;               // Height of object
    o.platform = 0;             // 0 = not a platform. 1 = platform
    o.active = 1;               // 0 = not active. 1 = active
    o.id = 0;                   // [frog, Car3RightBaseClear]
    o.direction = 0;            // 0 = left. 1 = right. 2 = up. 3 = down.
    o.speed = 3;                // Speed of the object
    return o;
}

void updateLocation(struct object *o);

/*
* Updates the frog's position based on the arrow buttons.
* @param: none
* @return: none
*/
void updateFrogLocation(int buttonPress, struct gameState *g) {
    switch (buttonPress) {
        case 0:     //UP
            if (g->objects[0].yCellOff > 0) {
                g->objects[0].yCellOff -= 1;
                g->objects[0].yOffset -= Y_CELL_PIXEL_SCALE;
            }
            break;
        case 1:     //DOWN
            if ((g->objects[0].yCellOff + 1) < GAME_GRID_HEIGHT) {
                g->objects[0].yCellOff += 1;
                g->objects[0].yOffset += Y_CELL_PIXEL_SCALE;
            }
            break;
        case 2:     //LEFT
            if (g->objects[0].xOffset > 0) {
                g->objects[0].xCellOff -= 1;
                g->objects[0].xOffset -= X_CELL_PIXEL_SCALE;
                if (g->objects[0].xOffset < 0) {
                    g->objects[0].xOffset = 0;
                    g->objects[0].xCellOff = 0;
                }
            }
            break;
        case 3:     //RIGHT
            if ((g->objects[0].xOffset) < SCREEN_WIDTH) {
                g->objects[0].xOffset += X_CELL_PIXEL_SCALE;
                if (g->objects[0].xOffset > SCREEN_WIDTH) g->objects[0].xOffset = SCREEN_WIDTH;
            }
            break;
    }
    /* if ((getButtonPress(4) == 0) && (g->objects[0].yCellOff > 0)) g.objects[0].yCellOff -= 1;                              // UP
    else if ((getButtonPress(5) == 0) && ((g->objects[0].yCellOff + 1) < GAME_GRID_HEIGHT)) g.objects[0].yCellOff += 1;    // DOWN
    else if ((getButtonPress(6) == 0) && (g->objects[0].xCellOff > 0)) g.objects[0].xCellOff -= 1;                         // LEFT
    else if ((getButtonPress(7) == 0) && ((g->objects[0].xCellOff + 1) < GAME_GRID_WIDTH)) g.objects[0].xCellOff += 1; */     // RIGHT
}

//https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
int checkCollision(struct object *o, struct object *frog) {
    if (o->xOffset < frog->xOffset + frog->width &&
        o->xOffset + o->width > frog->xOffset &&
        o->yCellOff < frog->yCellOff + frog->height &&
        o->yCellOff + o->height > frog->yCellOff) {
            return 1;
        }
        return 0;
}

void updateObjects(struct gameState *g) {
    for (int i = 1; i < NUM_OBJECTS; i++) {
        if (g->objects[i].active == 1) {
            if (g->objects[i].collidable == 1) {
                if (checkCollision(&g->objects[i], &g->objects[0]) == 1) {
                    printf("COLLISION!\n");
                    return;
                }
            }
            updateLocation(&g->objects[i]);
        }
        
    }
}

void updateLocation(struct object *o) {
    if (o->direction == 0) {
        o->xOffset -= o->speed;
        if (o->xOffset < 0) {
            o->xStart += o->speed;
            if (o->xStart >= 32) {
                o->xStart = 0;
                o->active = 0;
            }
        }
    } else {
        o->xOffset += o->speed;
        if (o->xOffset > SCREEN_WIDTH) {
            o->xOffset = SCREEN_WIDTH;
            o->active = 0;
        }
    }
}



void setObjects(int level, struct gameState *g) {
    if (level == 1) {
        for (int i = 1; i < NUM_OBJECTS; i++) {
            g->objects[i].active = 1;
            g->objects[i].direction = i%2;
            if ((i%2) == 0) g->objects[i].xOffset = SCREEN_WIDTH;
            g->objects[i].yCellOff = i + 2;
            g->objects[i].yOffset = (i + 2) * Y_CELL_PIXEL_SCALE;
        }
    }
}