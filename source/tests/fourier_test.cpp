#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <limits>
#include <gtest/gtest.h>

#include "fourier_test.h"

using ComplexVector = Vector <Complex <long double> >;

using namespace std;

#define PRINT(X) \
	std::cerr << #X << ": " << X << std::endl

static char *program_name;
static size_t vectorSize;
static const size_t file_amount = 28;
static FourierTransform* ft;
static FourierTransform* ift;
static const string test_files[file_amount] = {
	"testfiles/Frecuencia1.txt",
	"testfiles/TFrecuencia1.txt",
	"testfiles/Frecuencia1B.txt",
	"testfiles/TFrecuencia1B.txt",
	"testfiles/Frecuencia2.txt",
	"testfiles/TFrecuencia2.txt",
	"testfiles/Frecuencia2B.txt",
	"testfiles/TFrecuencia2B.txt",
	"testfiles/Frecuencia3.txt",
	"testfiles/TFrecuencia3.txt",
	"testfiles/Frecuencia3B.txt",
	"testfiles/TFrecuencia3B.txt",
	"testfiles/Frecuencia4.txt",
	"testfiles/TFrecuencia4.txt",
	"testfiles/Frecuencia4B.txt",
	"testfiles/TFrecuencia4B.txt",
	"testfiles/Frecuencia5.txt",
	"testfiles/TFrecuencia5.txt",
	"testfiles/Frecuencia5B.txt",
	"testfiles/TFrecuencia5B.txt",
	"testfilees/Pulso.txt",
	"testfilees/TPulso.txt",
	"testfilees/PulsoB.txt",
	"testfilees/TPulsoB.txt",
	"testfilees/dwavfs11025.txt",
	"testfilees/Tdwavfs11025.txt",
	"testfilees/gwavfs11025.txt",
	"testfilees/Tgwavfs11025.txt"
};

static option_t options[] = {
	{1, "n", "number", DEFAULT_AMOUNT, opt_number, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static void
opt_number(std::string const &arg)
{
	std::istringstream iss(arg);

	if (!(iss >> vectorSize) || !iss.eof()) {
		std::cerr << "Not a possible amount: "
		     << arg
		     << "."
		     << std::endl;
		exit(1);
	}
	if (iss.bad()) {
		std::cerr << "Cannot read amount."
		     << std::endl;
		exit(1);
	}
}

static void
opt_help(std::string const &arg)
{
	std::cerr << program_name << " [-n amount]"
				 << std::endl;
	exit(0);
}

// Google Test exige que las pruebas estén en un namespace sin nombre
//
namespace {
	class RandomVectors : public ::testing::Test {
	protected:
		RandomVectors() : OrigVector(vectorSize),
		                  FTVector(vectorSize),
		                  FinalVector(vectorSize)
		{
			cerr << "Esta prueba crea un vector de "
			     << vectorSize
			     << " números complejos pseudo-aleatorios "
			     << "(la cantidad de elementos puede ser cambiada llamando "
			     << program_name
			     << " -n <cantidad>). "
			     << endl
			     << "Luego le aplica la DFT, y al vector "
			     << "resultante le aplica la IDFT, "
			     << "mediante las funciones utiizadas en el TP. "
			     << endl
			     << "Por último, comprueba que el vector y la antitransformada de "
			     << "su transformada sean iguales."
			     << endl;
			srand(time(NULL));
			for (size_t i = 0; i < vectorSize; ++i) {
				long double randA = rand() * rand() * 10000;
				long double randB = rand() * rand() * 10000;
				OrigVector.push_back(Complex <long double>(randA, randB));
			}
		}
		~RandomVectors() {
			cerr << endl;  // por razones de formato de la impresión
		}
		ComplexVector OrigVector;
		ComplexVector FTVector;
		ComplexVector FinalVector;
	};

	class VectorsFromFiles : public ::testing::Test {
	protected:
		VectorsFromFiles() : i(0) {
			cerr << "Esta prueba lee vectores y sus transformadas de archivos de prueba "
			     << "y luego las compara a los valores obtenidos al aplicarle "
				  << "la función DFT() e IDFT() usadas en el código del TP."
				  << endl
				  << "Se considera que dos números son iguales si su diferencia es menor o igual a "
			     << Complex_acceptableDelta
				  << endl;
		}
		void read_vectors_from_files() {
			ifs.open(test_files[i], ios::in);
			if (!load_signal(ifs, *originalVector))
				exit(1);
			ifs.close();
			++i;
			ifs.open(test_files[i], ios::in);
			if (!load_signal(ifs, *transformedVector))
				exit(1);
			ifs.close();
			++i;
		}
		~VectorsFromFiles() {
			cerr << endl;  // por razones de formato
		}
		size_t i;
		ifstream ifs;
		ComplexVector *originalVector;
		ComplexVector *transformedVector;
		ComplexVector *FTOutput;
		ComplexVector *IFTOutput;
	};

	TEST_F(RandomVectors, DFTandIDFT) {
		ft->compute(OrigVector, FTVector);
		ift->compute(FTVector, FinalVector);
		for (size_t i = 0; i < vectorSize; ++i)
			EXPECT_EQ(OrigVector[i], FinalVector[i]);
	}

	TEST_F(VectorsFromFiles, DFTandIDFT) {
		while (i < file_amount) {
			originalVector = new ComplexVector;
			transformedVector = new ComplexVector;
			FTOutput = new  ComplexVector;
			IFTOutput = new ComplexVector;
			read_vectors_from_files();	
			if (!ft->compute(*originalVector, *FTOutput))
				exit(1);
			for (size_t j = 0 ; j < originalVector->size(); ++j)
				EXPECT_EQ((*transformedVector)[j], (*FTOutput)[j]);
			if (!ift->compute(*transformedVector, *IFTOutput))
				exit(1);
			for (size_t j = 0 ; j < originalVector->size(); ++j)
				EXPECT_EQ((*originalVector)[j], (*IFTOutput)[j]);
			delete transformedVector; 
			delete FTOutput;
			delete originalVector;
			delete IFTOutput;
			cerr << test_files[i]
			     << " fue procesado."
			     << endl;
		}
	}

}  // namespace

int main(int argc, char **argv) {
	program_name = argv[0];
	cmdline cmdl(options);
	cmdl.parse(argc, argv);

	DFT dft;
	IDFT idft;
	FFT fft;
	IFFT ifft;

	::testing::InitGoogleTest(&argc, argv);

	cerr << "Pruebas para la DFT e IDFT: " << endl;
	ft = new FourierTransform(&dft);
	ift = new FourierTransform(&idft);
	RUN_ALL_TESTS();
	delete ft;
	delete ift;
/*
	cerr << "Pruebas para la FFT e IFFT: " << endl;
	ft = new FourierTransform(&fft);
	ift = new FourierTransform(&ifft);
	RUN_ALL_TESTS()
	delete ft;
	delete ift;
*/
	return 0;
}