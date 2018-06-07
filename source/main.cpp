#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdlib>

#include "main.h"

using namespace std;

static option_t options[] = {
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
	{1, "m", "method", "FFT", opt_method, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static char *program_name;
static FourierAlgorithm *chosen_method;
static FourierTransform *transform;
static istream *iss = NULL;
static ostream *oss = NULL;
static fstream ifs;
static fstream ofs;

static void
opt_input(string const &arg)
{
	if (arg == "-") {
		iss = &cin;
	}
	else {
		ifs.open(arg.c_str(), ios::in);
		iss = &ifs;
	}

	if (!iss->good()) {
		cerr << "Cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_output(string const &arg)
{
	if (arg == "-") {
		oss = &cout;
	} else {
		ofs.open(arg.c_str(), ios::out);
		oss = &ofs;
	}

	if (!oss->good()) {
		cerr << "Cannot open "
		     << arg
		     << "."
		     << endl;
		exit(1);
	}
}

static void
opt_method(string const &arg)
{
	istringstream iss(arg);
	string read_method;

	if (!(iss >> read_method) || iss.bad()) {
		cerr << "Cannot read method."
		     << endl;
		exit(1);
	}
	if (read_method == "FFT")
		chosen_method = new FFT;
	else if (read_method == "IFFT")
		chosen_method = new IFFT;
	else if (read_method == "DFT")
		chosen_method = new DFT;
	else if (read_method == "IDFT")
		chosen_method = new IDFT;
	else {
		cerr << "Not a posible method: "
		     << arg
		     << "."
		     << endl;
		opt_help();
	   exit(1);
	}
	::transform = new FourierTransform(chosen_method);
}

static void
opt_help(string const & arg)
{
	cout << "Usage: "
	     << program_name
	     << " [-m FFT | IFFT | DFT | IDFT] [-i file] [-o file]"
	     << endl;
	exit(0);
}

static void
print_msg_and_exit(string const & msg)
{
	cerr << msg
	     << endl;
	delete chosen_method;
	delete ::transform;
	chosen_method = nullptr;
	::transform = nullptr;
	exit(1);
}

int
main(int argc, char * const argv[])
{
	program_name = argv[0];
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	// Cuestiones de formato para la impresión:
	oss->setf(ios::fixed, ios::floatfield);
	oss->precision(6);

	bool status;
	ComplexVector inSignal;
	ComplexVector outSignal;
	istringstream line;
	string s;

	for (int lineNo = 1; getline(*iss, s); ++lineNo)
	{
		if (iss->bad())
			print_msg_and_exit("An error occured while processing line " + to_string(lineNo) + ".");
		
		line.str(s); // 
		line.clear();

		status = load_signal(line, inSignal);
		if (!status)
			print_msg_and_exit("Error processing \"" + line.str() + "\" (line " + to_string(lineNo) + ").");

		status = ::transform->compute(inSignal, outSignal);
		if (!status)
			print_msg_and_exit("An error occured while performing the requested operation.");

		status = print_signal(*oss, outSignal);
		if (!status) 
			print_msg_and_exit("Cannot write to output stream.");
		inSignal.clear();
		outSignal.clear();
	}
	delete chosen_method;
	delete ::transform;
	chosen_method = nullptr;
	::transform = nullptr;
}
