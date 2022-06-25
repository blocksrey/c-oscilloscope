#ifndef PPM_H
#define PPM_H

#include <stdio.h>

static void writePPM(float buffer[][3], int width, int height, char *path) {
	FILE *fp = fopen(path, "w");

	fprintf(fp, "P6\n%i %i\n255\n", width, height);

	for (int i = 0; i < width*height; ++i) fprintf(
		fp,
		"%c%c%c",
		(char)fmin(100.0f*buffer[i][1], 255),
		(char)fmin(255.0f*buffer[i][1], 255),
		(char)fmin(150.0f*buffer[i][1], 255)
	);

	fclose(fp);
}

#endif
