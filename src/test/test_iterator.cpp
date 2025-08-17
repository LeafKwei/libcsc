#include <cstdio>
#include <iostream>
#include <fstream>
#include "dbc/syntax/CommandDrv.hpp"
using namespace dbc;

class Iterator : public Diterator{
public:
    Iterator() : indent(0){}

    void enter(const Dstring &name) override{
        for(int i = 0; i < indent; i++) printf("\t");
        printf("%s::\n", name.c_str());
        ++indent;
    }

    void exit(const Dstring &name) override{
         if(indent > 0) --indent;
        for(int i = 0; i < indent; i++) printf("\t");
        printf("::%s\n", name.c_str());
    }

    void pair(const Dstring &name, const Dstring &value) override{
        for(int i = 0; i < indent; i++) printf("\t");
        printf("%s = %s\n", name.c_str(), value.c_str());
    }

private:
    int indent;
};

int main(void){
    std::ifstream ifs("myconfig.dbc");
    Dstring str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    Iterator iterator;
    Dcontext context;
    CommandDrv drv;
    drv.drive(str, context);
    context.iterate(iterator);
}