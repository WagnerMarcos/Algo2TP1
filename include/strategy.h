/*FT tiene un IProcessBehavior del cual se hereda DFT e IDFT
en main se instancia FT, y luego de procesar lo ingresado por usuario se setea que clase es _pb
ej: _pb = new DFT ( input , output )
*/


class IProcessBehavior{

	bool
	transform( ComplexVector const & input, ComplexVector & output )
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


	coefficient() = 0 ;
};

class FT{
	IProcessBehavior* _pb;


public:

	enum StrategyType{
		DFT, IDFT
	};

	FT(){
		_pb = NULL;
	}

	void SetFT( size_t method ){
		delete _pb;
		if(method == DFT)
			_pb = new DFT( input , output );
		if(method == IDFT)
			_pb = new IDFT( input , output );
	
	}

	void run(){
		_pb -> process();
	}


};

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

	class DFT : public IProcessBehavior {

		inline const Complex <>
		coefficient( int const i, int const j, int const n )
		{
			return exp(I * -2.0 * M_PI * i * j / n);
			}
		}
	};

	class IDFT : public IProcessBehavior {
		inline const Complex <>
		coefficient( int const i, int const j, int const n )
		{
			return exp(I * -2.0 * M_PI * i * j / n);
		}
};