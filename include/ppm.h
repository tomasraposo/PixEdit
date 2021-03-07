#ifndef __PPM_H__
#define __PPM_H__
#include <stdio.h>

typedef struct {
	unsigned char colours[3];
} pixel;

typedef struct {
	char* magic_number;	
	int width;
	int height;
	int max_val;
	pixel* body;
	int size;
} ppm;

/* returns pixel indexed at row r, column c */
pixel get_pixel(ppm* img, int r, int c);
/* set pixel indexed at row r, column c*/
void set_pixel(pixel p, ppm* img, int r, int c);
/* parses header of ppm image and returns index of last consumed byte in the input stream */
int read_header(FILE* fin, ppm* img);
/* parses body of ppm image accepts both P3 and P6 formats */
void read_body(FILE* fin, int curr_byte, ppm* img);
/* writes pixel data to file */
void write_ppm(FILE* fout, ppm* img);
/* skip trailling whitespace and line comments */
static void skipws(FILE* fin);
void free_ppm(ppm* img);
#endif/* !__PPM_H__ */