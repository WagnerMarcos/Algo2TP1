#ifndef _STRATEGY_H_INCLUDED_
#define  _STRATEGY_H_INCLUDED_

#include "Complex.h"
#include "Vector.h"

class FourierTransform {
public:
	FourierTransform(FourierTransform * method) : _method{method} {}
	~FourierTransform() {}
	inline bool compute(ComplexVector const & input, ComplexVector & output) {
		return _method->compute(input, output);
	}
private:
	FourierAlgorithm* _method;
};

class FourierAlgorithm {
public:
	virtual bool compute(ComplexVector const & input, ComplexVector & output) = 0;
protected:
	FourierAlgorithm();
	virtual	~FourierAlgorithm();
}

class Discrete : public FourierAlgorithm {
public:
	Discrete();
	virtual ~Discrete();
	bool compute(ComplexVector const & input, ComplexVector & output);
protected:
	virtual inline const Complex<> coefficient(size_t, size_t) = 0;
};

class DFT : public Discrete {
private:
	inline const Complex <> coefficient(int const i, int const j, int const n) override {
		return exp(I * -2.0 * M_PI * i * j / n)
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
	virtual bool compute(ComplexVector const & input, ComplexVector & output);
protected:
	Fast();
	virtual ~Fast();
};

class FFT : public Fast {
public:
	bool compute(ComplexVector const & input, ComplexVector & output);
};

class IFFT : public Fast {
public:
	bool compute(ComplexVector const & input, ComplexVector & output);
};

#endif