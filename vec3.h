#ifndef VEC3_H
#define VEC3_H

#include <math.h>

static inline void vec3Vec3Add(float *a, float *b) {
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
}

static inline void vec3Vec3Sub(float *a, float *b) {
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
}

static inline void vec3Vec3Mul(float *a, float *b) {
	a[0] *= b[0];
	a[1] *= b[1];
	a[2] *= b[2];
}

static inline void vec3Vec3Div(float *a, float *b) {
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
}

static inline void vec3NumAdd(float *a, float b) {
	a[0] += b;
	a[1] += b;
	a[2] += b;
}

static inline void vec3NumSub(float *a, float b) {
	a[0] -= b;
	a[1] -= b;
	a[2] -= b;
}

static inline void vec3NumMul(float *a, float b) {
	a[0] *= b;
	a[1] *= b;
	a[2] *= b;
}

static inline void vec3NumDiv(float *a, float b) {
	a[0] /= b;
	a[1] /= b;
	a[2] /= b;
}

static inline float dot4(float *a, float *b) {
	return
		a[0]*b[0] +
		a[1]*b[1] +
		a[2]*b[2];
}

static inline float length3(float *b) {
	return sqrt(
		b[0]*b[0] +
		b[1]*b[1] +
		b[2]*b[2]
	);
}

#endif