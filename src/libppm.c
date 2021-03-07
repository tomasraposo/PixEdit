#include "libppm.h"
#include "ppm.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void negate(ppm* img, int colour) {
	for (int i=0; i<img->size; i++) {
			img->body[i].colours[colour] = img->max_val - img->body[i].colours[colour];
	}	
}

void flatten(ppm* img, int colour) {
	for (int i=0; i<img->size; i++) {
		img->body[i].colours[colour] = 0;
	}	
}

void mirror(ppm* img) {
	for (int i=0; i<img->size/2; i++) {
		pixel p = img->body[img->size-1-i];
		img->body[img->size-1-i] = img->body[i];
		img->body[i] = p;
	}	
}

void flip_vertical(ppm* img) {
	for ( int i = 0; i < img->height/2; ++i ) {
		int k = img->height - 1 - i;
		for ( int j = 0; j < img->width; ++j ) {
			pixel p = img->body[i * img->width + j];
			img->body[i * img->width + j] = img->body[k * img->width + j];
			img->body[k * img->width + j] = p;
    	}
	}
}

void grey_scale(ppm* img) {
	for (int i=0; i<img->size; i++) {
		int avg = (img->body[i].colours[RED]+img->body[i].colours[GREEN]+img->body[i].colours[BLUE]) / 3;
		img->body[i].colours[RED] = avg; 
		img->body[i].colours[GREEN] = avg;
		img->body[i].colours[BLUE] = avg;
	}
}

void horizontal_blur(ppm* img) {
	for (int i=0; i<img->height; i++) {
		for (int j=0; j<img->width; j++) {
			int ravg = 0, gavg = 0, bavg = 0;
			int k = i*img->width+j;
			int max_k;
			if ((k+1) % img->width == 0) max_k=k+1;
			else if (k % (img->width-1) == img->width-1) max_k=k+2;
			else max_k = k+3;
			for (int l=k; l<max_k; l++) {
				ravg += img->body[l].colours[RED];
				gavg += img->body[l].colours[GREEN];
				bavg += img->body[l].colours[BLUE];
			}
			img->body[k].colours[RED]=ravg/(max_k-k);
			img->body[k].colours[GREEN]=gavg/(max_k-k);
			img->body[k].colours[BLUE]=bavg/(max_k-k);
		}
	}
}

void extreme_contrast(ppm* img) {
	for (int i=0; i<img->size; i++) {
		for (int j=0; j<3; j++) {
			if (img->body[i].colours[j] > 127) {
				img->body[i].colours[j] = 255;
			} else {
				img->body[i].colours[j] = 0;
			}
		}	
	}
}

void random_noise(ppm* img) {
	unsigned char MAX_VALUE;
	for (int i=0; i<img->size; i++) {
		for (int j=0; j<3; j++) {
			MAX_VALUE = img->max_val - img->body[i].colours[j];
			if (MAX_VALUE == 0) {
				img->body[i].colours[j]-=(rand() % 255);
			} else if (MAX_VALUE == 255) {
				img->body[i].colours[j]+=(rand() % 255);
			} else {
				if ((rand() % 2) == 0) {
					img->body[i].colours[j]-=rand() % MAX_VALUE;;
				} else {
					img->body[i].colours[j]+=rand() % MAX_VALUE;;
				}
			}
		}
	}
}

void invert_rgb(ppm* img) {
	for (int i=0; i<img->size; i++) {
		img->body[i].colours[RED] = img->max_val - img->body[i].colours[RED];
		img->body[i].colours[GREEN] = img->max_val - img->body[i].colours[GREEN];
		img->body[i].colours[BLUE] = img->max_val - img->body[i].colours[BLUE];
	}
}

void zerout(ppm* img, int colour1, int colour2) {
	for (int i=0; i<img->size; i++) {
		img->body[i].colours[colour1] = 0;
		img->body[i].colours[colour2] = 0;
	}
}
