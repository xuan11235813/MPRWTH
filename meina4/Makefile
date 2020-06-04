CXXFLAGS = -O3 -g -std=c++17 -Wall -Wextra -Wpedantic

main:  tvector.o tmatrix.o IGL.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp tvector.h
	$(CXX) $(CXXFLAGS) -c $<

vector.o: tvector.cpp tvector.h
	$(CXX) $(CXXFLAGS) -c $<

matrix.o: tmatrix.cpp tmatrix.h tvector.h
	$(CXX) $(CXXFLAGS) -c $<





clean:
	rm -f vector.o matix.o main.o

.PHONY: clean
