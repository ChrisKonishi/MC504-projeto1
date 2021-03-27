#include <stdio.h>
#include <stdlib.h>

#include "img_utils.h"

#define N_THR 8 /* number of threads */

/* 
args:   operation
        input image
        out image
        additional args to the operation (optional)
ex:
    ./main sobel in.png out.png

 */
int main(int argc, char* arg[]){
    if (argc < 3){
        printf("Argument error\n");
        exit(1);
    }
    
    image *img = malloc(sizeof(image));
    image* padded_img = malloc(sizeof(image));

    read_img(arg[2], img);

    pad(img, padded_img, 20);

    write_img(arg[3], *padded_img);

    free_img(img);
    free_img(padded_img);
    return 0;
}