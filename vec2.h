#ifndef VEC2_H
#define VEC2_H

#include <math.h>

static inline void vec2Vec2Add(float *a, float *b) {
	a[0] += b[0];
	a[1] += b[1];
}

static inline void vec2Vec2Sub(float *a, float *b) {
	a[0] -= b[0];
	a[1] -= b[1];
}

static inline void vec2Vec2Mul(float *a, float *b) {
	a[0] *= b[0];
	a[1] *= b[1];
}

static inline void vec2Vec2Div(float *a, float *b) {
	a[0] /= b[0];
	a[1] /= b[1];
}

static inline void vec2NumAdd(float *a, float b) {
	a[0] += b;
	a[1] += b;
}

static inline void vec2NumSub(float *a, float b) {
	a[0] -= b;
	a[1] -= b;
}

static inline void vec2NumMul(float *a, float b) {
	a[0] *= b;
	a[1] *= b;
}

static inline void vec2NumDiv(float *a, float b) {
	a[0] /= b;
	a[1] /= b;
}

static inline float dot2(float *a, float *b) {
	return
		a[0]*b[0] +
		a[1]*b[1];
}

static inline float length2(float *b) {
	return sqrt(
		b[0]*b[0] +
		b[1]*b[1]
	);
}

#endif