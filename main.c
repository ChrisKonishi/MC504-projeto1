#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "img_utils.h"
#include "noise_red.h"

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
    if (argc < 4){
        printf("Argument error\n");
        exit(1);
    }
    
    image* img = malloc(sizeof(image));
    image* out_img;
    

    read_img(arg[2], img);

    if (!strcmp(arg[1], "noise")){
        /* Noise reduction */
        out_img = noise_reduction(img);
    }
    else{
        printf("Method not defined\n");
        exit(1);
    }

    write_img(arg[3], *out_img);

    free_img(img);
    free_img(out_img);
    return 0;
}