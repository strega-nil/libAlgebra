/*
	Frac - FRaction ArithmetiC

	Written in 2013 by Nicole Mazzuca <npmazzuca@gmail.com>

	To the extent possible under law, the author has dedicated all
	copyright and related and neighboring rights to this software
	to the public domain worldwide. This software is distributed
	without any warranty.

	You should have received a copy of the CC0 Public Domain
	Dedication along with this software. If not, see
	<http://creativecommons.org/publicdomain/zero/1.0/>
*/

#ifndef _FRAC_H
#define _FRAC_H

#include <stdbool.h>

#ifndef bool

#define bool int
#define true 1
#define false 0

#endif

typedef struct {
	int num, den;
} frac;

frac   fnew(int num, int den);

frac   i2f(int i);
char*  f2s(frac f);
double f2d(frac f);

frac    fsimp(frac f);

bool    feq(frac f1, frac f2);
bool    fneq(frac f1, frac f2);
bool    fmor(frac f1, frac f2);
bool    fles(frac f1, frac f2);
bool    feqm(frac f1, frac f2);
bool    feql(frac f1, frac f2);

frac   fadd(frac f1, frac f2);
frac   fsub(frac f1, frac f2);
frac   fmul(frac f1, frac f2);
frac   fdiv(frac f1, frac f2);

#endif
