//This project makes use of code from 359 lectures and tutorials.

#include <unistd.h>
#include <stdio.h>
#include <initGPIO.h>
#include <snes.h>
#include <screen.h>
#include <stdlib.h>
#include <sys/mman.h>
#include "framebuffer.h"
#include <pthread.h>
#include <time.h>
#include "framebuffer.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <gameObject.h>

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
//#define INP_GPIO(g) *(gpioPtr+((g)/10)) &= ~(7<<(((g)%10)*3))
//#define OUT_GPIO(g) *(gpioPtr+((g)/10)) |= (1<<(((g)%10)*3))
//#define SET_GPIO_ALT(g,a) *(gpioPtr+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define     CLK         11  //the clock line
#define     LAT         9   //the latch line
#define     DAT         10  //the data line

#define	GPLEV0	13          //read data line
#define	GPSET0	7           //write data line
#define GPCLR0	10          //clear data line


#define NUM_VALUE_PACKS 6
#define NUM_OBJECTS 19

#define GAME_GRID_WIDTH 40
#define GAME_GRID_HEIGHT 20
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define TIME_LIMIT 180
#define MOVE_LIMIT 200
#define SCORE_CONSTANT 20


/*
* Initializes the given GPIO line based on the desired function
* @param lineNum: the GPIO line to be initialized.
* @param function: a value of 0 represents input, and 1 represents output.
* @return: none
*/
void init_GPIO(unsigned int *gpioPtr, int lineNum, int function) {
    if (function == 0) {
        INP_GPIO(gpioPtr, lineNum);
    } else if (function == 1) {
        OUT_GPIO(gpioPtr, lineNum);
    }
}

struct gameState g;
void mainMenu();
void frogLifeLost();
void pauseMenu();

void initTime() {
    g.sTime = time(0);
    g.time = 0;
}

/*
* Checks whether the button at the given index was pressed.
* @param i: the index of the button.
* @return: returns 0 if the button was pressed. Returns 1 otherwise.
*/
int getButtonPress(int i) {
    if (g.buttonsPressed[i] == 0) {
        g.buttonsPressed[i] = 1;
        return 0;
    }
    return 1;
}

/*
* Initializes the game state.
* @param: none
* @return: none
*/
void initGameState() {
    g.pause = 0;
    g.win = 0;
    g.lose = 0;
    g.score = 0;
    g.bonusScore = 0;
    g.lives = 4;
    g.level = 1;
    g.moves = MOVE_LIMIT;
    initTime();
    g.buttons = malloc(16 * sizeof(int));
    g.buttonsPressed = malloc(16 * sizeof(int));
    g.objects = malloc(NUM_OBJECTS * sizeof(struct object));
    g.valuePacks = malloc(NUM_VALUE_PACKS * sizeof(struct object));
    for (int i = 0; i < 16; i ++) {
        g.buttons[i] = 1;
        g.buttonsPressed[i] = 1;
    }
    g.objects[0] = initFrog();
    for (int i = 1; i < NUM_OBJECTS; i++) {
        g.objects[i] = initObject();
    }
    for (int i = 0; i < NUM_VALUE_PACKS; i++) {
        g.valuePacks[i] = initValuePack(i);
    }
    g.gameMap = malloc(1280 * 720 * 2);
}

/*
* Set the game's state and changing values to the initial base state.
* @param: none
* @return: none
*/
void resetGameState() {
    for(int i = 1; i < NUM_OBJECTS; i++) {
        g.objects[i] = initObject();
    }
    for (int i = 0; i < NUM_VALUE_PACKS; i++) {
        g.valuePacks[i] = initValuePack(i);
    }
    setObjects(g.level, &g);
    g.objects[0] = initFrog();
    
    g.win = 0;
    g.lose = 0;
    g.score = 0;
    g.bonusScore = 0;
    g.lives = 4;
    g.level = 1;
    g.moves = MOVE_LIMIT;
    
    initTime();
}

/*
* Draws the game over screen and waits until an input is recieved before going to main menu.
* @param: none
* @return: none
*/
void gameOver() {
    int btnPressed = 0;
    g.lose = 1;
    g.pause = 1;
    drawEndGame(0);
    sleep(1);
    while (!btnPressed) {
        for (int i = 0; i < 16; i ++) {
            if (getButtonPress(i) == 0) btnPressed = 1;
        }
    }
}

/*
* Draws the winner screen and waits until an input is recieved before going to main menu.
* @param: none
* @return: none
*/
void gameWon() {
    int btnPressed = 0;
    g.win = 1;
    g.pause = 1;
    drawEndGame(1);
    sleep(1);
    while (!btnPressed) {
        for (int i = 0; i < 16; i ++) {
            if (getButtonPress(i) == 0) btnPressed = 1;
        }
    }
}

