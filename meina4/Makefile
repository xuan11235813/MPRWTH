CXXFLAGS = -O3 -g -std=c++17 -Wall -Wextra -Wpedantic

main:  main.o
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp tvector.h tmatrix.h
	$(CXX) $(CXXFLAGS) -c $<







clean:
	rm -f vector.o matix.o main.o

.PHONY: clean
