#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include "img_utils.h"
#include "sobel.h"

typedef struct{
    unsigned char** Gx;
    unsigned char** Gy;
    image* img;
    image* nImg;
    int start;
    int end;
}sobelArg;

image* sobel(image* img){
    unsigned char Gx[3][3] = {{-1,0,1},
                    {-2,0,2},
                    {-1,0,1}},
                    Gy[3][3] = {{1,2,1},
                                {0,0,0},
                                {-1,-2,-1}};
    image* nImg = new_img(img->h, img->w);
    sobelArg arg[N_THR];
    pthread_t thr[N_THR];
    img = pad(img,1);
    int nLines = img->h/N_THR;
    for (int i = 0; i < N_THR; i++) {
        arg[i].Gx = (unsigned char **) Gx;
        arg[i].Gy = (unsigned char **) Gy;
        arg[i].img = img;
        arg[i].nImg = nImg;
        arg[i].start = (nLines*i) + 1;
        if (i < N_THR - 1){
            arg[i].end = nLines*(i+1);
        }else{
            arg[i].end = img->h - 1;
        }
        pthread_create(&thr[i],NULL,sobelLine,(void *) &arg[i]);
    }
    for (int i = 0; i < N_THR; i++){
        pthread_join(thr[i], NULL);
    }
    return nImg;

}

unsigned char ** getNeighbor(int x, int y, image* img){
    unsigned char** m = createMatrix(3,3);
    //printf("x: %d, y: %d, w: %d, h: %d\n",x,y,img->w,img->h);
    if(x < 1){
        printf("error1\n");
        return NULL;
    } else if (y < 1){
        printf("error2\n");
        return NULL;
    } else if (x > (img->w - 2) ){
        printf("error3\n");
        return NULL;
    } else if (y > (img->h - 2)){
        printf("error4\n");
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

void* sobelLine(void* args){
    sobelArg* arg = (sobelArg*) args;
    unsigned char** Gx = arg->Gx;
    unsigned char** Gy = arg->Gy;
    unsigned char** neighbor;
    unsigned char pixel;
    for (int i = arg->start; i < arg->end; i++){
        for (int j = 1; j < arg->img->w-1; j++){
            neighbor = getNeighbor(j,i,arg->img);
            if (neighbor){
                pixel = sobelPixel(Gx, Gy, neighbor);
            } else{
                return NULL;
            }
            write_pixel(arg->nImg,j,i,pixel);
            freeMatrix(neighbor,3,3);
        }
    }
}

unsigned char sobelPixel(unsigned char **Gx, unsigned char **Gy, unsigned char **neighbor) {
    unsigned char v = 0, h = 0, G;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            h += Gx[i][j]*neighbor[i][j];
            v += Gy[i][j]*neighbor[i][j];
        }
    }
    G = (unsigned char) round(sqrt(pow(h,2)+pow(v,2)));
    return G;
}
