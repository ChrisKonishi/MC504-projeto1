#include <stdio.h>
#include <stdlib.h>

#include "img_utils.h"

#include "sobel.h"
typedef struct{
    int** Gx;
    int** Gy;
    image* img;
    image* nImg;
}sobelArg;

image* sobel(image* img){
    int Gx[3][3] = {{-1,0,1},
                    {-2,0,2},
                    {-1,0,1}},
                    Gy[3][3] = {{1,2,1},
                                {0,0,0},
                                {-1,-2,-1}};
    image* nImg;
    sobelArg* arg = (sobelArg*) malloc(sizeof(sobelArg));
    arg->Gx = (int**) Gx;
    arg->Gy = (int**) Gy;
    nImg = pad(img,1);
    arg->img = nImg;
    arg->nImg = new_img(img->h,img->w);

}

unsigned char ** getNeighbor(int x, int y, image* img){
    unsigned char** m = createMatrix(3,3);
    if(x < 1 || x > img->h-2 || y < 1 || y < img->w - 2){
        printf("error\n");
        return NULL;
    }else {
        for (int i = 0, v = -1; i < 3, v < 2; i++, v++){
            for (int j = 0, h = -1; j < 3, h < 2; j++, h++){
                m[i][j] = read_pixel(img,x+h,y+v);
            }
        }
        return m;
    }
}

unsigned char ** createMatrix(int n, int m){
    unsigned char** matrix = (unsigned char**) malloc(m*sizeof(unsigned char*));
    for(int i = 0; i < m; i++){
        matrix[i] = (unsigned char*) malloc(n*sizeof(unsigned char));
    }
    return matrix;
}
void freeMatrix(unsigned char **matrix, int n, int m){
    for(int i = 0; i < m; i++){
        free(matrix[i]);
    }
    free(matrix);
}