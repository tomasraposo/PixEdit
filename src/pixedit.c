#include "ppm.h"
#include "libppm.h"
#include "libutilities.h"
#include "ppmviewer.h"
#include <stdlib.h>
#include <string.h>

#define STRCMP(a, eq, b) (strcmp(a, b) eq 0)

typedef enum {
	NEGATE,
	FLATTEN,
	MIRROR,
	FLIP_VERTICAL,
	GREY_SCALE,
	HORIZONTAL_BLUR,
	EXTREME_CONSTRAST,
	RANDOM_NOISE,
	INVERT_RGB,
	ZEROUT
} ppm_fn;

void (*ppm_fns[10])() = {
	negate,
	flatten,
	mirror,
	flip_vertical,
	grey_scale,
	horizontal_blur,
	extreme_contrast,
	random_noise,
	invert_rgb,
	zerout
};

int main(int argc, char** argv) {
	char* usage = "Usage: ./pixedit [OPTION] ... [INFILE] [OUTFILE]\nType './pixedit --h [--help]' for instructions.";
	if (argc < 2) 
		err(usage);
	if (STRCMP(argv[1], ==, "--h")) {
		char* version = "pixedit, a tiny ppm image editor version 1.0\nThis is free software: you are free to change and redistribute it.";
		char* d = "-d\t\t(single-flag) opens new window with [FILE]";
		char* n = "-n[r][g][b]\tnegates the red, green or blue value of each pixel";
		char* f = "-f[r][g][b]\tsets red, green or blue value of each pixel to zero";
		char* m = "-m\t\tflips image along diagonal";
		char* fv = "-fv\t\tflips each row vertically";
		char* gs = "-gs\t\tsets each pixel value to the average of the three";
		char* hb = "-hb\t\ttakes the values of the red numbers of three adjacent pixels and replaces them with their average";
		char* ec = "-ec\t\tchanges each colour number to either the highest colour number possible (if greater than 127) or to 0";
		char* rn = "-rn\t\tadds a random number to each colour number or subtracts a random number.";
		char* i =  "-i\t\tinverts the red, green and blue vales of each pixel";
		char* z = "-z[rg][rb][gb]\tflattens red and green, red and blue or green and blue values of each pixel";
		printf("%s\n\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", usage, version, d, n, f, m, fv, gs, hb, ec, rn, i, z);
		return 0; 
	}
	if (STRCMP(argv[1], ==, "-d") && argc == 3) {
		return img_viewer(argc, argv);		
	}
	FILE* fin = fopen(argv[argc-2], "r");
	ppm* img = malloc(1 * sizeof(ppm));
	char rmode[3];
	int curr_byte = read_header(fin, img); 
	
	if (strcmp(img->magic_number, "P3")) 
		strcpy(rmode, "r");
	else if (strcmp(img->magic_number, "P6")) 
		strcpy(rmode, "rb");
	
	if (!(fin = fopen(argv[argc-2], rmode))) {
		fprintf(stderr, "%s %s.\n", "Unable to open ", argv[argc-2]);
		fclose(fin);
		exit(1);
	}

	if (curr_byte > 0) read_body(fin, curr_byte, img);
	
	char wmode[3];
	if (strcmp(rmode, "r")) 
		strcpy(wmode, "w");
	else if (strcmp(rmode, "rb")) 
		strcpy(wmode, "wb");
	
	FILE* fout;	
	if (!(fout = fopen(argv[argc-1], wmode))) {
		fprintf(stderr, "%s %s.\n", "Unable to create ", argv[argc-1]);
		fclose(fout);
		exit(1);
	}

	for (int i=1; i<argc-2; i++) {
		if (STRCMP(argv[i],==,"-nr")) {
			(*ppm_fns[NEGATE])(img, RED);
		} else if (STRCMP(argv[i],==,"-ng")) {
			(*ppm_fns[NEGATE])(img, GREEN);
		} else if (STRCMP(argv[i],==,"-nb")) {
			(*ppm_fns[NEGATE])(img, BLUE);
		} else if (STRCMP(argv[i],==,"-fr")) {
			(*ppm_fns[FLATTEN])(img, RED);
		} else if (STRCMP(argv[i],==,"-fg")) {
			(*ppm_fns[FLATTEN])(img, GREEN);
		} else if (STRCMP(argv[i],==,"-fb")) {
			(*ppm_fns[FLATTEN])(img, BLUE);
		} else if (STRCMP(argv[i],==,"-m")) {
			(*ppm_fns[MIRROR])(img);
		} else if (STRCMP(argv[i],==,"-fv")) {
			(*ppm_fns[FLIP_VERTICAL])(img);
		} else if (STRCMP(argv[i],==,"-gs")) {
			(*ppm_fns[GREY_SCALE])(img);
		} else if (STRCMP(argv[i],==,"-hb")) {
			(*ppm_fns[HORIZONTAL_BLUR])(img);
		} else if (STRCMP(argv[i],==,"-ec")) {
			(*ppm_fns[EXTREME_CONSTRAST])(img);
		} else if (STRCMP(argv[i],==,"-rn")) {
			(*ppm_fns[RANDOM_NOISE])(img);
		} else if (STRCMP(argv[i],==,"-i")) {
			(*ppm_fns[INVERT_RGB])(img);
		} else if (STRCMP(argv[i],==,"-zrg")) {
			(*ppm_fns[ZEROUT])(img, RED, GREEN);
		} else if (STRCMP(argv[i],==,"-zrb")) {
			(*ppm_fns[ZEROUT])(img, RED, BLUE);
		} else if (STRCMP(argv[i],==,"-zgb")) {
			(*ppm_fns[ZEROUT])(img, GREEN, BLUE);
		}
	}
	write_ppm(fout, img);

	char* exit_msg =  " created with success.";
	strcat(argv[argc-1], exit_msg);
	free_ppm(img);
	fprintf(stdout, "%s\n", lastsubstr(argv[argc-1], '/'));
	exit(0);
}
