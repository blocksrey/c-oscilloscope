#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"
#include "zeromath/trig.h"
#include "zeromath/prim.h"

#define W 800
#define H 600

static f32 pixels[W*H];

typedef struct vec2 {
	f32 x;
	f32 y;
} vec2;

#define get_pixel(x, y) pixels[x + W*(y)]
#define lengthof(a) (sizeof a/sizeof *a)
#define DOT(x0, y0, x1, y1) ((x0)*(x1) + (y0)*(y1))
#define DD(x0, y0) ((x0)*(x0) + (y0)*(y0))

int main() {
	//*
	vec2 points[] = {
		(vec2){453,98},
		(vec2){793,94},
		(vec2){988,256},
		(vec2){984,532},
		(vec2){788,719},
		(vec2){449,713},
		(vec2){300,493},
		(vec2){321,264},
		(vec2){449,98},
		(vec2){516,312},
		(vec2){505,304},
		(vec2){495,300},
		(vec2){472,297},
		(vec2){451,310},
		(vec2){438,321},
		(vec2){436,337},
		(vec2){436,354},
		(vec2){453,369},
		(vec2){484,375},
		(vec2){505,384},
		(vec2){520,400},
		(vec2){520,432},
		(vec2){501,461},
		(vec2){488,465},
		(vec2){451,463},
		(vec2){430,449},
		(vec2){430,446},
		(vec2){570,304},
		(vec2){602,304},
		(vec2){621,306},
		(vec2){635,306},
		(vec2){650,306},
		(vec2){671,304},
		(vec2){627,312},
		(vec2){625,337},
		(vec2){625,354},
		(vec2){627,384},
		(vec2){627,423},
		(vec2){623,444},
		(vec2){623,457},
		(vec2){770,302},
		(vec2){755,302},
		(vec2){736,316},
		(vec2){723,333},
		(vec2){721,354},
		(vec2){721,377},
		(vec2){732,409},
		(vec2){740,428},
		(vec2){755,446},
		(vec2){761,453},
		(vec2){780,446},
		(vec2){791,425},
		(vec2){791,411},
		(vec2){795,384},
		(vec2){791,352},
		(vec2){786,325},
		(vec2){786,318},
		(vec2){837,302},
		(vec2){835,314},
		(vec2){835,333},
		(vec2){835,356},
		(vec2){837,388},
		(vec2){843,428},
		(vec2){837,484},
		(vec2){845,453},
		(vec2){837,417},
		(vec2){843,297},
		(vec2){849,295},
		(vec2){868,293},
		(vec2){889,289},
		(vec2){896,308},
		(vec2){904,321},
		(vec2){904,335},
		(vec2){881,356},
		(vec2){866,363},
		(vec2){860,363},
	};
	//*/

	usize N = lengthof(points);

	vec2 L = (vec2){+10000000, +10000000};
	vec2 U = (vec2){-10000000, -10000000};

	for (usize i = N; i--;) {
		L.x = MIN(points[i].x, L.x);
		L.y = MIN(points[i].y, L.y);
		U.x = MAX(points[i].x, U.x);
		U.y = MAX(points[i].y, U.y);
	}

	for (usize i = N; i--;) {
		points[i].x -= (L.x + U.x)/2;
		points[i].y -= (L.y + U.y)/2;

		points[i].x *= 2*H/(U.y - L.y)/3;
		points[i].y *= 2*H/(U.y - L.y)/3;

		points[i].x += W/2;
		points[i].y += H/2;
	}

	i32 ox, oy;

	f32 R = 5;
	f32 pr = PI*R; // pi*radius
	f32 time = 0.0f;

	#define move(px, py) i32 dx = ox - px; i32 dy = oy - py; ox = px; oy = py

	usize uhh = 0;

	for (usize f = 0; f < 4*N; ++f) {
		move(points[uhh].x, points[uhh].y);

		++uhh;
		uhh %= N;

		for (usize p = W*H; p--;) {
			i32 px = p%W;
			i32 py = p/W;

			f32 l = SQRT(dx*dx + dy*dy);
			f32 ux = dx/l;
			f32 uy = dy/l;
			f32 t = CLMP(DOT(ux, uy, px - ox, py - oy), 0, l);
			f32 b = 10/MAX(1, l)/POW(DD(ox + t*ux - px, oy + t*uy - py), 0.66666666);

			get_pixel(px, py) += b;
			get_pixel(px, py) *= 0.98f;
		}

		write_ppm(pixels, W, H);
	}

	return 0;
}
