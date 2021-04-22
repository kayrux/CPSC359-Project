#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

#define NUM_OBJECTS 19
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
    int level;
    int moves;
    int win;
    int lose;
    int next;
	int *buttons;
    int *buttonsPressed;
    struct object *objects;
    int **gameMap;
	long time;
    long sTime;
    char* fBuffer;
};

struct object initObject() {
    struct object o;
    int dir = rand() % 2;
    int speed = rand() % 11 + 5;
    int ran = rand() % 5 + 1;
    if(dir%2 == 0) {
        while (ran == 3 || ran == 4) {ran = rand() % 5 + 1;}
    } else {
        while (ran == 1 || ran == 2 || ran == 5) {ran = rand() % 5 + 1;}
    }
    
    o.collidable = 1;           // 0 = not collidable. 1 = collidable 
    o.xStart = 0;               // Used for objects partway through the screen
    o.xCellOff = 0;             // X cell position of object
    o.yCellOff = 0;             // Y Cell position of object
    o.xOffset = 0;              // X pixel position of object
    o.yOffset = 0;              // Y pixel position of object
    o.width = X_CELL_PIXEL_SCALE;                // Width of object
    o.height = Y_CELL_PIXEL_SCALE;               // Height of object
    o.platform = 0;             // 0 = not a platform. 1 = platform
    o.active = 0;               // 0 = not active. 1 = active
    o.id = ran;                   // [frog, Car3RightBaseClear]
    o.direction = dir;            // 0 = left. 1 = right. 2 = up. 3 = down.
    o.speed = speed;                // Speed of the object

    if (o.id == 5) o.width = X_CELL_PIXEL_SCALE * 2;

    return o;
}

struct object initFrog() {
    struct object o;
    o.collidable = 1;                               // 0 = not collidable. 1 = collidable 
    o.xStart = 0;                                   // Used for objects partway through the screen
    o.xCellOff = 19;                                // X cell position of object
    o.yCellOff = 19;                                // Y Cell position of object
    o.xOffset = o.xCellOff * X_CELL_PIXEL_SCALE;    // X pixel position of object
    o.yOffset = o.xCellOff * Y_CELL_PIXEL_SCALE;    // Y pixel position of object
    o.width = 32;                                   // Width of object
    o.height = 32;                                  // Height of object
    o.platform = 0;                                 // 0 = not a platform. 1 = platform
    o.active = 1;                                   // 0 = not active. 1 = active
    o.id = 0;                                       // [frog, Car3RightBaseClear]
    o.direction = 0;                                // 0 = left. 1 = right. 2 = up. 3 = down.
    o.speed = 3;                                    // Speed of the object

    return o;
}

void updateLocation(struct object *o);

/*
* Resets the frogs location to the bottom center of the screen.
* @param frog: The frog object.
* @return: none.
*/
void resetFrogLocation(struct object *frog) {
    frog->xCellOff = 19;
    frog->yCellOff = 19;
    frog->xOffset = frog->xCellOff * X_CELL_PIXEL_SCALE;
    frog->yOffset = frog->xCellOff * Y_CELL_PIXEL_SCALE;
}

/*
* Updates the frog's position based on the arrow buttons.
* @param buttonPress: The int corresponding to the button that was pressed.
* @param *g: The current gameState.
* @return: none
*/
void updateFrogLocation(int buttonPress, struct gameState *g) {
    int moveMade = 0;
    switch (buttonPress) {
        case 0:     //UP
            if (g->objects[0].yCellOff >= 0) {
                g->objects[0].yCellOff -= 1;
                g->objects[0].yOffset -= Y_CELL_PIXEL_SCALE;
            }
            moveMade = 1;
            break;
        case 1:     //DOWN
            if ((g->objects[0].yCellOff + 1) < GAME_GRID_HEIGHT + 1) {
                g->objects[0].yCellOff += 1;
                g->objects[0].yOffset += Y_CELL_PIXEL_SCALE;
            }
            moveMade = 1;
            break;
        case 2:     //LEFT
            g->objects[0].xCellOff -= 1;
            g->objects[0].xOffset -= X_CELL_PIXEL_SCALE;
            if (g->objects[0].xOffset < 0) {
                g->objects[0].xOffset = 0;
                g->objects[0].xCellOff = 0;
            }
            moveMade = 1;
            break;
        case 3:     //RIGHT
            g->objects[0].xOffset += X_CELL_PIXEL_SCALE;
            if (g->objects[0].xOffset > SCREEN_WIDTH - X_CELL_PIXEL_SCALE) g->objects[0].xOffset = SCREEN_WIDTH - X_CELL_PIXEL_SCALE;
            moveMade = 1;
            break;
    }
    if (g->objects[0].yCellOff == -1) {
        g->level++;
        g->next = 1;
        resetFrogLocation(&g->objects[0]);
    }
    if (g->objects[0].yCellOff == 20 && g->level > 1) {
        g->level--;
        g->next = 1;
        g->objects[0].yCellOff = 0;
        g->objects[0].xCellOff = 19;
    }
    if (moveMade) {
        g->moves -= 1;
    }
}

/* Collision detection modified from https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
* Checks for a collision between the first object and the second.
* @param *o: The first object.
* @param *frog: The second object.
* @return: 1 if there is a collision. 0 if there is no collision.
*/
int checkCollision(struct object *o, struct object *frog) {
    if ((o->xOffset < frog->xOffset + frog->width) &&
        (o->xOffset + o->width > frog->xOffset)) {
            resetFrogLocation(frog);
            printf("Collision! Object: (%d, %d), Frog(%d, %d)\n", o->xOffset, o->yOffset, frog->xOffset, frog->yOffset);
            return 1;
    }
    return 0;
}

