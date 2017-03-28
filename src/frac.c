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

#include <stdio.h>
#include <malloc.h>
#include "frac.h"

/** INTERNAL: Finds the length of a decimal number.
 *
 *  This takes an integer (n), and returns how many chars
 *  a string holding this integer would need (i.e. n = 10
 *  would return 2).
 */
int ilen(int n)
{
	 int i;
	 for(i = 1; n >= 10; i++){
		 n = n / 10;
	 }
	 return i;
}

/** INTERNAL: Changes two fraction dens to the same int.
 *
 *  Takes two fraction pointers, f1 and f2, and changes the
 *  denominators to equal each other, by multiplying the
 *  num/den by the opposite denominator.
 */
int lcf(frac* f1, frac* f2)
{
	if(f1->den == f2->den){
		return 0;
	}

	int d1 = f1->den;
	int d2 = f2->den;

	f1->num = f1->num * d2;
	f1->den = f1->den * d2;

	f2->num = f2->num * d1;
	f2->den = f2->den * d1;

	return 0;
}


/** Takes ints num and den, returns fraction num/den.
 *  This is just an easy way to make a fraction.
 */
frac fnew(int num, int den)
{
	frac f = {num, den};
	return f;
}

// Fraction Casters

/** Takes an int n, returns fraction n/1.
 *  Exactly what it sounds like on the tin
 *  (int to fraction).
 */
frac i2f(int n)
{
	frac f = {n, 1};
	return f;
}

/** Takes a fraction f, returns a string, for printing &c.
 *  If the denominator is 1, it returns a string that
 *  looks like an int. Otherwise, it returns a string,
 *  "num/den".
 */
char* f2s(frac f)
{
	char* str;

	if(f.den == 1){
		str = malloc(sizeof(char) * (ilen(f.num) + 1));
		sprintf(str, "%d", f.num);
	} else {
		str = malloc(sizeof(char) * (ilen(f.num) + ilen(f.den) + 2));
		sprintf(str, "%d/%d", f.num, f.den);
	}

	return str;
}

/** Takes a fraction f, returns a double.
 *  Returns the division of the numerator by the denominator.
 */
double f2d(frac f)
{
	return (double)f.num / f.den;
}

/** Takes a fraction f, simplifies it as far as it can, returns it.
 *  If the numerator is 0, the denominator is set to 1.
 *  Otherwise, it simplifies the fraction as far as it can.
 */
frac fsimp(frac f)
{
	if(f.num == 0){
		f.den = 1;
		return f;
	}

	int lpcf; // largest possible common factor

	if(f.num == f.den){
		f.num = 1;
		f.den = 1;
		return f;
	} else if(f.num > f.den){
		lpcf = f.den;
	} else {
		lpcf = f.num;
	}

	for(int i = lpcf; i > 0; i++){
		if((f.num % i == 0) && (f.den % i == 0)){
			f.num = f.num / i;
			f.den = f.den / i;
		}
	}

	return f;
}

// Fraction Boolean Operators

/** f1 == f2
 */
bool feq(frac f1, frac f2)
{
	lcf(&f1, &f2);
	if(f1.num == f2.num){
		return true;
	} else {
		return false;
	}
}

/** f1 != f2
 */
bool fneq(frac f1, frac f2)
{
	return !(feq(f1, f2));
}

/** f1 > f2
 */
bool fmor(frac f1, frac f2)
{
	lcf(&f1, &f2);

	if(f1.num > f2.num){
		return true;
	} else {
		return false;
	}
}

/** f1 < f2
 */
bool fles(frac f1, frac f2)
{
	return fmor(f2, f1);
}

/** f1 >= f2
 */
bool feqm(frac f1, frac f2)
{
	return !(fmor(f2, f1));
}

/** f1 <= f2
 */
bool feql(frac f1, frac f2)
{
	return !(fmor(f1, f2));
}


// Fraction Arithmetic

/** f1 + f2.
 *  First changes the denominators of f1 and f2
 *  to be equal, then adds the numerators, and finally
 *  returns the answer.
 */
frac fadd(frac f1, frac f2)
{
	lcf(&f1, &f2);

	f1.num = f1.num + f2.num;

	return f1;
}

/** f1 - f2.
 *  First changes the denominators of f1 and f2
 *  to be equal, then subtracts the numerators, and finally
 *  returns the answer.
 */
frac fsub(frac f1, frac f2)
{
	lcf(&f1, &f2);

	f1.num = f1.num - f2.num;

	return f1;
}

/** f1 * f2.
 *  Multiplies the numerators, multiplies the denominators,
 *  and returns the product.
 */
frac fmul(frac f1, frac f2)
{
	f1.num = f1.num * f2.num;
	f1.den = f1.den * f2.den;

	return f1;
}

/** f1 / f2.
 *  Multiplies f1 by the reciprocal of f2.
 *  So it multiplies f1.num by f2.den, and vice versa, then
 *  returns the product.
 */
frac fdiv(frac f1, frac f2)
{
	f1.num = f1.num * f2.den;
	f1.den = f1.den * f2.num;

	return f1;
}
