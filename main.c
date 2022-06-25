#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "int.h"
#include "ppm.h"

#define W 600
#define H 400

#define PI 3.1415927f
#define TAU 6.2831853f

static float pixels[W*H][3];

#define SET_PIXEL(x, y, g) pixels[x + W*(y)][1] = g
#define ADD_PIXEL(x, y, g) pixels[x + W*(y)][1] += g
#define MUL_PIXEL(x, y, g) pixels[x + W*(y)][1] *= g
#define DIV_PIXEL(x, y, g) pixels[x + W*(y)][1] /= g
#define LENGTH(a) (sizeof(a)/sizeof(*a))
#define DOT(x0, y0, x1, y1) ((x0)*(x1) + (y0)*(y1))
#define DD(x0, y0) ((x0)*(x0) + (y0)*(y0))
#define CLAMP(n, a, b) fmaxf(a, fminf(n, b))

/*
static float isqrt(float n) {
	const float x = 0.5f*n;
	const float t = 1.5f;
	union {
		float f;
		u32 i;
	} c = {.f = n};
	c.i = 0x5f3759df - (c.i >> 1);
	c.f *= t - x*c.f*c.f;
	return c.f;
}
*/

/*
static void line(
	u16 *o,
	s16 *d
) {
	u16 ox = o[0];
	u16 oy = o[1];

	s16 dx = d[0];
	s16 dy = d[1];

	float i = isqrt(dx*dx + dy*dy);

	for (float u = 0; u < 1; u += i) {
		SET_PIXEL(
			ox + (s16)(dx*u),
			oy + (s16)(dy*u),
			255
		);
	}
}
*/

typedef struct {
	float a;
	float p;
} fti;

static void dft(u16 n, float *v, fti *o) {
	for (u16 f = 0; f < n; ++f) {
		int x = 0;
		int y = 0;

		for (u16 i = 0; i < n; ++i) {
			x += v[i]*cosf(TAU/n*(float)f*(float)i);
			y -= v[i]*sinf(TAU/n*(float)f*(float)i);
		}

		x /= n;
		y /= n;

		o[f].a = sqrtf(x*x + y*y);
		o[f].p = atan2f(y, x);
	}
}

static float dc(u16 n, fti *o, float t, float x) {
	for (u16 f = 0; f < n; ++f)
		x += o[f].a*cosf(f*t + o[f].p);

	return x;
}

/*
function dft(x) {
  const X = [];
  const N = x.length;

  for (let f = 0; f < N; ++f) {
    let re = 0;
    let im = 0;

    for (let n = 0; n < N; ++n) {
      re += x[n]*cos(TWO_PI/N*f*n);
      im -= x[n]*sin(TWO_PI/N*f*n);
    }

    re /= N;
    im /= N;

    let a = sqrt(re*re + im*im);
    let p = atan2(im, re);
  
    X[f] = {re, a, p};
  }
  
  return X;
}

function setup() {
  createCanvas(500, 500);
  
  x = [];
  y = [];
  time = 0;
  
  for (let i = 0; i < drawing.length; i += 10) {
    x.push(drawing[i].x);
    y.push(drawing[i].y);
  }

  fx = dft(x);
  fy = dft(y);
}

function dc(t, x, time) {
  for (let f = 0; f < t.length; ++f)
    x += t[f].a*cos(f*time + t[f].p);
  return x;
}

let x1, y1;

function draw() {
  stroke(0, 255, 0);
  background(0);
  
  x0 = x1;
  y0 = y1;
  
  x1 = dc(fx, width/2, time);
  y1 = dc(fy, height/2, time);
  
  line(x0, y0, x1, y1);

  time += TWO_PI/fx.length;
}
*/