void frogOnPlatform(struct object *o, struct object *frog) {
    if ((o->xOffset + (o->width / 2) < frog->xOffset + frog->width) &&
        ((o->xOffset + o-> width) - (o->width / 4) > frog->xOffset)) {
        int frogOffset = o->speed;
        if (o->direction == 0) frogOffset = frogOffset * -1;
        frog->xOffset += frogOffset;
        if (frog->xOffset < 0) frog->xOffset = 0;  
        if (frog->xOffset > SCREEN_WIDTH - X_CELL_PIXEL_SCALE) frog->xOffset = SCREEN_WIDTH - X_CELL_PIXEL_SCALE; 
    }

}

int updateObjects(struct gameState *g) {
    for (int i = 1; i < NUM_OBJECTS; i++) {
        if (g->objects[i].active == 1) {            // Updates the object if it is active
            updateLocation(&g->objects[i]);
            if ((g->objects[i].platform) && (g->objects[i].yOffset == g->objects[0].yOffset)) {      // Checks collidable objects for a collision
                frogOnPlatform(&g->objects[i], &g->objects[0]);
            }
            if ((g->objects[i].collidable == 1) && (g->objects[i].yOffset == g->objects[0].yOffset)) {      // Checks collidable objects for a collision
                if (checkCollision(&g->objects[i], &g->objects[0]) == 1) {
                    return 1;
                }
            }
        }  
    }
    return 0;
}

/* 
* Updates the location of the given object based on direction, current location, and speed.
* @param *o: The object to update.
* @return: none.
*/
void updateLocation(struct object *o) {
    if (o->direction == 0) {
        o->xOffset -= o->speed;
        if (o->xOffset + 4 < 0) {
            o->speed = rand() % 11 + 5;
            o->xOffset = SCREEN_WIDTH;
        }
    } else {
        o->xOffset += o->speed;
        if (o->xOffset > SCREEN_WIDTH) {
            o->speed = rand() % 11 + 5;
            o->xOffset = 0;
        }
    }
    o->xCellOff = o->xOffset / X_CELL_PIXEL_SCALE;
}



void setObjects(int level, struct gameState *g) {
    if (level == 1) {
        for (int i = 1; i < NUM_OBJECTS; i++) {
            if(g->objects[i].id > 5) {
                g->objects[i].id = g->objects[i].id - 5;
            }
            g->objects[i].active = 1;
            g->objects[i].xOffset = 0;
            g->objects[i].xCellOff = 0;
            if ((g->objects[i].direction%2) == 0) {
                g->objects[i].xOffset = SCREEN_WIDTH;
                g->objects[i].xCellOff = GAME_GRID_WIDTH;
            }
            g->objects[i].yCellOff = i;
            g->objects[i].yOffset = i * Y_CELL_PIXEL_SCALE;
        }
    }

    if (level == 2) {
        for (int i = 1; i < NUM_OBJECTS; i++) {
            if(g->objects[i].id < 6) {
                g->objects[i].id = g->objects[i].id + 5;
            }
            if(i%2 == 1) {
                g->objects[i].active = 0;
            }
            g->objects[i].platform = 1;
            g->objects[i].active = 1;
            g->objects[i].xOffset = 0;
            g->objects[i].xCellOff = 0;
            if ((g->objects[i].direction%2) == 0) {
                g->objects[i].xOffset = SCREEN_WIDTH;
                g->objects[i].xCellOff = GAME_GRID_WIDTH;
            }
            g->objects[i].yCellOff = i;
            g->objects[i].yOffset = i * Y_CELL_PIXEL_SCALE;
        }
    }

    if (level == 3) {
        for (int i = 1; i < NUM_OBJECTS; i++) {
            if(g->objects[i].id > 6 && i <= 10) {
                g->objects[i].id = g->objects[i].id - 5;
                g->objects->platform = 1;
            } else {
                g->objects->platform = 0;
            }
            
            g->objects[i].active = 1;
            if(i == 10) {
                g->objects[i].active = 0;
            }
            g->objects[i].xOffset = 0;
            g->objects[i].xCellOff = 0;
            if ((g->objects[i].direction%2) == 0) {
                g->objects[i].xOffset = SCREEN_WIDTH;
                g->objects[i].xCellOff = GAME_GRID_WIDTH;
            }
            g->objects[i].yCellOff = i;
            g->objects[i].yOffset = i * Y_CELL_PIXEL_SCALE;
        }
    }

    if (level == 4) {
        for (int i = 1; i < NUM_OBJECTS; i++) {
            if(g->objects[i].id < 6) {
                g->objects[i].id = g->objects[i].id + 10;
            } else if(g->objects[i].id >= 6 && g->objects[i].id < 11) {
                g->objects[i].id = g->objects[i].id + 5;
            }
            g->objects[i]->platform = 0;
            g->objects[i].active = 1;
            g->objects[i].xOffset = 0;
            g->objects[i].xCellOff = 0;
            if ((g->objects[i].direction%2) == 0) {
                g->objects[i].xOffset = SCREEN_WIDTH;
                g->objects[i].xCellOff = GAME_GRID_WIDTH;
            }
            g->objects[i].yCellOff = i;
            g->objects[i].yOffset = i * Y_CELL_PIXEL_SCALE;
        }
    }
}