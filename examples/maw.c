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

/*
	src/maw.c - Matrix Arithmetic Wrapper
	This gives an example for how to use the library.
	It probably isn't safe, so don't use it in production code.
	It's also kinda terrible. It doesn't error check AT ALL.
	You can probably use it as just a calculator though...
*/

#include <malloc.h>
#include "../src/frac.h"
#include "../src/mal.h"

char opErr[] = "Invalid Op. Valid operations: 'a'ddition, 's'ubtraction, 'm'ultiplication, s'c'alar multiplication, 'i'nverse.";

char getOp(char * op)
{
	char ch;

	if(op != NULL){
		ch = *op;
	} else {
		ch = getchar();
	}

	while(true){
		switch(ch){
			case 'a':
			case 'A':
				return 'a';
			case 's':
			case 'S':
				return 's';
			case 'm':
			case 'M':
				return 'm';
			case 'i':
			case 'I':
				return 'i';
			case 'c':
			case 'C':
				return 'c';
			default:
				printf("%s\n> ", opErr);
				break;
		}

		/* Clear the stdin buffer */
		while((ch = getchar()) != '\n')
			;

		/* Get the operation */
		ch = getchar();

	}
}

int main(int argc, char ** argv)
{
	char op;
	char mStr[1024];
	matrix ans, m1, m2;
	int sc = 0;

	if(argc > 1){
		op = getOp(argv[1]);
	} else {
		printf("Which operation: ");
		op = getOp(NULL);
	}


	printf("First matrix:\n");
	scanf("%s", mStr);
	m1 = MatrixInit(mStr);

	if(op == 'a' || op == 's' || op == 'm'){
		printf("Second matrix:\n");
		scanf("%s", mStr);
		m2 = MatrixInit(mStr);
	} else if(op == 'c') {
		printf("Scalar multiple:\n");
		scanf("%d", &sc);
	}

	switch(op){
		case 'a':
			ans = MatrixAdd(m1, m2);
			break;
		case 's':
			ans = MatrixSub(m1, m2);
			break;
		case 'm':
			ans = MatrixMul(m1, m2);
			break;
		case 'i':
			ans = MatrixInv(m1);
			break;
		case 'c':
			ans = MatrixSMul(m1, i2f(sc));
			break;
		default:
			printf("Something went very wrong.\n");
			return 1;
	}

	printf("Answer:\n");
	MatrixPrint(ans);

	MatrixFree(m1);
	MatrixFree(ans);
	if(op == 'a' || op == 's' || op == 'm'){
		MatrixFree(m2);
	}

	return 0;
}
