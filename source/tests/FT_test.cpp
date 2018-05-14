#include <iostream>

#include "strategy.h"

using namespace std;

bool Discrete::compute(ComplexVector const & input, ComplexVector & output) {
	size_t n = input.size();
	output.reserve(n);
	Complex <> sum = 0;
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			sum += input[j] * coefficient(i, j, n);
		}
		output.push_back(sum);
		sum = 0;
	}
	return true;
}

int main() {
	FourierTransform transform(new DFT);
	ComplexVector in(4);
	for (int i = 0; i < 4; ++i)
		in[i] = 1;
	cout << "in:" << endl;
	for (int i = 0; i < 4; ++i)
		cout << in[i] << "; " << endl;
	ComplexVector out(4);
	transform.compute(in, out);
	cout << "out:" << endl;
	for (int i = 0; i < 4; ++i)
		cout << out[i] << "; " << endl;
}