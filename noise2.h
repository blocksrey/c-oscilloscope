#ifndef NOISE2_H
#define NOISE2_H

#include "noise.h"

static inline int stitch2(int n, int x, int y) {
	return x%n + y%n*n;
}

static inline float interp2(float x, float y, float a, float b, float c, float d) {
	return a + (b - a)*x + (c - a)*y + (a - b - c + d)*x*y;
}

static inline float noise2(noiseMap *map, float *v) {
	int x = floor(v[0]);
	int y = floor(v[1]);
	return interp2(
		remap(fract(v[0])),
		remap(fract(v[1])),
		map->edges[stitch2(map->total, x    , y    )],
		map->edges[stitch2(map->total, x + 1, y    )],
		map->edges[stitch2(map->total, x    , y + 1)],
		map->edges[stitch2(map->total, x + 1, y + 1)]
	);
}

#endif