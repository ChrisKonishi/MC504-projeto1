# MC504 Projeto 1

## Compiling

~~~bash
gcc -pthread *.c -lm -o app.out -Wall
~~~

## Executing

~~~bash
./app.out <method> <img_in> <img_out> <optional_args>
~~~

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

