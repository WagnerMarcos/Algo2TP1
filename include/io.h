#ifndef _IO_H_INCLUDED_
#define _IO_H_INCLUDED_

#include "Complex.h"
#include "Vector.h"
#include "DFT.h"

bool load_signal(std::istream &, DFT::ComplexVector &);
bool print_signal(std::ostream &, DFT::ComplexVector const &);

#endif	//_IO_H_INCLUDED_
