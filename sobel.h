#define N_THR 8 /* number of threads */

/*
    Applies sobel filter
    image* img: the image that the filter will be applied
 */
image* sobel(image* img);

int** getNeighbor(int x, int y, image* img);

int** createMatrix(int n,int m);

void freeMatrix(int** matrix, int n, int m);