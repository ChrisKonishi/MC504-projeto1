#include <stdio.h>
#include <stdlib.h>

#include "img_utils.h"
#include "sobel.h"

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
    image * sobelImage;

    read_img(arg[2], img);

    if (arg[1][0] == '2'){
        sobelImage = sobel(img);
    } else{
        printf("Wrong operation\n");
    }

    //image* padded_img = pad(img, 20);

    //write_img(arg[3], *padded_img);
    write_img(arg[3],*sobelImage);

    free_img(img);
    //free_img(padded_img);
    free_img(sobelImage);
    return 0;
}