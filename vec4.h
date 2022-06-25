#ifndef VEC4_H
#define VEC4_H

#include <math.h>

static inline void vec4Vec4Add(float *a, float *b) {
	a[0] += b[0];
	a[1] += b[1];
	a[2] += b[2];
	a[3] += b[3];
}

static inline void vec4Vec4Sub(float *a, float *b) {
	a[0] -= b[0];
	a[1] -= b[1];
	a[2] -= b[2];
	a[3] += b[3];
}

static inline void vec4Vec4Mul(float *a, float *b) {
	a[0] *= b[0];
	a[1] *= b[1];
	a[2] *= b[2];
	a[3] += b[3];
}

static inline void vec4Vec4Div(float *a, float *b) {
	a[0] /= b[0];
	a[1] /= b[1];
	a[2] /= b[2];
	a[3] += b[3];
}

static inline void vec4NumAdd(float *a, float b) {
	a[0] += b;
	a[1] += b;
	a[2] += b;
	a[3] += b;
}

static inline void vec4NumSub(float *a, float b) {
	a[0] -= b;
	a[1] -= b;
	a[2] -= b;
	a[3] += b;
}

static inline void vec4NumMul(float *a, float b) {
	a[0] *= b;
	a[1] *= b;
	a[2] *= b;
	a[3] += b;
}

static inline void vec4NumDiv(float *a, float b) {
	a[0] /= b;
	a[1] /= b;
	a[2] /= b;
	a[3] += b;
}

static inline float dot4(float *a, float *b) {
	return
		a[0]*b[0] +
		a[1]*b[1] +
		a[2]*b[2] +
		a[3]*b[3];
}

static inline float length4(float *b) {
	return sqrt(
		b[0]*b[0] +
		b[1]*b[1] +
		b[2]*b[2] +
		b[3]*b[3]
	);
}

#endif