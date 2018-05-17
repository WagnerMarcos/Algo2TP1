#include <iostream>
#include <cmath>

#include "fourier.h"


#define PRINT(X) \
	std::cerr << #X << ": " << X << std::endl

bool
Discrete::compute(ComplexVector const & input, ComplexVector & output)
{
	size_t n = input.size();
	output.reserve(n);
	Complex <> sum = 0;
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			sum += input[j] * _coefficient(i, j, n);
		}
		output.push_back(sum);
		sum = 0;
	}
	return true;
}

bool
Fast::compute(ComplexVector const & input, ComplexVector & output)
{
	output.clear();
	output = _compute(input);
	for (size_t i = 0; i < output.size(); ++i)
		output[i] /= _divisor(output.size());
	return true;
}

ComplexVector
Fast::_compute(ComplexVector const & input)
{
	size_t n = input.size();
	if (n <= 1) {
		return ComplexVector(input);
	}

	ComplexVector inputEven(n/2);
	ComplexVector inputOdd(n/2);

	for (size_t i = 0; i < n / 2; ++i) {
		inputEven[i] = input[2 * i];
		inputOdd[i] = input[2 * i + 1];
	}

	ComplexVector outputEven(_compute(inputEven));
	ComplexVector outputOdd(_compute(inputOdd));

	ComplexVector output(n);
	for (size_t k = 0; k < n / 2; ++k){
		output[k] = outputEven[k] + _coefficient(k, n) * outputOdd[k];
		output[k + n/2] = outputEven[k] - _coefficient(k, n) * outputOdd[k];
	}

	return output;
}