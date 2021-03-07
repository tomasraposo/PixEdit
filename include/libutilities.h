#ifndef __LIBUTILITIES__H__
#define __LIBUTILITIES__H__
#include <stdio.h>

/* returns last substring after separator */
char* lastsubstr(char* str, char sp);
/* peek at next byte in the input stream */
int fpeek(FILE* fin);
/* return string representation of signed integer */
char* itoa(int n);
/* return numeric representation of string */
int atoint(char *str);
/* return ascii string of current date and time */
char* tnow();
/* prints to stderr and exits with code 1 */
void err(char *errstr);
#endif  //!__LIBUTILITIES__H__