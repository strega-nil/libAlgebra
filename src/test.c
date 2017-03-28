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

#include "mal.h"
#include <stdio.h>

int exp(int b, int ex){
	int ret = 1;
	for(int i = 0; i < ex; i++){
		ret = ret * b;
	}

	return ret;
}

int testInit()
{
	/* Test MatrixInit */
	matrix m1 = MatrixInit("[0,1,2][3,4,5][6,7,8]");

	if(m1.mx == NULL){
		puts("MatrixInit(): NOT ALLOCATED");
		return 0;
	} else {
		puts("MatrixInit(): Allocation: SUCCESS");
	}

	if(m1.rows != 3){
		printf("MatrixInit(): ROWS INCORRECT: %d\n", m1.rows);
	}
	if(m1.columns != 3){
		printf("MatrixInit(): COLUMNS INCORRECT: %d\n", m1.columns);
	}
	if(m1.rows == 3 && m1.columns == 3){
		puts("MatrixInit(): Columns and Rows: SUCCESS");
	} else {
		return 0;
	}

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(!feq(m1.mx[i][j], i2f(i * 3 + j) )){
				printf("MatrixInit(): INCORRECT NUMBERS: mx[%d][%d]\n", i, j);
				return 0;
			}
		}
	}

	puts("MatrixInit(): SUCCESS");

	/* Test Matrix Init with Multiple Char Numbers */
	matrix m2 = MatrixInit("[1,10,100][1000,10000,100000][1000000,10000000,100000000]");

	if(m2.mx == NULL){
		puts("MatrixInit(mchar): NOT ALLOCATED");
		return 0;
	} else {
		puts("MatrixInit(mchar): Allocation: SUCCESS");
	}

	if(m2.rows != 3){
		printf("MatrixInit(mchar): ROWS INCORRECT: %d\n", m2.rows);
	}
	if(m2.columns != 3){
		printf("MatrixInit(mchar): COLUMNS INCORRECT: %d\n", m2.columns);
	}
	if(m2.rows == 3 && m1.columns == 3){
		puts("MatrixInit(mchar): Columns and Rows: SUCCESS");
	} else {
		return 0;
	}

	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			if(fneq(m2.mx[i][j], i2f( exp(10, (i * 3) + j) ))){
				printf("MatrixInit(mchar): INCORRECT NUMBERS: mx[%d][%d]\n", i, j);
				return 0;
			}
		}
	}

	puts("MatrixInit(mchar): SUCCESS");
	return 1;
}

int testArith()
{
	return 0;
}

int main()
{
	if(!testInit()){
		return 0;
	}
	return 0;
}
