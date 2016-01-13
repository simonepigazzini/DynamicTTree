#include <iostream>
#include <string>

#include "interface/DynamicTTreeReader.h"

#define DYNAMIC_TREE_NAME DynamicTTreeReader

#define DATA_TABLE                              \
    DATA(int, i)                                \
    DATA(float, f)
#define DATA_VECT_TABLE                         \
    DATA(int, vi, i)
#define DATA_CLASS_TABLE                        \
    DATA(std::string, s)

#include "src/DynamicTTreeReader.cc"

#ifdef __ROOTCLING__
#pragma link C++ class DynamicTTreeReader+;
#endif

#ifndef __MAIN__
#define __MAIN__

int main(int argc, char* argv[])
{
    TFile* fi = TFile::Open("test.root", "RECREATE");
    TTree* t_ = new TTree();
    int i=5;
    float f=5.5;
    int vi[5]={1,2,3,4,5};
    std::string s="string";
    t_->Branch("i", &i, "i/I");
    t_->Branch("f", &f, "f/F");
    t_->Branch("vi", vi, "vi[i]/I");
    t_->Branch("s", "std::string", &s);
    t_->Fill();
    t_->Write("test");
    fi->Close();

    TFile* fo = TFile::Open("test.root", "READ");
    TTree* test = (TTree*)fo->Get("test");
    //TTreeDynamicReader a(test);
    DynamicTTreeReader a(test);
    for(int i=0; i<test->GetEntriesFast(); ++i)
    {
        test->GetEntry();
        std::cout << a.i << std::endl;
        std::cout << a.f << std::endl;
        std::cout << *a.s << std::endl;
        for(int j=0; j<a.i; ++j)
            std::cout << a.vi[j] << std::endl;                
    }
    
    return 0;
}

#endif
