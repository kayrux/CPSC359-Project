/*
* Modified from http://cep.xray.aps.anl.gov/software/qt4-x11-4.2.2/qtopiacore-testingframebuffer.html
* for the purpose of assignment 4 CPSC359 P19
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include "framebuffer.h"

struct fbs initFbInfo(void)
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    long int screensize = 0;
    void *fbp = 0;

    // Open the file for reading and writing
    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1) {
        perror("Error: cannot open framebuffer device");
        exit(1);
    }
    printf("The framebuffer device was opened successfully.\n");

    // Get fixed screen information
    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1) {
        perror("Error reading fixed information");
        exit(2);
    }

    // Get variable screen information
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
        perror("Error reading variable information");
        exit(3);
    }

    

    // Figure out the size of the screen in bytes
    screensize = vinfo.xres_virtual * vinfo.yres_virtual * vinfo.bits_per_pixel / 8;
    printf("Hello: %d",vinfo.bits_per_pixel);

    // Map the device to memory
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    
    if ((int)fbp == -1) {
        perror("Error: failed to map framebuffer device to memory");
        exit(4);
    }
    
    printf("The framebuffer device was mapped to memory successfully.\n");
    printf("%dx%d, %dbpp\n", vinfo.xoffset, vinfo.yoffset, vinfo.bits_per_pixel);
    
    struct fbs result = {(char *)fbp, (int) vinfo.xoffset, (int) vinfo.yoffset,
        (int) vinfo.bits_per_pixel, (int) finfo.line_length,
        (float) screensize};
    
    return result;

}
