/*
	MAL - Matrix Arithmetic Library

	Written in 2013 by Nicole Mazzuca <npmazzuca@gmail.com>

	To the extent possible under law, the author has dedicated all
	copyright and related and neighboring rights to this software
	to the public domain worldwide. This software is distributed
	without any warranty.

	You should have received a copy of the CC0 Public Domain
	Dedication along with this software. If not, see
	<http://creativecommons.org/publicdomain/zero/1.0/>
*/

#ifndef _MAL_H
#define _MAL_H

#include "frac.h"

typedef struct {
	int rows, columns;
	frac ** mx;
} matrix;

matrix MatrixInit(char *);
int    MatrixPrint(matrix);
matrix MatrixAdd(matrix, matrix);
matrix MatrixSub(matrix, matrix);
matrix MatrixMul(matrix, matrix);
matrix MatrixSMul(matrix, frac);
matrix MatrixInv(matrix);
int    MatrixFree(matrix);

#endif
