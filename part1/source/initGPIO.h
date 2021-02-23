#ifndef initGPIO
#define initGPIO

/*
* Maps the gpio pointer address.
* @return: the gpio pointer address.
*/
unsigned int *getGPIOPtr(void);

/*
* Initializes recieved parameter as input.
* @param gpioPtr: the base gpio address.
* @param g: the offset.
* @return: none.
*/
void INP_GPIO(unsigned int *gpioPtr, int g);

/*
* Initializes recieved parameter as output.
* @param gpioPtr: the base gpio address.
* @param g: the offset.
* @return: none.
*/
void OUT_GPIO(unsigned int *gpioPtr, int g);

/*
* Set one inputed gpio parameter to another inputed gpio paramater.
* @param gpioPtr: the base gpio address.
* @param g: the offset.
* @return: none.
void SET_GPIO_ALT(unsigned int *gpioPtr, int g, int a);
*/

#endif