/*
* Checks the game state to confirm whether or not the game should end in a loss. (For cases like out of time
* or out of lives.)
* @param: none
* @return: none
*/
void checkLoseCondition() {
    if (g.moves <= 0 || g.lives <= 0 || g.score <= 0 || g.time >= TIME_LIMIT) gameOver();
}

/*
* Checks the game state to confirm whether or not the game should end in a win. (For cases like reaching the end.)
* @param: none
* @return: none
*/
void checkWinCondition() {
    if(g.level == 5) gameWon();
}

/*
* Calculate the current game score and store the result in the gamestate.
* @param: none
* @return: none
*/
void updateScore() {
     g.score = ((TIME_LIMIT - g.time) + g.moves + g.lives) * SCORE_CONSTANT;
     g.score += g.bonusScore;
}

/*
* Track the amount of time the player has remaining and store the changes as time passes.
* @param: none
* @return: none
*/
void updateTime() {
    if ((time(0) - g.sTime) >= 1) {
        g.time ++;
        g.sTime = time(0);
        for (int i = 0; i < NUM_VALUE_PACKS; i ++) {
            if (g.time == g.valuePacks[i].spawnTime) g.valuePacks[i].active = 1; // Spawns the value pack at specified time
        }
    }
}

/*
* Updates the frog's position based on the arrow buttons.
* @param: none
* @return: none
*/
void renderObject(struct object *o) {
    drawCar1(o->xCellOff, o->yCellOff, o->xOffset, o->xStart, g.gameMap, o->id);
}

/*
* Render a the screen image based on the current player level.
* Render the objects and valuepacks at a calculated position.
* @param: none
* @return: none
*/
void render() {
    if(g.level == 1) {
        if(g.next == 1) {
            sleep(1);
            levelOneLoadDraw();
            sleep(2);
            setObjects(g.level, &g);
            g.next = 0;
        }
        levelOnePlayDraw(g.gameMap);                                             // Level One Background
    }
    if(g.level == 2) {
        if(g.next == 1) {
            sleep(1);
            levelTwoLoadDraw();
            sleep(2);
            setObjects(g.level, &g);
            g.next = 0;
        }
        levelTwoPlayDraw(g.gameMap);                                             // Level One Background
    }
    if(g.level == 3) {
        if(g.next == 1) {
            sleep(1);
            levelThreeLoadDraw();
            sleep(2);
            setObjects(g.level, &g);
            g.next = 0;
        }
        levelThreePlayDraw(g.gameMap);                                             // Level One Background
    }
    if(g.level == 4) {
        if(g.next == 1) {
            sleep(1);
            levelFourLoadDraw();
            sleep(2);
            setObjects(g.level, &g);
            g.next = 0;
        }
        levelFourPlayDraw(g.gameMap);                                             // Level One Background
    }
    
    
    for (int i = 1; i < NUM_OBJECTS; i++) {
        if (g.objects[i].active == 1) {renderObject(&g.objects[i]);}  // render Object based on id
    }
    for (int i = 0; i < NUM_VALUE_PACKS; i++) {
        if (g.valuePacks[i].active == 1) {
            g.valuePacks[i].id = g.level + 15; // render Value Pack based on id
            renderObject(&g.valuePacks[i]);
        }  
    }
    drawFrog(g.objects[0].xOffset, g.objects[0].yCellOff, g.gameMap);         // Draw frog
    if (g.lives < 4) coverFrogLives(g.gameMap, g.lives);
    drawDisplay(0, TIME_LIMIT - g.time, g.gameMap);
    drawDisplay(1, g.score, g.gameMap);
    drawDisplay(2, g.moves, g.gameMap);
    renderScreen(g.gameMap);
}


/*
* Updates the frog's position based on the arrow buttons.
* @param: none
* @return: none
*/
void updateFrog() {
    if (getButtonPress(4) == 0) updateFrogLocation(0, &g);         // UP
    else if (getButtonPress(5) == 0) updateFrogLocation(1, &g);    // DOWN
    else if (getButtonPress(6) == 0) updateFrogLocation(2, &g);    // LEFT
    else if (getButtonPress(7) == 0) updateFrogLocation(3, &g);    // RIGHT
}

/*
* Reduces the remaining number of frog lives
* Decreases the frog lives by 1.
* @param: none
* @return: none
*/
void frogLifeLost() {
    g.lives -= 1;
}

/*
* Calls a multitude of update functions to update the time, frog, and checks the win and loss conditions.
* It also checks if the game should be paused.
* @param: none
* @return: none
*/
void update() {
    int collision = updateObjects(&g);
    if (collision) {
        frogLifeLost();
    }
    updateTime();
    updateFrog();
    updateScore();
    checkLoseCondition();
    checkWinCondition();
    if (getButtonPress(3) == 0) g.pause = 1 - g.pause;          //Pause/Resume game
}

