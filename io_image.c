#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"


void read_img(char path[], image* img){
    img->img = stbi_load(path, &img->w, &img->h, &img->c, 0);
}

void write_img(char path[], image img){
    stbi_write_png(path, img.w, img.h, img.c, img.img, img.w*img.c);
}

unsigned char read_pixel(image* img, int x, int y){
    return img->img[y*img->w + x];
}

void write_pixel(image* img, int x, int y, unsigned char val){
    img->img[y*img->w + x] = val;
}