/*
Compare two integers.

const void *a: pointer to the first integer
const void *b: pointer to the second integer

return: 1 if a > b, -1 if a < b
*/
#include "noise_red.c"

int compare(const void *a, const void *b);

/*
Function passed in thread to apply the noise reduction algorithm in image
section.

image* out_padded: pointer to the base img data
image* out_img: pointer to the img to write data
int x0, int y0, int xf, int yf: beginning and ending coordinates
 */
void* reduction_thread(void* args);
/*
Called by the main function.

args:   operation
        input image
        out image
        additional args to the operation (optional)
ex:
    ./main sobel in.png out.png

 */
int noise_reduction(char argc, char* arg[]);
