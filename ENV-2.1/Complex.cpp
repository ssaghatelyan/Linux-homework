#include "Complex.h"
#include <cmath>

Complex::Complex(double r_, double i_) : r(r_), i(i_) {}

double Complex::real() const{
        return r;
}
double Complex::imag() const{
        return i;
}

Complex Complex::operator+(const Complex& o) const {
	return Complex(r+o.r, i+o.i);
}
Complex Complex::operator-(const Complex& o) const {
	return Complex(r-o.r, i-o.i);
}
Complex Complex::operator*(double k) const {
	return Complex(r*k, i*k);
}
double Complex::abs() const {
	return std::sqrt(r*r + i*i);
}
std::ostream& operator<<(std::ostream& os, const Complex& comp){
	os<< "(" <<  comp.real();
	if(comp.imag()>=0){
		os<< " + " << comp.imag() << "i)";
	}
	else{
		os<<" - " << -comp.imag() << "i)";
	}
	return os;
}
