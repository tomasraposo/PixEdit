#include "ppm.h"
#include "libppm.h"
#include "libutilities.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WIDTH 1
#define HEIGHT 2
#define MAX_VAL 3
#define SP 0x20 /* ' ' */
#define LF 0x0a /* \n' */
#define CR 0x0d /* \r' */

pixel get_pixel(ppm* img, int r, int c) {
	return img->body[r*img->width+c];
}

void set_pixel(pixel p, ppm* img, int r, int c) {
	img->body[r*img->width+c] = p;
}

int read_header(FILE *fin, ppm* img) {
	char buff[15], magic_number[3];
	int token = 1;
	char ch;
	if ((ch = fgetc(fin)) != 'P') 
		err("Please provide a valid ppm file.");	

	strncat(magic_number, &ch, 1);
	if (isdigit(ch = fgetc(fin)) && (ch == '3' || ch == '6')) {
		strncat(magic_number, &ch, 1);
		if ((img->magic_number = malloc(3 * sizeof(char))))
			strcpy(img->magic_number, magic_number);
	}
	while (1) {
		skipws(fin); /* skip excessive whitespace and line comments */
		while (isdigit(ch = fgetc(fin))) {
			strncat(buff, &ch, 1);
		}
		if (token == WIDTH) {
			img->width = atoint(buff);
		} else if (token == HEIGHT) {	
			img->height = atoint(buff);
		} else if (token == MAX_VAL) {
			img->max_val = atoint(buff);
			if (img->max_val < 0 || img->max_val > 255) /* check if max value is within bounds */
				err("Invalid RGB value.");
			skipws(fin);
			break;
		}
		token++;
		memset(buff, '\0', sizeof(buff)); 
		/* clear buffer , buffer[0] = '\0' */
	}
	int curr_byte = ftell(fin);	
	fclose(fin);
	return curr_byte;
}

void read_body(FILE* fin, int curr_byte, ppm* img) {
	long fsize;
    if (fseek(fin, 0, SEEK_END) || (fsize = ftell(fin)) > 0) {
		fseek(fin, curr_byte, SEEK_SET); /* skip first byte after the header */
		int bsize = img->width * img->height;
		pixel* body = malloc(bsize * sizeof(pixel));
		if (!body) 
			err("Unable to allocate sufficient memory.");	
		if (strcmp(img->magic_number, "P3")==0) {
			for (int i=0; i<bsize; i++) {
				for (int j=0; j<3; j++) {
					unsigned char colour;
					fscanf(fin, "%hhu", &colour);
					body[i].colours[j] = colour;
				}
			}
		} else if (strcmp(img->magic_number, "P6")==0) {
			size_t byte_count;
			if ((byte_count = fread(body, sizeof(pixel)*img->width, img->height, fin)) != img->height) {
				err("Unable to read from file.");
			}
		}
		img->body = body;
		img->size = bsize;
	}
	fclose(fin);
}

void write_ppm(FILE* fout, ppm* img) {
	fprintf(fout, "%s\n%d %d\n%d\n", img->magic_number, img->width, img->height, img->max_val);
	if (strcmp(img->magic_number, "P3")==0) {
		for (int i=0; i<img->size; i++) {
			for (int j=0; j<3; j++) {
				char* colour = itoa(img->body[i].colours[j]);
				fprintf(fout, "%s ", colour);
			}
			if ((i+1) % img->width == 0) {
				fprintf(fout, "\n");
			}
		}	
	} else if (strcmp(img->magic_number, "P6")==0) {
		fwrite(img->body, sizeof(pixel)*img->width, img->height, fout);
	}
	fclose(fout);
}

static void skipws(FILE* fin) {
	char ch;
	while (ch = fgetc(fin), isspace(ch) || ch == '#') {
		if (ch == '#') 
			while (ch = fgetc(fin), ch != '\n');
	}
	ungetc(ch, fin); /* put char back into the stream */
}

void free_ppm(ppm* img) {
	free(img->magic_number);
	free(img->body);
	free(img);
}