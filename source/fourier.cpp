#include <iostream>
#include <cmath>

#include "fourier.h"

bool
Discrete::compute(ComplexVector const & input, ComplexVector & output)
{
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

bool
Fast::compute(ComplexVector const & input, ComplexVector & output)
{
	bool status;
	Complex<>* AuxComplexArray = new Complex<>[input.size()];
	Complex<>* InputAux = new Complex<>[input.size()];

	for(size_t i=0; i<input.size(); i++)	// Para la función recursiva se utiliza arreglos
		InputAux[i] = input[i];				// de complejos, aquí se cargan los datos de 
											// entrada.
	status = _compute(InputAux , AuxComplexArray , input.size());

	for(size_t i=0; i<input.size(); ++i)		// Se carga el arreglo de complejos
		output.push_back(AuxComplexArray[i]);	// resultante al vector de salida.

	delete[] AuxComplexArray;
	delete[] InputAux;

	return status;
}

bool
Fast::_compute(Complex <> * input, Complex <> * output, int n)
{

	if(n==1) {
		output[0]=input[0];
		return true;
	}

	Complex<>* inputEven= new Complex<>[n/2];	//Se crean arreglos de complejos para
	Complex<>* inputOdd= new Complex<>[n/2];	//realizar dividir y conquistar
	Complex<>* outputEven= new Complex<>[n/2];	//Se divide 
	Complex<>* outputOdd= new Complex<>[n/2];

	Complex<> w(1,0);
	Complex<> wn(cos( -2*M_PI / n ), sin( -2*M_PI / n));

	for (int i = 0; i < (n / 2); i++) {
		inputEven[i] = input[2 * i];
		inputOdd[i] = input[2 * i + 1];
	}
	_compute(inputEven, outputEven, n/2);
	_compute(inputOdd, outputOdd, n/2);

	for(int k = 0; k < n/2; ++k){
		output[k] = outputEven[k] + outputOdd[k]* FFTcoefficient(k, n);
		output[k+n/2] = outputEven[k] - (outputOdd[k])* FFTcoefficient(k, n);
	}

	delete[] inputEven;
	delete[] inputOdd;
	delete[] outputEven;
	delete[] outputOdd;

	return true;
}