class DYNAMIC_TREE_NAME
{
public:
    virtual ~DYNAMIC_TREE_NAME() {};
#define DATA(t, name) argument_type<void(t)>::type name;
    DATA_TABLE                                                          
#undef DATA
    
#define DATA(t, name, size) argument_type<void(t)>::type* name;
    DATA_VECT_TABLE                                                          
#undef DATA

#define DATA(t, name) argument_type<void(t)>::type* name;
    DATA_CLASS_TABLE                                                          
#undef DATA    
    
    DYNAMIC_TREE_NAME(TTree* t)
        {
            tree_ = t;

#define DATA(t, name) tree_->SetBranchAddress(#name, &name);
DATA_TABLE                                                          
#undef DATA

    tree_->GetEntry(0);
    
#define DATA(t, name, size) name=new argument_type<void(t)>::type[size]; tree_->SetBranchAddress(#name, name);
DATA_VECT_TABLE                                                          
#undef DATA
    
#define DATA(t, name) name=new argument_type<void(t)>::type(); tree_->SetBranchAddress(#name, &name);
DATA_CLASS_TABLE                                                          
#undef DATA

    }

private:
    TTree* tree_;
};
