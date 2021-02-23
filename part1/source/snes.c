#include <unistd.h>
#include <stdio.h>
#include <initGPIO.h>
#include <wiringPi.h>
#include <snes.h>

#define     CLK         11  //the clock line
#define     LAT         9   //the latch line
#define     DAT         10  //the data line

#define	GPLEV0	13          //read data line
#define	GPSET0	7           //write data line
#define GPCLR0	10          //clear data line

/*
* Reads button inputs and prints an appropriate output
* @param gpioPtr: the base gpio address.
* @param buttons: the integer array.
* @return: none.
*/
void read_SNES(unsigned int *gpioPtr, int* oldButtons) {
    int newButtons[16];

    init_SNES(gpioPtr);
    gpioPtr[GPSET0] = 1 << CLK;
    gpioPtr[GPSET0] = 1 << LAT;
    wait(12);
    gpioPtr[GPCLR0] = 1 << LAT;
    for(int i = 0; i < 16; i++) {
        wait(6);
        gpioPtr[GPCLR0] = 1 << CLK;
        wait(6);
        newButtons[i] = read_Data(gpioPtr);
        gpioPtr[GPSET0] = 1 << CLK;
    }
    print_message(newButtons, oldButtons);
}

/*
* Prints an appropriate button output
* @param newButtons: the integer array of new Button input.
* @param oldButtons: the integer array of old Button input.
* @return: none.
*/
void print_message(int* newButtons, int* oldButtons) {
    int btnPressed = 0;
    
    if((newButtons[0] == 0) && (oldButtons[0] != newButtons[0])) {
        oldButtons[0] = newButtons[0];
        btnPressed = 1;
        printf("Button B Pressed\n");
    } else if ((newButtons[0] == 1) && (oldButtons[0] != newButtons[0])) {
        oldButtons[0] = 1;
    }
    if((newButtons[1] == 0) && (oldButtons[1] != newButtons[1])) {
        oldButtons[1] = newButtons[1];
        btnPressed = 1;
        printf("Button Y Pressed\n");
    }  else if ((newButtons[1] == 1) && (oldButtons[1] != newButtons[1])) {
        oldButtons[1] = 1;
    }
    if((newButtons[2] == 0) && (oldButtons[2] != newButtons[2])) {
        oldButtons[2] = newButtons[2];
        btnPressed = 1;
        printf("Button SL Pressed\n");
    } else if ((newButtons[2] == 1) && (oldButtons[2] != newButtons[2])) {
        oldButtons[2] = 1;
    }
    if((newButtons[3] == 0) && (oldButtons[3] != newButtons[3])) {
        oldButtons[3] = newButtons[3];
        btnPressed = 1;
        printf("Button ST Pressed\n");
    } else if ((newButtons[3] == 1) && (oldButtons[3] != newButtons[3])) {
        oldButtons[3] = 1;
    }
    if((newButtons[4] == 0) && (oldButtons[4] != newButtons[4])) {
        oldButtons[4] = newButtons[4];
        btnPressed = 1;
        printf("Button UP Pressed\n");
    } else if ((newButtons[4] == 1) && (oldButtons[4] != newButtons[4])) {
        oldButtons[4] = 1;
    }
    if((newButtons[5] == 0) && (oldButtons[5] != newButtons[5])) {
        oldButtons[5] = newButtons[5];
        btnPressed = 1;
        printf("Button DOWN Pressed\n");
    } else if ((newButtons[5] == 1) && (oldButtons[5] != newButtons[5])) {
        oldButtons[5] = 1;
    }
    if((newButtons[6] == 0) && (oldButtons[6] != newButtons[6])) {
        oldButtons[6] = newButtons[6];
        btnPressed = 1;
        printf("Button LEFT Pressed\n");
    } else if ((newButtons[6] == 1) && (oldButtons[6] != newButtons[6])) {
        oldButtons[6] = 1;
    }
    if((newButtons[7] == 0) && (oldButtons[7] != newButtons[7])) {
        oldButtons[7] = newButtons[7];
        btnPressed = 1;
        printf("Button RIGHT Pressed\n");
    } else if ((newButtons[7] == 1) && (oldButtons[7] != newButtons[7])) {
        oldButtons[7] = 1;
    }
    if((newButtons[8] == 0) && (oldButtons[8] != newButtons[8])) {
        oldButtons[8] = newButtons[8];
        btnPressed = 1;
        printf("Button A Pressed\n");
    } else if ((newButtons[8] == 1) && (oldButtons[8] != newButtons[8])) {
        oldButtons[8] = 1;
    }
    if((newButtons[9] == 0) && (oldButtons[9] != newButtons[9])) {
        oldButtons[9] = newButtons[9];
        btnPressed = 1;
        printf("Button X Pressed\n");
    } else if ((newButtons[9] == 1) && (oldButtons[9] != newButtons[9])) {
        oldButtons[9] = 1;
    }
    if((newButtons[10] == 0) && (oldButtons[10] != newButtons[10])) {
        oldButtons[10] = newButtons[10];
        btnPressed = 1;
        printf("Button L Pressed\n");
    } else if ((newButtons[10] == 1) && (oldButtons[10] != newButtons[10])) {
        oldButtons[10] = 1;
    }
    if((newButtons[11] == 0) && (oldButtons[11] != newButtons[11])) {
        oldButtons[11] = newButtons[11];
        btnPressed = 1;
        printf("Button R Pressed\n");
    } else if ((newButtons[11] == 1) && (oldButtons[11] != newButtons[11])) {
        oldButtons[11] = 1;
    }
    if (btnPressed) printf("\nPlease press a button...\n\n");
}

/*
* Writes a bit to the latch line.
* @param gpioPtr: the base gpio address.
* @return: none.
*/
void write_Latch(unsigned int *gpioPtr) {
    gpioPtr[GPSET0] = 1 << LAT;
    gpioPtr[GPCLR0] = 1 << LAT;
}

/*
* Writes a bit to the clock line.
* @param gpioPtr: the base gpio address.
* @return: none.
*/
void write_Clock(unsigned int *gpioPtr) {
    gpioPtr[GPSET0] = 1 << CLK;
    gpioPtr[GPCLR0] = 1 << CLK;
}

/*
* Reads a bit from the data line.
* @param gpioPtr: the base gpio address.
* @return: returns the read bit.
*/
int read_Data(unsigned int *gpioPtr) {
    return (gpioPtr[GPLEV0] >> DAT) & 1; 
}

/*
* Delays the program by the specified amount of microseconds.
* @param waitTime: the amount of microseconds to wait.
* @return: none.
*/
void wait(int waitTime) {
    delayMicroseconds(waitTime);
}

/*
* Sets the clock line and latch line to output. Sets the data line to input.
* @param gpioPtr: the base gpio address.
* @return: none.
*/
void init_SNES(unsigned int *gpioPtr) {      
    OUT_GPIO(gpioPtr, CLK);            // CLK       
    OUT_GPIO(gpioPtr, LAT);            // LATCH    
    INP_GPIO(gpioPtr, DAT);            // DATA
}
