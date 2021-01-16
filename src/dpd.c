#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#include "common.h"
#include "image.h"

void write_lump_file(const char lump_filename[], const int image_data[],
		     const size_t image_data_size)
{
	int fd = open(lump_filename, O_RDWR | O_CREAT, 0644);

	if (fd == -1)
		error("[write_lump_file] File %s not be opened for reading",
		      lump_filename);
	close(fd);

	FILE *fp = fopen(lump_filename, "wb+");

	for (unsigned int i = 0; i < image_data_size; i++) {
		fputc(image_data[i], fp);
	}

	fclose(fp);
}

void build_palette(const char *image_filename, const char *lump_filename)
{
	int width, height;

	int *image_data;
	size_t image_data_size;

	if (!read_png_file(image_filename, &image_data, &image_data_size,
			   &width, &height))
		error("Error in loading the image\n");

	write_lump_file(lump_filename, image_data, image_data_size);
	free(image_data);

    if (image_data != NULL) {
        image_data = NULL;
    }
}

int main(int argc, char **argv)
{
	const char *image_filename = argv[1];
	const char *lump_filename = argv[2];

	if (argc < 3)
		help("A minimum of 2 arguments are required (at least one PNG file and one output file)\n");

	build_palette(image_filename, lump_filename);
}