int main() {
	/*
	int POINTS[] = {
		94,302,
		111,289,
		130,276,
		151,270,
		165,256,
		172,232,
		178,214,
		174,193,
		169,174,
		174,159,
		197,157,
		201,169,
		199,190,
		193,197,
		169,178,
		165,157,
		165,136,
		167,115,
		176,96,
		186,83,
		214,75,
		230,71,
		256,71,
		274,75,
		295,88,
		312,98,
		325,104,
		329,113,
		300,113,
		276,113,
		247,117,
		285,115,
		314,121,
		321,134,
		321,146,
		318,157,
		321,176,
		333,180,
		358,172,
		375,157,
		377,142,
		365,121,
		348,117,
		321,117,
		314,128,
		318,151,
		316,169,
		312,176,
		302,172,
		304,180,
		308,188,
		304,195,
		306,209,
		291,211,
		274,209,
		279,197,
		287,195,
		270,176,
		253,169,
		266,161,
		276,167,
		285,155,
		268,153,
		249,153,
		266,153,
		281,155,
		279,167,
		270,180,
		272,193,
		270,209,
		300,203,
		306,216,
		304,228,
		300,222,
		283,222,
		262,224,
		256,232,
		266,243,
		272,260,
		287,256,
		291,247,
		281,241,
		270,235,
		285,241,
		291,247,
		291,260,
		285,268,
		272,281,
		258,279,
		247,272,
		232,268,
		247,274,
		253,285,
		247,300,
		235,297,
		209,293,
		188,283,
		176,276,
		165,268,
		203,289,
		226,302,
		251,304,
		256,314,
		266,329,
		276,346
	};
	*/

	float POINTS[] = {
		453,98,
		793,94,
		988,256,
		984,532,
		788,719,
		449,713,
		300,493,
		321,264,
		449,98,
		516,312,
		505,304,
		495,300,
		472,297,
		451,310,
		438,321,
		436,337,
		436,354,
		453,369,
		484,375,
		505,384,
		520,400,
		520,432,
		501,461,
		488,465,
		451,463,
		430,449,
		430,446,
		570,304,
		602,304,
		621,306,
		635,306,
		650,306,
		671,304,
		627,312,
		625,337,
		625,354,
		627,384,
		627,423,
		623,444,
		623,457,
		770,302,
		755,302,
		736,316,
		723,333,
		721,354,
		721,377,
		732,409,
		740,428,
		755,446,
		761,453,
		780,446,
		791,425,
		791,411,
		795,384,
		791,352,
		786,325,
		786,318,
		837,302,
		835,314,
		835,333,
		835,356,
		837,388,
		843,428,
		837,484,
		845,453,
		837,417,
		843,297,
		849,295,
		868,293,
		889,289,
		896,308,
		904,321,
		904,335,
		881,356,
		866,363,
		860,363

	};

	u16 N = LENGTH(POINTS)/2;

	float xs[N];
	float ys[N];

	float lx =  10000000;
	float ly =  10000000;
	float hx = -10000000;
	float hy = -10000000;

	for (int i = 0; i < N; ++i) {
		xs[i] = POINTS[2*i + 0];
		ys[i] = POINTS[2*i + 1];

		lx = fminf(xs[i], lx);
		ly = fminf(ys[i], ly);
		hx = fmaxf(xs[i], hx);
		hy = fmaxf(ys[i], hy);
	}

	printf("%f %f\n", (double)lx, (double)ly);

	for (int i = 0; i < N; ++i) {
		xs[i] -= (lx + hx)/2;
		ys[i] -= (ly + hy)/2;

		xs[i] *= W/(hx - lx)/2;
		ys[i] *= H/(hy - lx)/2;
	}

	fti fx[N];
	fti fy[N];

	dft(N, xs, fx);
	dft(N, ys, fy);






	//u16 nf = 200;

	float dx;
	float dy;
	//float B  = 5.0f;
	float pr = 5.0f*PI; // pi*radius


	float time = 0;

	float ox = dc(N, fx, time, 0.49f*W);
	float oy = dc(N, fy, time, 0.49f*H);

	char fs[24];

	u16 px, py;

	for (u16 i = 0; i < 3*N; ++i) {
		sprintf(fs, "output/%05d.ppm", i);

		float bx = ox;
		float by = oy;

		time += TAU/N;

		ox = dc(N, fx, time, 0.49f*W);
		oy = dc(N, fy, time, 0.49f*H);

		dx = bx - ox;
		dy = by - oy;

		for (u32 p = 0; p < W*H; ++p) {
			px = p%W;
			py = p/W;
			float l = sqrtf(dx*dx + dy*dy);
			float ux = dx/l;
			float uy = dy/l;
			if (l == 0) {
				ux = 0;
				uy = 0;
			}
			float z = CLAMP(DOT(ux, uy, px - ox, py - oy), 0, l);
			float b = 2*pr/(pr + 2*l)/fmax(1, pow(DD(ox + z*ux - px, oy + z*uy - py), 0.666666));
			ADD_PIXEL(px, py, b);
			MUL_PIXEL(px, py, 0.98f);
		}

		writePPM(pixels, W, H, fs);
	}

	return 0;
}
