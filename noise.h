#ifndef NOISE_H
#define NOISE_H

#include <math.h>
#include <stdlib.h>

#include <stdio.h>

#define mod(x, y) (fmod(x, y) + (x < 0)*y)
#define fract(x) (x - floor(x))

static inline float remap(float x) {
	return 2*(x < .5 ? x*x : .5 - (x - 1)*(x - 1));
}

typedef struct noiseMap {
	int total;
	float *edges;
} noiseMap;

float noiseMapSize = sizeof(noiseMap);
float floatSize = sizeof(float);

static inline noiseMap *noiseMapNew(int length, int dimensions) {
	int total = pow(length, dimensions);

	noiseMap *map = (noiseMap *)malloc(noiseMapSize + floatSize*total);

	map->total = total;
	map->edges = (float *)malloc(floatSize*total);

	for (int i = 0; i < total; ++i) map->edges[i] = (float)(1.*rand()/RAND_MAX);

	return map;
}

#endif