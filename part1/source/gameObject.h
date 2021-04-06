#ifndef gameObject
#define gameObject

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

//void renderObject(struct object *o);
void updateObjects(struct gameState *g);
//void updateLocation(struct object *o);

#endif