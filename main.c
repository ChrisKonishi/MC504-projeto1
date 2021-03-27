#include <stdio.h>
#include <stdlib.h>

#include "img_utils.h"

#define N_THREADS 8

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

    read_img(arg[2], img);

    /* Test: print image, writes black pixels on the main diagonal */
    for (int i=0; i<img->h; i++){
        for (int j=0; j<img->w; j++){
            printf("%d ", read_pixel(img, i, j));
            if (i==j)
                write_pixel(img, i, j, 0);
        }
        printf("\n");
    }

    write_img(arg[3], *img);

    free(img);
    return 0;
}