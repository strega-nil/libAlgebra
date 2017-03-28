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

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <ctype.h>
#include "mal.h"

/** INTERNAL: Initializes a null matrix, in case of error.
 *  Return this matrix if any errrors occur.
 *  Usually materr(1) means initialization error, materr(2)
 *  means that the operation is allowed.
 */
matrix materr(int err)
{
	matrix mx = {err, 0, NULL};
	return mx;
}

/** INTERNAL: Initializes a matrix, with x rows and y columns.
 *  Mallocs the matrix, then initializes all the numbers inside
 *  to zero. If the x or y values are impossible, returns materr(1).
 */
matrix initialize(int x, int y)
{
	if(x < 1 || y < 1){
		return materr(1);
	}
	matrix mx;
	mx.rows = x;
	mx.columns = y;
	// Initial Array
	mx.mx = malloc(sizeof(frac*) * mx.rows);
	// Internal Arrays
	for ( int i = 0; i < mx.rows; i++)
		mx.mx[i] = malloc(sizeof(frac) * mx.columns);
	// Initialize numbers
	for ( int row = 0; row < mx.rows; row++)
		for ( int col = 0; col < mx.columns; col++)
			mx.mx[row][col] = i2f(0);
	return mx;
}


/** INTERNAL: Tests if a matrix algebra operation is allowable.
 *  Returns true if yes, false if no.
 */
bool isValidOp(matrix m1, matrix m2, char op)
{
	switch (op){
		// multiply
		case 'm':
			if ( m1.columns == m2.rows )
				return true;
			else
				return false;
			break;

		// add or subtract
		case 'a':
		case 's':
			if (m1.columns == m2.columns
			    && m1.rows == m2.rows)
				return true;
			else
				return false;
			break;

		// inverse
		case 'i':
			if(m1.rows == m1.columns)
				return true;
			else
				return false;
			break;
		default:
			return false;
	}
}

/** Initializes a matrix using a string.
 *  The string should be of the form [a,b,c][d,e,f][g,h,i] for
 *  the matrix [a, b, c]
 *             [d, e, f]
 *             [g, h, i]
 */
matrix MatrixInit(char* string)
{
	frac num;
	int rows = 0;
	int cols = 0;

	// amount of rows
	for(int i = 0;; i++) {
		if(string[i] == '\0'){
			break;
		}
		if(string[i] == '['){
			rows = rows + 1;
		}
	}

	// amount of columns
	for(int i = 0;; i++) {
		if(string[i] == ']'){
			break;
		}
		if(string[i] == '[' || string[i] == ','){
			cols = cols + 1;
		}
	}

	matrix mx = initialize(rows, cols);
	if (mx.mx == NULL){
		return materr(1);
	}

	// Putting the numbers where they belong
	int x = 0, y = 0;
	while(true) {
		string = string + 1;

		if(string[0] == '\0'){
			break;
		}

		// Dealing with numbers longer than one char
		while(isdigit(string[-1])){
			if(isdigit(string[0])){
				string = string + 1;
			} else {
				break;
			}
		}

		if(isdigit(string[0])){
			if(x >= cols) {
				x = 0;
				y = y + 1;
			}

			if(y >= rows) {
				break;
			}

			num = i2f(atoi(string));

			mx.mx[y][x] = num;
			x = x + 1;
		}
	}

	return mx;
}

/** Prints a matrix.
 *  Looks like:
 *  [ a, b, c ]
 *  [ d, e, f ]
 *  [ g, h, i ]
 */
int MatrixPrint(matrix mx)
{
	for(int row = 0; row < mx.rows; row++){
		printf("[ ");

		for(int col = 0; col < mx.columns; col++) {
			printf("%s ", f2s(mx.mx[row][col]));
		}

		printf("]\n");
	}
	return 0;
}


/** Adds two matrices.
 *  Returns materr(2) if the two matrices can't
 *  be added, materr(1) if the initialization
 *  didn't go right.
 */
matrix MatrixAdd(matrix m1, matrix m2)
{
	if (!isValidOp(m1,m2,'a')){
		return materr(2);
	}

	matrix mx = initialize(m1.rows, m1.columns);
	if (mx.mx == NULL){
		return materr(1);
	}

	for(int row = 0; row < mx.rows; row++)
		for(int col = 0; col < mx.columns; col++)
			mx.mx[row][col] = fadd(m1.mx[row][col], m2.mx[row][col]);
	return mx;
}


/** Subtracts m2 from m1.
 *  Returns materr(2) if m2 can't be subtracted
 *  from m1, materr(1) if the initialization
 *  didn't go right.
 */
matrix MatrixSub(matrix m1, matrix m2)
{
	if (!isValidOp(m1,m2,'s')){
		return materr(2);
	}

	matrix mx = initialize(m1.rows, m1.columns);
	if (mx.mx == NULL){
		return materr(1);
	}

	for(int row = 0; row < mx.rows; row++){
		for(int col = 0; col < mx.columns; col++){
			mx.mx[row][col] = fadd(m1.mx[row][col], m2.mx[row][col]);
		}
	}
	return mx;
}


/** Multiplies mx by f.
 *  Returns materr(1) if the initialization
 *  of sc didn't go right.
 */
matrix MatrixSMul(matrix mx, frac f)
{
	matrix sc = initialize(mx.columns, mx.columns);
	if (sc.mx == NULL){
		return materr(1);
	}

	for(int i = 0; i < mx.columns; i++){
		sc.mx[i][i] = f;
	}

	return MatrixMul(mx, sc);
}


/** Multiplies m1 by m2.
 *  Returns materr(2) if the two matrices can't
 *  be multiplied, materr(1) if the initialization
 *  didn't go right.
 */
matrix MatrixMul(matrix m1, matrix m2)
{
	if (!isValidOp(m1,m2,'m')){
		return materr(2);
	}

	matrix mx = initialize(m1.rows, m2.columns);
	if (mx.mx == NULL){
		return materr(1);
	}

	for(int row = 0; row < mx.rows; row++){
		for(int col = 0; col < mx.columns; col++){
			for(int i = 0; i < m1.columns; i++){
				mx.mx[row][col] = fadd(mx.mx[row][col], fmul(m1.mx[row][i], m2.mx[i][col]));
			}
		}
	}
	return mx;
}


/** Inverses mx.
 *  Returns materr(2) if mx isn't a square, 2x2 matrix,
 *  or materr(1) if the initialization didn't go right.
 */
matrix MatrixInv(matrix mx)
{
	if (!isValidOp(mx,mx,'i')){
		return materr(2);
	}

	if(mx.rows == 2){

		matrix inv = initialize(mx.rows, mx.columns);
		if(inv.mx == NULL){
			return materr(1);
		}

		frac tmp;
		frac det = fdiv(i2f(1),
		                fsub(fmul(mx.mx[0][0], mx.mx[1][1]),
		                     fmul(mx.mx[0][1], mx.mx[1][0])));

		tmp = mx.mx[0][0];
		inv.mx[0][0] = mx.mx[1][1];
		inv.mx[1][1] = tmp;

		inv.mx[0][1] = fmul(mx.mx[0][1], i2f(-1));
		inv.mx[1][0] = fmul(mx.mx[1][0], i2f(-1));
		return MatrixSMul(mx, det);
	} else {
		return materr(2);
	}
}


/** Frees a matrix.
 */
int MatrixFree(matrix mx)
{
	for(int i = 0; i < mx.rows; i++){
		free(mx.mx[i]);
	}
	free(mx.mx);
	return 0;
}
