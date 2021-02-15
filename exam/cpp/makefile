CXX = c++
CXXFLAGS = -Wall -Wextra -g -std=c++14

SRC = src/main.cc \
	  src/benchmark.cc

#prova.cc -> prova.x
EXE = $(SRC:.cc=.x)

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cc .x

all: $(EXE)

.PHONY: all

docs: Doxygen/doxy.in
	doxygen $^

%.x: %.cc 
	$(CXX) $< -o $@ $(CXXFLAGS)

.PHONY: format

clean:
	rm -f $(EXE) *~

.PHONY: clean
