#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>


class Complex{
public:
	Complex(double r = 0, double i = 0 );
	double real() const;
	double imag() const;
	Complex operator+(const Complex& other) const;
	Complex operator-(const Complex& other) const;
	Complex operator*(double cnst) const;
	double abs() const;
	friend std::ostream& operator<<(std::ostream& os, const Complex& c);
private:
	double r, i;
};

#endif
