#define N_THR 8 /* number of threads */

/*
    Applies sobel filter
    image* img: the image that the filter will be applied
 */
image* sobel(image* img);

unsigned char ** getNeighbor(int x, int y, image* img);

unsigned char ** createMatrix(int n, int m);

void freeMatrix(unsigned char **matrix, int n, int m);