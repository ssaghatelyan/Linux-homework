#include <iostream>
#include <vector>
#include "Complex.h"
#include "sort_complex.h"

int main(){
	Complex a(10, 4);
	Complex b(6, 3);
	double cnst = 2;

	Complex c1 = a + b;
	std::cout << "add: " << a << " + " << b << " = " << c1 << "\n";

	Complex c2 = a - b;
        std::cout << "sub: " << a << " - " << b << " = " << c2 << "\n";

	Complex c4 = a * cnst;
        std::cout << "mul by const: " << a << " * " << cnst << " = " << c4 << "\n";

	std::vector<Complex> arr{
		{3, 4}, {1, 1}, {-2, 0}, {0, 0}
	};

	std::cout << "Before sorting:\n";
	for(const auto& x : arr){
		std::cout << x << " (Absolute value = " << x.abs() <<")\n";
	}
	bubbleSortByAbs(arr);
	std::cout << "After sorting:\n";
	for(const auto& x : arr){
		std::cout << x << " (Absolute value = " << x.abs() <<")\n";
	}
}
