#include <stdio.h>
#include <stdlib.h>

#include "img_utils.h"

#include "sobel.h"
typedef struct{
    int** Gx;
    int** Gy;
    image* img;
}sobelArg;

image* sobel(image* img){
    int Gx[3][3] = {{-1,0,1},
                    {-2,0,2},
                    {-1,0,1}},
                    Gy[3][3] = {{1,2,1},
                                {0,0,0},
                                {-1,-2,-1}};
    sobelArg* arg = malloc(sizeof (sobelArg));
    arg->Gx = (int**) Gx;
    arg->Gy = (int**) Gy;
    arg->img = img;

}
