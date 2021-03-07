#ifndef __LIBPPM__H__
#define __LIBPPM__H__
#include "ppm.h"

/* RGB colour codes */
typedef enum { RED,GREEN,BLUE } colour;

/* negates the red, green or blue number of each pixel */
void negate(ppm* img, int colour);

/* sets red, green or blue value of each pixel to zero */
void flatten(ppm* img, int colour);

/* flips image along diagonal  */
void mirror(ppm* img);

/* flips each row vertically */
void flip_vertical(ppm *img);

/* sets each pixel value to the average of the three */
void grey_scale(ppm* img);

/* takes the values of the red numbers of three adjacent pixels and replaces them with their average */
void horizontal_blur(ppm* img);

/* changes each colour number to either the highest colour number possible (if greater than 127) or to 0 */
void extreme_contrast(ppm* img);

/* adds a random number to each colour number or subtracts a random number */
void random_noise(ppm* img);

/* inverts reg, green and blue colour vales */
void invert_rgb(ppm* img);

/* flattens green and blue colour values */
void zerout(ppm* img, int colour1, int colour2);
#endif  //!__LIBPPM__H__
