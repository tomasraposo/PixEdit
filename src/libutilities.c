#include "libutilities.h"
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

char* lastsubstr(char* str, char sp) {
	char* auxstr;
	while (1) {
		auxstr = strrchr(str, sp);
		if (!auxstr) break;
		str = auxstr+1;
	}
	if (str) {
		return str;
	}
	return "";
}

int fpeek(FILE* fin) {
	int c = fgetc(fin);
	ungetc(c, fin);
	return c;
}

char* itoa(int n) {
	if (n > INT_MAX) {
		fprintf(stderr, "Potential integer overflow.");
		exit(1);
	}
	int temp = n, len;
	char *str;
	if (n == 0) {
		// *str = '\0';
		// *str++ = '0';
		// return str;
		return "0";
	} 
	if (n > 0) { 
		len = 0;
	} else { 
		len = 1;
		*str = '-'; /* accommodate '-' sign */
	}
	while (temp) {
		temp /= 10;
		len++;
	}
	str = malloc(len * sizeof(char));
	if (!str) {
		fprintf(stderr, "%s\n.", "Unable to allocate sufficient memory.");
		exit(1);
	}
	temp = n;
	int i = len-1;
	while (temp) {
		*(str+i) = temp % 10 + '0';
		temp /= 10;
		i--;
	}
	return str;
}

int atoint(char* str) {
	int n = 0;
	int sign = 1;
	if (str[0] == '-') {
		sign = -1;
		str++;
	}
	while (str) {
		if (*str < '0' || *str > '9') { /* check if is invalid ascii value */
			break;
		}
		n = n * 10 + *str - '0';
		str++;
	}
	return sign * n;
}

char* tnow() {
	time_t t;
	time(&t);
	return asctime(localtime(&t));
}

void err(char *errstr) {
	fprintf(stderr, "%s\n", errstr);	
	exit(1);
}
