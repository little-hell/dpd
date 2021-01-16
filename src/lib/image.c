#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "image.h"
#include "common.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static void get_pixel(stbi_uc *image, int width, int x, int y, stbi_uc *r,
		      stbi_uc *g, stbi_uc *b)
{
	// https://redd.it/8gyyb6

	const stbi_uc *pixel = image + (3 * (y * width + x));

	*r = pixel[0];
	*g = pixel[1];
	*b = pixel[2];
}

bool read_png_file(const char filename[], int **image_data,
		   size_t *image_data_size, int *width, int *height)
{
	int channels;

	unsigned char *img = stbi_load(filename, width, height, &channels, 3);

	if (img == NULL) {
		return false;
	}

	printf("Loaded image with a width of %dpx, a height of %dpx and %d channels\n",
	       *width, *height, channels);
	*image_data = malloc(sizeof(int) * ((*width) * (*height) * 3));
	*image_data_size = (*width) * (*height) * 3;

	int i = 0;

	for (int y = 0; y < *height; y++) {
		for (int x = 0; x < *width; x++) {
			stbi_uc r;
			stbi_uc g;
			stbi_uc b;

			get_pixel(img, *width, x, y, &r, &g, &b);
			(*image_data)[i] = r;
			(*image_data)[i + 1] = g;
			(*image_data)[i + 2] = b;

			i += 3;
		}
	}
	return true;
}
