CXX = g++
CXXFLAGS = -std=c++11
INCLUDE = -I"./"

ROOT_LIB := `root-config --libs --glibs`
ROOT_FLAGS := `root-config --cflags --ldflags`

all: bin/DTR_SimpleExample

bin/%: test/%.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDE) $(ROOT_LIB) $(ROOT_FLAGS)

clean:
	rm -fr bin/*
