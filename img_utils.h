/* 
    Struct storing image data
*/
typedef struct{
    int h, w, c; /* dimensions */
    unsigned char* img; /* pixel values */
} image;

#include "img_utils.c"

/* 
char path[]: path to the image
image* img: pointer to an image struct to store the data
Only supports grayscale images
 */
void read_img(char path[], image* img);


/* 
char path[]: write path
image* img: an image struct to write
Only supports grayscale images
 */
void write_img(char path[], image img);

/* 
image* img: pointer to the img source to read data
int x, int y: coordinates
return: pixel value (0-255)
 */
unsigned char read_pixel(image* img, int x, int y);

/* 
image* img: pointer to the img to write data
int x, int y: coordinates
unsigned char val: value to store
 */
void write_pixel(image* img, int x, int y, unsigned char val);


/* 
pads an image with zeros
img = original img
p = pad size 
    suppose a 512x512 image, if p=2, nimg will be 516x516

returns a pointer to the padded image
 */
image* pad(image* img, int p);

/* 
free an image
 */
void free_img(image* img);


/* 
Allocates a new image with height h and width w
Don't forget to call free_img afterwards!
 */
image* new_img(int h, int w);
