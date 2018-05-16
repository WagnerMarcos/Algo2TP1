#ifndef _FOURIER_H_INCLUDED_
#define  _FOURIER_H_INCLUDED_

#include "Complex.h"
#include "Vector.h"

using ComplexVector = Vector <Complex <long double> >;

class FourierAlgorithm {
public:
	virtual bool compute(ComplexVector const & input, ComplexVector & output) = 0;
	virtual ~FourierAlgorithm() {}
};

class FourierTransform {
public:
	FourierTransform(FourierAlgorithm *method) : _method(method) {}
	virtual ~FourierTransform() {}
	inline bool compute(ComplexVector const & input, ComplexVector & output) {
		return _method? _method->compute(input, output) : false;
	}
private:
	FourierAlgorithm *_method;
};

class Discrete : public FourierAlgorithm {
public:
	bool compute(ComplexVector const & input, ComplexVector & output);
protected:
	virtual const Complex<> coefficient(int const i, int const j, int const n) = 0;
};

class DFT : public Discrete {
private:
	inline const Complex <> coefficient(int const i, int const j, int const n) override {
		return exp(I * -2.0 * M_PI * i * j / n);
	}
};

class IDFT : public Discrete {
private:
	inline const Complex <> coefficient(int const i, int const j, int const n) override {
		return exp(I * 2.0 * M_PI * i * j / n) / n;
	}
};

class Fast : public FourierAlgorithm {
public:
	bool compute(ComplexVector const & input, ComplexVector & output);
	bool _compute(Complex <> *, Complex <> *, int n);
protected:
	virtual const Complex <> FFTcoefficient(int const k, int const n)=0;
};

class FFT : public Fast {
public:
	inline const Complex <> FFTcoefficient(int const k, int const n) override {
		Complex<> W( cos(2*M_PI*k / n) , sin(2*M_PI*k / n) );
		return W;
	}
};

class IFFT : public Fast {
public:
	inline const Complex <> FFTcoefficient(int const k, int const n) override {
		Complex <> W( cos(-2*M_PI*k / n) , sin(-2*M_PI*k / n) );
		return W;
	}
};

#endif	// _FOURIER_H_INCLUDED_