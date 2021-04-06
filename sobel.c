#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#include "img_utils.h"
#include "sobel.h"

typedef struct{
    char** Gx;
    char** Gy;
    image* img;
    image* nImg;
    int start;
    int end;
}sobelArg;

/*{{-1,0,1},
                    {-2,0,2},
                    {-1,0,1}},
                    Gy[3][3] = {{1,2,1},
                                {0,0,0},
                                {-1,-2,-1}};*/
image* sobel(image* img){
    char** Gx = createMatrixS(3,3);
    char** Gy = createMatrixS(3,3);
    Gx[0][0] = -1;
    Gx[0][1] = 0;
    Gx[0][2] = 1;
    Gx[1][0] = -2;
    Gx[1][1] = 0;
    Gx[2][2] = 2;
    Gx[2][0] = -1;
    Gx[2][1] = 0;
    Gx[2][2] = 1;
    Gy[0][0] = 1;
    Gy[0][1] = 2;
    Gy[0][2] = 1;
    Gy[1][0] = 0;
    Gy[1][1] = 0;
    Gy[2][2] = 0;
    Gy[2][0] = -1;
    Gy[2][1] = -2;
    Gy[2][2] = -1;
    image* nImg, *pImg;
    sobelArg arg[N_THR];
    pthread_t thr[N_THR];
    pImg = pad(img,1);
    nImg  = new_img(img->h, img->w);
    int nLines = img->h/N_THR;
    for (int i = 0; i < N_THR; i++) {
        arg[i].Gx = Gx;
        arg[i].Gy = Gy;
        arg[i].img = pImg;
        arg[i].nImg = nImg;
        arg[i].start = (nLines*i) + 1 ;
        if (i < N_THR - 1){
            arg[i].end = nLines*(i+1) + 1;
        }else{
            arg[i].end = img->h - 1;
        }
        pthread_create(&thr[i],NULL,sobelLine,(void *) &arg[i]);
    }
    for (int i = 0; i < N_THR; i++){
        pthread_join(thr[i], NULL);
    }
    freeMatrix((void**)Gx,3,3);
    freeMatrix((void**)Gy,3,3);
    free_img(pImg);
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
        //printf("Estou aqui\n");
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

char **createMatrixS(int n, int m)
{
    char **matrix = (char **)malloc(m * sizeof(char *));
    for (int i = 0; i < m; i++)
    {
        matrix[i] = (char *)malloc(n * sizeof(char));
    }
    return matrix;
}

void freeMatrix(void **matrix, int n, int m){
    for(int i = 0; i < m; i++){
        free(matrix[i]);
    }
    free(matrix);
}

void* sobelLine(void* args){
    sobelArg* arg = (sobelArg*) args;
    char** Gx = arg->Gx;
    char** Gy = arg->Gy;
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
            freeMatrix((void**)neighbor,3,3);
        }
    }
}

unsigned char sobelPixel(char **Gx, char **Gy, unsigned char **neighbor) {
    int v = 0, h = 0,result;
    unsigned char G;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            //printf("E eu aqui\n");
            h += Gx[i][j]*neighbor[i][j];
            v += Gy[i][j]*neighbor[i][j];
        }
    }
    result = (int) round(sqrt(pow(h, 2) + pow(v, 2)));
    if (result > 255){
        G = 255;
    } else if (result < 0){
        G = 0;
    } else{
        G = (unsigned char)round(sqrt(pow(h, 2) + pow(v, 2)));
    }
    return G;
}
