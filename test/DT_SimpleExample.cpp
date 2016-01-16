#include <iostream>
#include <string>

#include "interface/DynamicTTreeBase.h"

//**********DynamicTTree definition example***********************************************
//---Define the TTree branches
#define DYNAMIC_TREE_NAME DynamicTTree

#define DATA_TABLE                              \
    DATA(int, i)                                \
    DATA(float, f)
#define DATA_VECT_TABLE                         \
    DATA(int, vi, i)
#define DATA_CLASS_TABLE                        \
    DATA(std::string, s)

//---include the self generated code for the new DynamicTTree
#include "interface/DynamicTTreeInterface.h"

//---optional: register the new DynamicTTree in the ROOT dictionary
#ifdef __ROOTCLING__
#pragma link C++ class DynamicTTree+;
#endif

//*********MAIN***************************************************************************
#ifndef __MAIN__
#define __MAIN__

int main(int argc, char* argv[])
{
    //--create new TTree
    TFile* file = TFile::Open("test.root", "RECREATE");
    DynamicTTree newTree("test", "DynamicTTree");
    newTree.i = 5;
    newTree.f = 5.5;
    for(int j=0; j<newTree.i; ++j)
        newTree.vi[j] = j;
    *newTree.s = std::string("string");
    newTree.GetTTreePtr()->Fill();
    newTree.GetTTreePtr()->Write();
    file->Close();

    //---read back the same TTree
    TFile* inFile = TFile::Open("test.root", "READ");
    TTree* test = (TTree*)inFile->Get("test");
    DynamicTTree reader(test);
    while(reader.NextEntry())
    {
        std::cout << reader.i << std::endl;
        std::cout << reader.f << std::endl;
        std::cout << *reader.s << std::endl;
        for(int j=0; j<reader.i; ++j)
            std::cout << reader.vi[j] << std::endl;                
    }
    
    return 0;
}

#endif
