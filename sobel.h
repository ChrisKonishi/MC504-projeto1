#define N_THR 8 /* number of threads */

/*
 * Argument struct for sobel line function
 * char** Gx: Horizontal Sobel mask;
 * char** Gy: Vertical Sobel mask;
 * image* img: the original image to be transformed;
 * image* nImg: where the transformed image will be recorded;
 * int start: the first line for this sobelLine;
 * int end: the stop condition for the function
 * */
typedef struct{
    char** Gx;
    char** Gy;
    image* img;
    image* nImg;
    int start;
    int end;
}sobelArg;

/*
 * Applies sobel filter
 * image* img: the image that the filter will be applied
 */
image* sobel(image* img);

/*
 * Gets the 3x3 neighborhood of a given pixel;
 * int x: The x position of the pixel;
 * int y: The y position of the pixel;
 * image* img: the image where the neighborhood will be taken
 * */
unsigned char ** getNeighbor(int x, int y, image* img);

/*
 * Creates a unsigned char Matrix;
 * int n: Number of lines of the matrix;
 * int m: number of columns of the matrix
 * */
unsigned char ** createMatrix(int n, int m);

/*
 * Creates a char Matrix;
 * int n: Number of lines of the matrix;
 * int m: number of columns of the matrix
 * */
char **createMatrixS(int n, int m);

/*
 * Liberates a allocated matrix, of any kind;
 * void **matrix: the matrix to be liberated;
 * int n: the number of lines of this matrix
 * */
void freeMatrix(void **matrix, int n);

/*
 * Parallel execution on some lines of sobel filter;
 * void* args: struct containing the arguments need by this function, this casa a sobelArg
 * */
void* sobelLine(void* args);

/*
 * Executes the calculation for each pixel of the image;
 * char **Gx: Sobel horizontal mask;
 * char **Gy: Sobel vertical mask;
 * unsigned char **neighbor: 3x3 Neighborhood matrix
 * */
unsigned char sobelPixel(char **Gx, char **Gy, unsigned char **neighbor);
