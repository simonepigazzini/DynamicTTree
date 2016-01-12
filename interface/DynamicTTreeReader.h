#include "TFile.h"
#include "TTree.h"

template<typename T> struct argument_type;
template<typename T, typename U> struct argument_type<T(U)> { typedef U type; };

