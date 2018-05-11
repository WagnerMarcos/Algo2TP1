#ifndef _DFT_H_INCLUDED_
#define  _DFT_H_INCLUDED_

#include "Complex.h"
#include "Vector.h"

namespace DFT {
	typedef Vector <Complex <> > ComplexVector;
	enum class TransformType { DFT, IDFT };
	bool transform(ComplexVector const &, ComplexVector &, TransformType const & = TransformType::DFT);
	const Complex <> coefficient(int const i, int const j, int const n, TransformType const & method = TransformType::DFT);
}

#endif	// _DFT_H_INCLUDED_
