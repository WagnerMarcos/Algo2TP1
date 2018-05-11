#include <iostream>
#include <cmath>

#include "DFT.h"

namespace DFT {

	bool
	transform(ComplexVector const & input, ComplexVector & output, TransformType const & method)
	{
		size_t n = input.size();
		output.reserve(n);
		Complex <> sum = 0;
		for (size_t i = 0; i < n; ++i) {
			for (size_t j = 0; j < n; ++j) {
				sum += input[j] * coefficient(i, j, n, method);
			}
			output.push_back(sum);
			sum = 0;
		}
		return true;
	}

	inline const Complex <>
	coefficient(int const i, int const j, int const n, TransformType const & method)
	{
		switch (method) {
			case TransformType::DFT:
				return exp(I * -2.0 * M_PI * i * j / n);
			case TransformType::IDFT:
				return exp(I * 2.0 * M_PI * i * j / n) / n;
			default:
				return 0;
		}
	}

}
