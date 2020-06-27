CXXFLAGS = -O3 -g -std=c++17  -Wall -Wextra -Wpedantic


main:  vierGewinnt.o unit.o plotx11.o
	$(CXX) $(CXXFLAGS) -o $@ $^  -lX11 -lGL -lpthread

vierGewinnt.o: vierGewinnt.cpp 
	$(CXX) $(CXXFLAGS) -c $<







clean:
	rm -f vierGewinnt.o

.PHONY: clean
