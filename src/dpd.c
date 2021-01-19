#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "common.h"
#include "image.h"

int write_lump_file(const char lump_filename[], const int image_data[],
		    const size_t image_data_size)
{
	int fd = open(lump_filename, O_CREAT | O_EXCL | O_WRONLY);

	if (fd == -1) {
		return 1;
	}

	FILE *fp = fdopen(fd, "wb+");

	if (fp == NULL) {
		return 1;
	}

	for (unsigned int i = 0; i < image_data_size; i++) {
		fputc(image_data[i], fp);
	}

	fclose(fp);

	return 0;
}

void build_palette(const char *image_filename, const char *lump_filename)
{
	int width, height;

	int *image_data;
	size_t image_data_size;

	if (read_png_file(image_filename, &image_data, &image_data_size, &width,
			  &height) != 0)
		error("Error in loading the image\n");
	exit(1);

	if (write_lump_file(lump_filename, image_data, image_data_size) != 0)
		error("Error writing or creating the lumpfile!\n");
	exit(1);

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
	exit(1);

	build_palette(image_filename, lump_filename);
}
