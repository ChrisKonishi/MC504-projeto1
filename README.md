# MC504 Projeto 1

## Compiling

~~~bash
gcc -pthread *.c -lm -o app.out -Wall
~~~

## Executing

~~~bash
./app.out <method> <img_in> <img_out> <optional_args>
~~~

Methods: sobel, noise, sauvola

### Noise Reduction

~~~bash
./app.out noise noise_test.png out_noise.png
~~~

## Useful definition in img_utils

- image: a structure that stores image data: height, width, channel, pixel values

- read_image, write_image

- read_pixel, write_pixel: functions to manipulate the pixel value in an image (avoid manipulating directly)

- pad: pads an image with zeros 

- new_img: allocates a new image (height, width)

- free_img

## Sauvola method

The sauvola method is implemented in two functions: *apply_sauvola* and *sauvola*. The first is called by the main and arranges the method arguments and creates the p-threads used for parallelism, while the latter makes the necessary calculations and effectively writes the output image.

To use the method, simply follow the instructions given in the *Executing* section. This implementation uses fixed values of *k* and *R*, as well as a neighborhood of 15x15 elements. If you wish to change these arguments, you can tweak the *apply_sauvola* function call, which takes the original image, *R*, *k* and the neighborhood size, respectively.
