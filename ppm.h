#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include "libMaths/maths.h"

static void writePPM(f32 *buffer, u32 width, u32 height, char *path) {
	FILE *fp = fopen(path, "w");

	fprintf(fp, "P6\n%i %i\n255\n", width, height);

	for (int i = 0; i < width*height; ++i) fprintf(
		fp,
		"%c%c%c",
		(i8)MIN(100*buffer[i], 255),
		(i8)MIN(255*buffer[i], 255),
		(i8)MIN(150*buffer[i], 255)
	);

	fclose(fp);
}

#endif
