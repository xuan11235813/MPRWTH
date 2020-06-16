CXXFLAGS = -O3 -g -std=c++11  -Wall -Wextra -Wpedantic


main:  main.o unit.o IGL.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lGL -lX11 -lpthread

main.o: main.cpp tvector.h tmatrix.h unit.h
	$(CXX) $(CXXFLAGS) -c $<







clean:
	rm -f tvector.o tmatix.o main.o

.PHONY: clean
