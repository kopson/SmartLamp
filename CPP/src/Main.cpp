#include <iostream>
#include <cstddef>

#include "Log.h"
#include "Matrix.h"
#include "Rational.h"

int main(int argc, char* argv[]) { 

	Matrix<int> m1(2, 2);
	Matrix<int> m2(2, 2);
	Matrix<int> m3 = m1;
	Matrix<int>  m(10, 20);

	std::cout << CNAME(m3) << "=" << m3.print() << std::endl;

	Rational r("1/3");
	Rational r2(1, 3);
	Rational r3;
	r3 = r + r2;
	std::cout << "Hello:  " << CNAME(r3) << "=" << (double) r3 << " reciprocal =" << r3.reciprocal() << " !!" << std::endl;

	return EXIT_SUCCESS;
};