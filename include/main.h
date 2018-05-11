#ifndef _MAIN_H_INCLUDED_
#define _MAIN_H_INCLUDED_

#include "cmdline.h"
#include "Complex.h"
#include "Vector.h"
#include "DFT.h"
#include "io.h"

static void opt_input(std::string const &);
static void opt_output(std::string const &);
static void opt_method(std::string const &);
static void opt_help(std::string const &);
static void print_msg_and_exit(std::string const &);

#endif	// _MAIN_H_INCLUDED_
