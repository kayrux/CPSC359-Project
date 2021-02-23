#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "initGPIO.h"

/*
* Initializes recieved parameter as input.
* @param gpioPtr: the base gpio address.
* @param g: the offset.
* @return: none.
*/
void INP_GPIO(unsigned int *gpioPtr, int g) {
	*(gpioPtr+((g)/10)) &= ~(7<<(((g)%10)*3));
}

/*
* Initializes recieved parameter as output.
* @param gpioPtr: the base gpio address.
* @param g: the offset.
* @return: none.
*/
void OUT_GPIO(unsigned int *gpioPtr, int g) {
	INP_GPIO(gpioPtr, g);
	*(gpioPtr+((g)/10)) |= (1<<(((g)%10)*3));
}

/*
* Set one inputed gpio parameter to another inputed gpio paramater.
* @param gpioPtr: the base gpio address.
* @param g: the offset.
* @return: none.

void SET_GPIO_ALT(unsigned int *gpioPtr, int g, int a) {
	*(gpioPtr+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3));
}
*/

/*
* Maps the gpio pointer address.
* @return: the gpio pointer address.
*/
unsigned int *getGPIOPtr(void)
{
	int fdgpio = open("/dev/gpiomem", O_RDWR);
	
	if (fdgpio <0) {
		printf("unable to open");
	}
	
	unsigned int *gpioPtr = (unsigned int *)mmap(0,4096,PROT_READ|PROT_WRITE,MAP_SHARED,fdgpio,0);
	
	return gpioPtr;
}
