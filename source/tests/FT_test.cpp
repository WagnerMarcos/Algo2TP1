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
  cout << "Probando la jerarquía de clases" << endl;
}