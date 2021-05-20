/* GIMP RGBA C-Source image dump (valuePack.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[32 * 32 * 2 + 1];
} valuePackIMG = {
  32, 32, 2,
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\000\000\000\000\377\377\377\377\377\377\377\377\377\377"
  "\377\377\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374"
  "\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374"
  "\300\374\000\000\000\000\377\377\377\377\377\377\377\377\000\000\000\000\377\377\377\377"
  "\377\377\377\377\377\377\377\377\300\374\300\374\300\374\300\374\300\374"
  "\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374"
  "\300\374\300\374\300\374\300\374\000\000\000\000\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\000\376\000\376\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\376\000\376\000\376\000\376\300\374\300"
  "\374\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\000\376"
  "\000\376\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\376\000\376\000\376\000\376\300\374\300\374\377\377\377\377\377\377\377\377\377"
  "\377\377\377\000\376\000\376\000\000\000\000\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\000\000\000\000\000\376\000\376\300\374\300\374\377\377\377\377\377"
  "\377\377\377\377\377\377\377\000\376\000\376\000\000\000\000\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\000\000\000\000\000\376\000\376\300\374\300\374\377"
  "\377\377\377\377\377\377\377\377\377\377\377\000\000\000\000\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\000\000"
  "\000\000\300\374\300\374\377\377\377\377\377\377\377\377\377\377\377\377\000\000"
  "\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\000\000\000\000\300\374\300\374\377\377\377\377\377\377\377"
  "\377\300\374\300\374\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377\377"
  "\377\377\377\377\377\000\000\000\000\300\374\300\374\377\377\377\377\377\377\377"
  "\377\300\374\300\374\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\000\000\000\000\000\000\000\000\000\000\000\000\377\377\377\377\377\377\377"
  "\377\377\377\377\377\000\000\000\000\300\374\300\374\377\377\377\377\377\377\377"
  "\377\300\374\300\374\000\376\000\376\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\000"
  "\300\374\300\374\377\377\377\377\377\377\377\377\300\374\300\374\000\376\000"
  "\376\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\377\377\377"
  "\377\377\377\377\377\377\377\377\377\000\000\000\000\300\374\300\374\377\377\377"
  "\377\377\377\377\377\300\374\300\374\000\376\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\376\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\000\000\000\000\000\376\000\376\300\374\300\374\377\377"
  "\377\377\377\377\377\377\300\374\300\374\000\376\000\376\000\376\000\376\000\376\000"
  "\376\000\376\000\376\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\000\000\000\000\000\376\000\376\300\374\300\374\377"
  "\377\377\377\377\377\377\377\300\374\300\374\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\376\000\376\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377"
  "\000\000\000\000\000\000\000\000\000\376\000\376\000\376\000\376\300\374\300\374\377\377\377\377"
  "\377\377\377\377\300\374\300\374\000\376\000\376\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000"
  "\000\000\000\000\376\000\376\000\376\000\376\300\374\300\374\377\377\377\377\377\377\377"
  "\377\300\374\300\374\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\000\000\000\000\000\000\000\000\000\000\000\000\376\000\376\000\376\000\376\000\376\000\376\000\376"
  "\000\376\300\374\300\374\377\377\377\377\377\377\377\377\300\374\300\374\000"
  "\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\000\000\000\000\000\000"
  "\000\000\000\000\000\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\300\374\300\374"
  "\377\377\377\377\377\377\377\377\300\374\300\374\000\376\000\376\000\376\000\376"
  "\000\376\000\376\000\376\000\376\000\000\000\000\377\377\377\377\377\377\377\377\377\377"
  "\377\377\000\000\000\000\000\376\000\376\000\376\000\376\000\376\000\376\300\374\300\374\377"
  "\377\377\377\377\377\377\377\300\374\300\374\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\376\000\376\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377"
  "\000\000\000\000\000\376\000\376\000\376\000\376\000\376\000\376\300\374\300\374\377\377\377"
  "\377\377\377\377\377\300\374\300\374\000\376\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\376\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\000\000"
  "\000\000\000\376\000\376\000\376\000\376\000\376\000\376\300\374\300\374\377\377\377\377"
  "\377\377\377\377\300\374\300\374\000\376\000\376\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\000\000\000\377\377\377\377\377\377\377\377\377\377\377\377\000\000\000\000\000"
  "\376\000\376\000\376\000\376\000\376\000\376\300\374\300\374\377\377\377\377\377\377"
  "\377\377\300\374\300\374\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\376\000\000\000\000\000\000\000\000\000\000\000\000\000\376\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\376\300\374\300\374\377\377\377\377\377\377\377\377\300\374\300"
  "\374\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\000\000\000"
  "\000\000\000\000\000\000\000\000\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\300\374"
  "\300\374\377\377\377\377\377\377\377\377\300\374\300\374\000\376\000\376\000\376"
  "\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\300\374\300\374\377"
  "\377\377\377\377\377\377\377\300\374\300\374\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376\000\376"
  "\000\376\000\376\000\376\000\376\000\376\000\376\000\376\300\374\300\374\377\377\377\377"
  "\377\377\377\377\000\000\000\000\300\374\300\374\300\374\300\374\300\374\300\374"
  "\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374"
  "\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374"
  "\000\000\000\000\377\377\377\377\377\377\377\377\000\000\000\000\300\374\300\374\300\374"
  "\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374"
  "\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374\300\374"
  "\300\374\300\374\300\374\000\000\000\000\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377\377"
  "\377\377\377\377\377\377\377\377\377\377\377\377\377\377",
};

