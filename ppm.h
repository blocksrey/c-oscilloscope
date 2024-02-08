#ifndef PPM_H
#define PPM_H

#include "zeromath/prim.h"
#include "zeromath/maths.h"
#include <stdio.h>

static void write_ppm(f32 *buffer, u32 width, u32 height) {
	printf("P6\n%i %i\n255\n", width, height);
	for (u32 i = 0; i < width*height; ++i) {
		putchar((i8)MIN(60*buffer[i], 255));
		putchar((i8)MIN(245*buffer[i], 255));
		putchar((i8)MIN(130*buffer[i], 255));
	}
}

#endif
