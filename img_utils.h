/* 
    Struct storing image data
*/
typedef struct{
    int h, w, c; /* dimensions */
    unsigned char* img; /* pixel values */
} image;

#include <math.h>
#include "img_utils.c"

void read_img(char path[], image* img);

void write_img(char path[], image img);

unsigned char read_pixel(image* img, int x, int y);

void write_pixel(image* img, int x, int y, unsigned char val);