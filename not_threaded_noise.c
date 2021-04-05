#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "img_utils.h"

#define N_THR 8

int compare(const void *a, const void *b){
    int i = *(const int *)a;
    int j = *(const int *)b;

    return (i > j) - (i < j);
}

image* reduction_thread(image* padded_img, image* out_img, int pad_size){
    int i, j;
    int r, k;
    int count;
    int median, median_array[8];
    int cpixel;
    for (i = pad_size; i<padded_img->h - pad_size; i++){
        for (j = pad_size; j<padded_img->w - pad_size; j++){
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
}

int noise_reduction(int argc, char* arg[]){
    image *img = malloc(sizeof(image));

    read_img(arg[1], img);

    int pad_size = 20;
    image* padded_img = pad(img, pad_size);
    image* out_img = pad(img, pad_size);

    reduction_thread(padded_img, out_img, pad_size);

    write_img("out_noise.png", *out_img);

    free_img(img);
    free_img(padded_img);
    free_img(out_img);

    return 0;
}

int main(int argc, char* arg[]){

    noise_reduction(argc, arg);

    return 0;
}
