#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void error(char *error, ...)
{
	va_list argptr;
	va_start(argptr, error);
	vprintf(error, argptr);
	printf("\n");
	va_end(argptr);
}

void help(char *error, ...)
{
	va_list argptr;
	va_start(argptr, error);
	vprintf(error, argptr);

	printf("Usage: lumpy [OPTION] ... [INPUT] ... [OUTPUT]\n");
	va_end(argptr);
}