/*
* The game loop. Runs all the main processes.
* @param *p: a filler arguement
* @return: none
*/
void *gameLoop(void *p) {
    while (g.run) {
        while(g.pause) if (getButtonPress(3) == 0) g.pause = 1 - g.pause;          //Pause/Resume game
        update();
		render();
        if (g.pause && !g.lose && !g.win) {                    // GAME OVER
            pauseMenu();
        }
        if (g.pause && (g.lose || g.win)) {                    // GAME OVER
            mainMenu();
        }
    }
    pthread_exit(NULL);
}

/*
* The input loop. Continuously updates the buttons the user has pressed.
* @param *p: a filler arguement
* @return: none
*/
void *input(void *p) {
    int oldButtons[16];
    for (int i = 0; i < 16; i ++) {
        oldButtons[i] = 1;
    }
    unsigned int *gpioPtr = getGPIOPtr();

    while(g.run == 1) {
        read_SNES(gpioPtr, g.buttons);
        for (int i = 0; i < 16; i ++) {
            if ((oldButtons[i] == 1) && (g.buttons[i] == 0)) { // Button pressed.
                g.buttonsPressed[i] = 0;
            } else if ((oldButtons[i] == 0) && (g.buttons[i] == 1)) { // Button released.
                g.buttonsPressed[i] = 1;
            }
            oldButtons[i] = g.buttons[i];
        }
        
    }
    munmap(framebufferstruct.fptr, framebufferstruct.screenSize);
    pthread_exit(NULL);
}

/*
* Draw the pause menu and check to see the user input to decide if the player should restart the game
* ,quit the game, or unpause the game.
* @param: none
* @return: none
*/
void pauseMenu() {
    restartGamePause(g.gameMap);
    int restartSelect = 1;                    // Begins with the start option selected.
    int exitSelect = 0;
    g.pause = 1;                            // Pause game
    while (g.pause) {
        if (getButtonPress(3) == 0) g.pause = 1 - g.pause;          //Pause/Resume game
        if ((getButtonPress(4) == 0) || (getButtonPress(5) == 0)) {   // 'Up' or 'Down' button pressed
            restartSelect = 1 - restartSelect;
            exitSelect = 1 - exitSelect;
            if (restartSelect == 1) {
				restartGamePause(g.gameMap);
			} else {
				exitGamePause(g.gameMap);
			}
            
        }
        if (getButtonPress(8) == 0) {           // 'A' button pressed
            if (restartSelect == 1) {             // Start game
                g.pause = 0;
				sleep(1);
				levelOneLoadDraw();
				sleep(2);
				levelOnePlayDraw(g.gameMap);
                // TEST CODE
                resetGameState();
                // END TEST
            } else {                            // Quit game
                clear();
                g.run = 0;
                g.pause = 0;
                
            }
        }  
    }
}

/*
* Draw the main menu and check to see the user input to decide if the player should start the game
* or quit the game.
* @param: none
* @return: none
*/
void mainMenu() {
    drawStart();
    int startSelect = 1;                    // Begins with the start option selected.
    int quitSelect = 0;
    g.pause = 1;                            // Pause game
    while (g.pause) {
        if ((getButtonPress(4) == 0) || (getButtonPress(5) == 0)) {   // 'Up' or 'Down' button pressed
            startSelect = 1 - startSelect;
            quitSelect = 1 - quitSelect;
            if (startSelect == 1) {
				mainMenuDrawStart();
			} else {
				mainMenuDrawExit();
			}
            
        }
        if (getButtonPress(8) == 0) {           // 'A' button pressed
            if (startSelect == 1) {             // Start game
                g.pause = 0;
				sleep(1);
				levelOneLoadDraw();
				sleep(2);
				levelOnePlayDraw(g.gameMap);
                // TEST CODE
                resetGameState();
                // END TEST
            } else {                            // Quit game
                clear();
                g.run = 0;
                g.pause = 0;
                
            }
        }  
    }
}


/*
* Initialize the game, create the threads, and run the game loop.
* @param: none
* @return: 0
*/
int main() {
    srand(time(0));
    initGameState();
    pthread_t tidGameLoop;
    pthread_t tidInput;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	/* initialize + get FBS */
	framebufferstruct = initFbInfo();
    pthread_create(&tidInput, &attr, input, NULL);          // Start input loop
    g.run = 1;
    mainMenu();                                             // Start Menu
	pthread_create(&tidGameLoop, &attr, gameLoop, NULL);    // Game loop starts after player selects 'Start Game' in the start menu
    
	pthread_join(tidGameLoop, NULL);
    pthread_join(tidInput, NULL);

    return 0;
}