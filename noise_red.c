#include <stdlib.h>
#include <pthread.h>

#include "img_utils.h"
#include "noise_red.h"

#define N_THR 8

typedef struct {
    image* padded_img;
    image* out_img;
    int x0;
    int y0;
    int xf;
    int yf;
} thread_args;

/*
Compare two integers.

const void *a: pointer to the first integer
const void *b: pointer to the second integer

return: 1 if a > b, -1 if a < b
*/
int compare(const void *a, const void *b){
    int i = *(const int *)a;
    int j = *(const int *)b;

    return (i > j) - (i < j);
}

/*
Function passed in thread to apply the noise reduction algorithm in image
section.

image* out_padded: pointer to the base img data
image* out_img: pointer to the img to write data
int x0, int y0, int xf, int yf: beginning and ending coordinates
 */
void* reduction_thread(void* args){
    int i, j;
    int r, k;
    int count;
    int median, median_array[8];

    thread_args* arg = (thread_args*) args;
    image* padded_img = arg->padded_img;
    image* out_img = arg->out_img;
    int x0 = arg->x0;
    int y0 = arg->y0;
    int xf = arg->xf;
    int yf = arg->yf;

    for (i = y0; i < yf; i++){
        for (j = x0; j < xf; j++){
            count = 0;
            for (r = i - 1; r < i + 2; r++){
                for (k = j - 1; k < j + 2; k++){
                    if (!(r == i && k == j)){
                        median_array[count] = read_pixel(padded_img, r, k);
                    }
                    count++;
                }
            }

            qsort(median_array, 8, sizeof(int), compare);
            median = (median_array[3] + median_array[5]) / 2;
            write_pixel(out_img, i, j, median);
        }
    }
    return NULL;
}

/*
Called by the main function.

args:   operation
        input image
        out image
        additional args to the operation (optional)
ex:
    ./main sobel in.png out.png

 */
image* noise_reduction(image* img){

    pthread_t thr[N_THR];

    int i;
    int pad_size = 20;
    image* padded_img = pad(img, pad_size);
    image* out_img = pad(img, pad_size);

    thread_args args[N_THR];

    int div = ( (int) out_img->h - pad_size*2)/N_THR;
    for (i = 0; i < N_THR; i++){

        args[i].padded_img = padded_img;
        args[i].out_img = out_img;

        args[i].x0 = pad_size;
        args[i].xf = out_img->w - pad_size;
        args[i].y0 = i * div;
        if (i != N_THR - 1){
            args[i].yf = div*(i+1);
        }
        else{
            args[i].yf = out_img->h - pad_size;
        }

        pthread_create(&thr[i], NULL, reduction_thread, (void*) &args[i]);
    }

    for (i = 0; i < N_THR; i++){
        pthread_join(thr[i], NULL);
    }

    free_img(padded_img);

    return out_img;
}

/*
int main(int argc, char* arg[]){

    noise_reduction(argc, arg);

    return 0;
}
*/
