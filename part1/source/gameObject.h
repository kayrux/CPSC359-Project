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
    int spawnTime;
};

//A structure containing variables which are shared between all threads
struct gameState {
	int run;
    int pause;
    int score;
    int bonusScore;
    int lives;
    int level;
    int moves;
    int win;
    int lose;
    int next;
	int *buttons;
    int *buttonsPressed;
    struct object *objects;
    struct object *valuePacks;
	long time;
    long sTime;
    char* gameMap;
};

//void renderObject(struct object *o);
struct object initObject();
struct object initValuePack(int num);
struct object initFrog();
void updateFrogLocation(int buttonPress, struct gameState *g);
int updateObjects(struct gameState *g);
void setObjects(int level, struct gameState *g);
int checkCollision(struct object *o, struct object *frog);
void resetFrogLocation(struct object *frog);

//void updateLocation(struct object *o);

#endif