CXX = g++
CXXFLAGS = -std=c++11 -fPIC
SOFLAGS = -shared -O3
INCLUDE = -I"./"
LIB = -L"./lib/"

ROOT_LIB := `root-config --libs --glibs`
ROOT_FLAGS := `root-config --cflags --ldflags`

all: bin/DTR_SimpleExample lib/LinkDef.cxx lib/DTRDict.so

lib/LinkDef.cxx: test/DTR_SimpleExample.cpp
	rootcling -f $@ -c $^

lib/DTRDict.so: lib/LinkDef.cxx 
	$(CXX) $(CXXFLAGS) $(SOFLAGS) -o $@ $^ $(INCLUDE) $(ROOT_LIB) $(ROOT_FLAGS) $(LIB)

bin/%: test/%.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(INCLUDE) $(ROOT_LIB) $(ROOT_FLAGS) 

clean:
	rm -fr bin/*
	rm -fr lib/*
