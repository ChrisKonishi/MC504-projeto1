#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "img_utils.h"

// #define N_THR 8

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

void *sauvola(void *args) {
    sauvola_args *arg = (sauvola_args*) args;
    float sum, squared_sum;
    unsigned char val, pixel;
    int n = arg->n;
    float average, sqr_avg, std_dev;

    image *img = arg->img;
    image *nova_img = arg->nova_img;
    int row, col, i, j, p_row, p_col;
    float limiar;

    for (row = arg->start; row <= arg->end; row++) {
        for (col = 0; col < (img->w - n + 1); col++) {
            sum = 0;
            squared_sum = 0;
            for (i = -n/2; i <= n/2; i++) {
                for (j = -n/2; j <= n/2; j++) {
                    p_row = row + i + (int)n/2;
                    p_col = col + j + (int)n/2;
                    val = read_pixel(img, p_row, p_col);
                    sum += ((int) val)/255.0;
                    squared_sum += pow(((int) val)/255.0, 2);
                }
            }

            average = sum/(n * n);
            sqr_avg = squared_sum/(n * n);
            std_dev = sqrt(sqr_avg - pow(average, 2)); 
            limiar = average * (1 + arg->k * (std_dev/arg->R - 1));
            limiar = limiar * 255;
            pixel = (int) read_pixel(img, row + (int) n/2, col + (int) n/2);
            if (pixel > limiar) 
                pixel = 0;
            else
                pixel = 255;
            write_pixel(nova_img, row, col, (unsigned char) pixel);
        } 
    }
    int a = 0;
 }

image *apply_sauvola(image *img, float R, float k, int n) {
    pthread_t thr[N_THR];
    sauvola_args args[N_THR];
    int img_div, resto, start, end;
    image *nova_img, *pimg;
    img_div = img->h / N_THR;
    resto = img->h % N_THR;
    
    pimg = pad(img, n/2);
    nova_img = new_img(img->h, img->w);

    start = 0;
    for (int i = 0; i < N_THR; i++) {
        args[i].img = pimg;
        args[i].nova_img = nova_img;
        args[i].R = R;
        args[i].k = k;
        args[i].n = n;
        args[i].start = start;

        end = start + img_div - 1; 
            
        if (i < resto) 
            end++;
        
        if (end >= img->h) 
            end = img->h - 1;
        
        args[i].end = end;

        printf("%d, %d\n", args[i].start, args[i].end);
        
        start = end + 1;
        pthread_create(&thr[i], NULL, sauvola, (void*) &args[i]);
    }

    for (int i=0; i<N_THR; i++)
        pthread_join(thr[i], NULL);  

    return nova_img;
}

int main(int argc, char* arg[]){
    if (argc < 3){
        printf("Argument error\n");
        exit(1);
    }
    
    image *img = malloc(sizeof(image));

    read_img(arg[2], img);

    image* sauvola_img = apply_sauvola(img, 0.5, 0.05, 15);

    write_img("result.png", *sauvola_img);

    return 0;
} 