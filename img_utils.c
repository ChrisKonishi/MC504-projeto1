#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"


/* 
char path[]: path to the image
image* img: pointer to an image struct to store the data
Only supports grayscale images
 */
void read_img(char path[], image* img){
    img->img = stbi_load(path, &img->w, &img->h, &img->c, 0);
    if (img->c > 0){
        printf("Only grayscale images allowed\n");
        exit(1);
    }
}

/* 
char path[]: write path
image* img: an image struct to write
Only supports grayscale images
 */
void write_img(char path[], image img){
    stbi_write_png(path, img.w, img.h, img.c, img.img, img.w*img.c);
}

/* 
image* img: pointer to the img source to read data
int x, int y: coordinates
return: pixel value (0-255)
 */
unsigned char read_pixel(image* img, int x, int y){
    return (unsigned char) img->img[y*img->w + x];
}

/* 
image* img: pointer to the img to write data
int x, int y: coordinates
unsigned char val: value to store
 */
void write_pixel(image* img, int x, int y, unsigned char val){
    img->img[y*img->w + x] = val;
}