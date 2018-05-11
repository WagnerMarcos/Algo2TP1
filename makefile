CXXFLAGS = -g -Wall -Wpedantic -Wdeprecated -std=c++11 -O3
SRC = source
INCLUDE = include
TESTS = source/tests
GOOGLETEST =  source/tests/googletest
CXXARGS = -I. -iquote $(INCLUDE) -isystem $(GOOGLETEST)/include -pthread

all: fourier.exe Complex_test.exe DFT_test.exe

cmdline.o: $(SRC)/cmdline.cpp $(INCLUDE)/cmdline.h
	$(CXX) $(CXXFLAGS) $(CXXARGS) -c $(SRC)/cmdline.cpp -o cmdline.o

DFT.o: $(SRC)/DFT.cpp $(INCLUDE)/DFT.h $(INCLUDE)/Complex.h $(INCLUDE)/Vector.h
	$(CXX) $(CXXFLAGS) $(CXXARGS) -c $(SRC)/DFT.cpp -o DFT.o

io.o: $(SRC)/io.cpp $(INCLUDE)/io.h $(INCLUDE)/Complex.h $(INCLUDE)/Vector.h $(INCLUDE)/DFT.h
	$(CXX) $(CXXFLAGS) $(CXXARGS) -c $(SRC)/io.cpp -o io.o

main.o: $(SRC)/main.cpp $(INCLUDE)/main.h $(INCLUDE)/io.h $(INCLUDE)/Complex.h $(INCLUDE)/Vector.h $(INCLUDE)/cmdline.h $(INCLUDE)/DFT.h
	$(CXX) $(CXXFLAGS) $(CXXARGS) -c $(SRC)/main.cpp -o main.o

fourier.exe: cmdline.o DFT.o io.o main.o
	$(CXX) $(CXXFLAGS) $(CXXARGS) cmdline.o DFT.o  io.o main.o -o fourier.exe

gtest-all.o:
	$(CXX) $(CXXFLAGS) -isystem $(GOOGLETEST)/include -I$(GOOGLETEST) -pthread -c $(GOOGLETEST)/src/gtest-all.cc -o gtest-all.o

Complex_test.o: $(TESTS)/Complex_test.cpp $(INCLUDE)/Complex_test.h $(INCLUDE)/Complex.h $(INCLUDE)/Vector.h
	$(CXX) $(CXXFLAGS) $(CXXARGS) -c $(TESTS)/Complex_test.cpp -o Complex_test.o

Complex_test.exe: gtest-all.o Complex_test.o cmdline.o
	$(CXX) $(CXXFLAGS) $(CXXARGS) gtest-all.o Complex_test.o cmdline.o -o Complex_test.exe

DFT_test.o: $(TESTS)/DFT_test.cpp $(INCLUDE)/DFT_test.h $(INCLUDE)/Complex.h $(INCLUDE)/Vector.h $(INCLUDE)/io.h $(INCLUDE)/cmdline.h $(INCLUDE)/DFT.h
	$(CXX) $(CXXFLAGS) $(CXXARGS) -c $(TESTS)/DFT_test.cpp -o DFT_test.o

DFT_test.exe: DFT_test.o gtest-all.o cmdline.o
	$(CXX) $(CXXFLAGS) $(CXXARGS) gtest-all.o DFT_test.o DFT.o cmdline.o io.o -o DFT_test.exe

clean:
	$(RM) -vf *.o *.exe *.t *.out *.err
