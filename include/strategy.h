/*FT tiene un IProcessBehavior del cual se hereda DFT e IDFT
en main se instancia FT, y luego de procesar lo ingresado por usuario se setea que clase es _pb
ej: _pb = new DFT ( input , output )
*/
#ifndef _STRATEGY_H_INCLUDED_
#define  _STRATEGY_H_INCLUDED_


#include "Complex.h"
#include "Vector.h"

class IProcessBehavior;

class FT{

	IProcessBehavior* _pb;
	size_t chosen_method;
	size_t NumberOfMethods=2;
public:

	enum StrategyType
	{
		DFT_method, IDFT_method
	};

	FT()
	{
		_pb = NULL;
	}

	~FT() {}

	bool
	SetFT(size_t method)
	{
		if(chosen_method>NumberOfMethods)
			return false;
		delete _pb;
		if(method == DFT_method)
			_pb = new DFT;
		if(method == IDFT_method)
			_pb = new IDFT;
		return true;
	}

	void 
	run()
	{
		_pb -> process();
	}
};

class IProcessBehavior{

	IProcessBehavior() = 0;
	coefficient(ComplexVector const & input, ComplexVector & output) = 0 ;

public:
	~IProcessBehavior( _pb )
	{
		delete _pb;
		_pb = NULL;
	} 
	bool
	transform( ComplexVector const & input, ComplexVector & output )
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


};


class DFT : public IProcessBehavior {

public:
	DFT() { }
	
	~IDFT( _pb ) 
	{
		delete _pb;
		_pb = NULL;
	}

	inline const Complex <>
	coefficient( int const i, int const j, int const n )
	{
		return exp(I * -2.0 * M_PI * i * j / n)
	}
};

class IDFT : public IProcessBehavior {

public:
	
	IDFT() { }

	~IDFT( _pb ) 
	{
		delete _pb;
		_pb = NULL;
	}

	inline const Complex <>
	coefficient( int const i, int const j, int const n )
	{
		return exp(I * -2.0 * M_PI * i * j / n);
	}
};


#endif