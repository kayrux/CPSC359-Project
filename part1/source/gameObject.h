#ifndef gameObject
#define gameObject

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
	long time;
    char* gameMap;
};

//void renderObject(struct object *o);
struct object initObject();
struct object initFrog();
void updateFrogLocation(int buttonPress, struct gameState *g);
void updateObjects(struct gameState *g);
void setObjects(int level, struct gameState *g);
int checkCollision(struct object *o, struct object *frog);
//void updateLocation(struct object *o);

#endif