#ifndef snes
#define snes

/*
* Writes a bit to the latch line.
* @param gpioPtr: the base gpio address.
* @return: none.
*/
void write_Latch(unsigned int *gpioPtr);

/*
* Writes a bit to the clock line.
* @param gpioPtr: the base gpio address.
* @return: none.
*/
void write_Clock(unsigned int *gpioPtr);

/*
* Reads a bit from the data line.
* @param gpioPtr: the base gpio address.
* @return: returns the read bit.
*/
int read_Data(unsigned int *gpioPtr);

/*
* Sets the clock line and latch line to output. Sets the data line to input.
* @param gpioPtr: the base gpio address.
* @return: none.
*/
void init_SNES(unsigned int *gpioPtr);

/*
* Delays the program by the specified amount of microseconds.
* @param waitTime: the amount of microseconds to wait.
* @return: none.
*/
void wait(int waitTime);

/*
* Reads button inputs and prints an appropriate output.
* @param gpioPtr: the base gpio address.
* @param buttons: the integer array.
* @return: none.
*/
void read_SNES(unsigned int *gpioPtr, int* buttons);

/* Checks if the button was pressed.
* @param newBtn: the new button press.
* @param oldBtn: the old button press.
* @return: Returns 1 if the button was pressed. Returns 0 otherwise.
*/
int buttonPressed(int newBtn, int oldBtn);

/*
* Compares newButtons with oldButtons and prints an appropriate button output.
* @param newButtons: the integer array of new Button input.
* @param oldButtons: the integer array of old Button input.
* @return: none
*/
void print_message(int* newButtons, int* oldButtons);


#endif