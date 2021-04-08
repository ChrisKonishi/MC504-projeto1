#include <stdlib.h>
#include <pthread.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image/stb_image.h"
#include "stb_image/stb_image_write.h"
#include "img_utils.h"

#include "img_utils.h"

#define N_THR 8 

/* pad_line args */
typedef struct{
/* 
pimg: padded image pointer location (h, w, c must be filled)
img: original image
p: pad size

The function will pad the lines [start, end-1]
*/
    image* pimg;
    image* img;
    int p;
    int start;
    int end;
} pad_arg;


void* pad_line(void* args);

/* 
char path[]: path to the image
image* img: pointer to an image struct to store the data
Only supports grayscale images
 */
void read_img(char path[], image* img){
    img->img = stbi_load(path, &img->w, &img->h, &img->c, 0);
    if (img->c > 1){
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


void* pad_line(void* args){
/* 
pads an image with zeros
pimg: padded image pointer location (h, w, c must be filled)
img: original image
p: pad size

The function will pad the lines [start, end-1]
*/
    pad_arg* arg = (pad_arg*) args;
    int start = arg->start;
    int end = arg->end;
    int p = arg->p;
    image* img = arg->img;
    image* pimg = arg->pimg;

    for (int i=start; i<end; i++){
        for (int j=0; j<pimg->w; j++){
            if (i<p || j<p || i>=pimg->h-p || j>=pimg->w-p){
                write_pixel(pimg, j, i, 0);
            }
            else{
                write_pixel(pimg, j, i, read_pixel(img, j-p, i-p));
            }
        }
    }
    return NULL;
}

image* pad(image* img, int p){
    image* pimg = new_img(img->h + 2*p, img->w + 2*p);

    pthread_t thr[N_THR];
    pad_arg args[N_THR];

    int n_lines = (int) pimg->h / N_THR;

    for (int i=0; i<N_THR; i++){
        args[i].pimg = pimg;
        args[i].img = img;
        args[i].p = p;
        args[i].start = n_lines*i;
        if (i == N_THR-1)
            args[i].end = pimg->h;
        else
            args[i].end = n_lines*(i+1);
        pthread_create(&thr[i], NULL, pad_line, (void*) &args[i]);
    }

    for (int i=0; i<N_THR; i++)
        pthread_join(thr[i], NULL); 

    return pimg;
}


void free_img(image* img){
    free(img->img);
    free(img);
}


image* new_img(int h, int w){
    image* img = malloc(sizeof(image));
    img->h = h;
    img->w = w;
    img->c = 1;
    img->img = malloc(h*w*sizeof(unsigned char));
    return img;
}
