#ifndef MATH_H
#define MATH_H

#include "prim.h"

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)
#define CLAMP(n, a, b) MAX(a, MIN(n, b))

#define SQRT(x) (1/ISQRT(x))
#define SINP(x) COSP(x - 1.5707963f)
#define POW(x, y) EXP(LOG(x)*y)
#define LOG(x) (0.6931472f*LOG2(x))
#define PI 3.1415927f
#define QT 1.5707963f
#define ET 0.7853982f

static f32 ISQRT(f32 n) {
	union {
		i32 i;
		f32 f;
	} u = {.f = n};

	u.i = 0x5f3759df - (u.i >> 1);
	u.f *= 0.5f*(3 - n*u.f*u.f);

	return u.f;
}

static f32 ATAN(f32 c, f32 s) {
	f32 o = 0, t;

	if (s < 0)        c  = -c, s  = -s, o -= PI;
	if (c < 0) t = c, c  =  s, s  = -t, o += QT;
	if (c < s) t = c, c +=  s, s -=  t, o += ET;

	f32 d = 2/(c*c + s*s);
	f32 x = d*c*c - 1;
	f32 y = d*c*s;

	return
		o +
		0.3926991f -
		0.5574841f*(x - y) +
		0.1648119f*(x*x - y*y) -
		0.0584015f*(x*x*y - y*y*x);
}

static f32 COSP(f32 x) {
	x *= 0.3183099f;
	i32 f = (i32)(x + 0.5f);
	f32 n = x - (f32)f;
	return (1 + f%2*~1)*(1 + (3.65278f*n*n - 4.90704f)*n*n);
}

static f32 EXP(f32 x) {
	x = x/1024 + 1;
	x *= x;
	x *= x;
	x *= x;
	x *= x;
	x *= x;
	x *= x;
	x *= x;
	x *= x;
	x *= x;
	x *= x;
	return x;
}

static f32 LOG2(f32 x)	// compute LOG2(x) by reducing x to [0.75, 1.5)
{
	// a*(x-1)^2 + b*(x-1) approximates LOG2(x) when 0.75 <= x < 1.5
	const f32 a = -0.6296735f;
	const f32 b = +1.466967f;
	f32 signif, fexp;
	i32 exp;
	f32 lg2;
	union { f32 f; u32 i; } ux1, ux2;
	i32 greater; // really a boolean 
	/* 
	 * Assume IEEE representation, which is sgn(1):EXP(8):frac(23)
	 * representing (1+frac)*2^(exp-127)	Call 1+frac the significand
	 */

	// get exponent
	ux1.f = x;
	exp = (ux1.i & 0x7F800000) >> 23; 
	// actual exponent is exp-127, will subtract 127 later

	greater = ux1.i & 0x00400000;	// true if signif > 1.5
	if (greater) {
		// signif >= 1.5 so need to divide by 2.	Accomplish this by 
		// stuffing exp = 126 which corresponds to an exponent of -1 
		ux2.i = (ux1.i & 0x007FFFFF) | 0x3f000000;
		signif = ux2.f;
		fexp = exp - 126;		// 126 instead of 127 compensates for division by 2
		signif = signif - 1.0;	// <
		lg2 = fexp + a*signif*signif + b*signif;	// <
	} else {
		// get signif by stuffing exp = 127 which corresponds to an exponent of 0
		ux2.i = (ux1.i & 0x007FFFFF) | 0x3f800000;
		signif = ux2.f;
		fexp = exp - 127;
		signif = signif - 1.0;	// <<--
		lg2 = fexp + a*signif*signif + b*signif;	// <<--
	}
	// lines marked <<-- are common code, but optimize better 
	//	when duplicated, at least when using gcc
	return(lg2);
}

#endif
