#ifndef SAUVOLA_H
#define SAUVOLA_H

#include "img_utils.h"

typedef struct {
/* arguments for the sauvola function 
    image *img: image to be filtered (needs to be padded)
    image *new_img: result image
    int R, k: sauvola arguments
    int start, end: lines of the matrix to be modified
*/
    image *img, *nova_img;
    int n, start, end;
    float R, k;

} sauvola_args;

void *sauvola(void *args);
/* function to be called from pthread_create
    Arguments: 
        sauvola_args *args: struct described above
*/
image *apply_sauvola(image *img, float R, float k, int n);
/* function that creates the p-threads and distributes the work
    Arguments:
        image *img: image to be filtered
        int R, k: sauvola arguments
    Return:
        new, filtered image
*/

#endif