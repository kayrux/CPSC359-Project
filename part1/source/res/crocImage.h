/* GIMP RGBA C-Source image dump (crocImage.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[48 * 16 * 2 + 1];
} crocImage = {
  48, 16, 2,
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\310\302\310\302\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\310\302\002\210\310\302\310\302\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\310\302\310"
  "\302\310\302\310\302\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\310\302\310\302\310\302"
  "\310\302\033\306\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\310\302\310\302\310\302\033\306\000\000"
  "\033\306\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\310\302\000\000\000\000\000\000\000\000\310"
  "\302\000\000\000\000\000\000\000\000\033\306\033\306\310\302\310\302\310\302\310\302\000\000\033"
  "\306\000\000\000\000\000\000\000\000\000\000\000\000\000\000\310\302\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\310\302\000\000\000\000\000\000\000\000\310\302\310\302"
  "\310\302\000\000\000\000\310\302\033\306\310\302\000\000\000\000\000\000\033\306\033\306\310\302"
  "\310\302\310\302\033\306\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\310\302\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\310\302\000\000\000\000\000\000\310\302\000\000\000\000\310\302\310"
  "\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310"
  "\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310"
  "\302\310\302\000\000\033\306\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\310\302\310\302"
  "\000\000\000\000\000\000\310\202\000\000\000\000\310\302\310\302\310\302\310\302\310\302\310"
  "\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302\033\306"
  "\310\302\310\302\310\302\310\302\310\302\310\202\310\302\310\302\310\302"
  "\033\306\033\306\310\302\310\302\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\310\302\310\302\033\306\310\302\310\302\310\302\310\302\310\302"
  "\033\306\310\302\310\302\310\202\310\302\310\302\310\302\310\302\033\306\310"
  "\202\310\302\310\302\310\302\310\302\310\302\310\202\310\302\310\302\310"
  "\302\310\302\310\302\310\302\310\302\310\302\033\306\310\302\310\302\000\000\000"
  "\000\033\306\000\000\033\306\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\310\302\310"
  "\302\310\302\033\306\310\302\310\302\310\302\310\302\310\302\033\306\310\302"
  "\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302"
  "\310\302\310\302\033\306\310\302\310\302\310\302\310\302\310\302\310\202\310"
  "\302\310\302\310\302\310\302\310\302\310\302\033\306\310\302\310\302\000\000\033"
  "\306\000\000\033\306\000\000\000\000\033\306\033\306\000\000\000\000\000\000\000\000\000\000\000\000\310\302\310"
  "\202\310\302\310\302\310\302\310\302\310\302\310\302\033\306\310\202\310\302"
  "\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302"
  "\310\302\000\000\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310"
  "\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310\302\310"
  "\302\000\000\000\000\000\000\033\306\033\306\033\306\033\306\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\310\202\033\306\310\302\310\302\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\310\302\310\302\310\302\310\302\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\033\306"
  "\033\306\033\306\033\306\000\000\000\000\033\306\033\306\033\306\000\000\310\302\310\302\310"
  "\302\310\202\000\000\033\306\000\000\000\000\033\306\033\306\000\000\310\302\310\302\310\302"
  "\310\302\310\302\000\000\033\306\000\000\000\000\000\000\033\306\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\033\306\033\306\033\306\033\306\033\306\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\310\302\310\302\310\302\310\302\000\000\000\000\000\000\033\306\000\000\000"
  "\000\000\000\310\302\310\302\310\302\310\302\310\302\000\000\000\000\000\000\033\306\000\000\000\000"
  "\000\000\033\306\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000",
};

