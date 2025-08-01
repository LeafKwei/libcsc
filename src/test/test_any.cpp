#include <iostream>
#include <fstream>
#include "dbc/lex/CharMngr.hpp"
#include "dbc/lex/functions.hpp"
#include "dbc/lex/Locator.hpp"
#include "dbc/core/Dcontext.hpp"
using namespace dbc;

void showError(const Dstring &err, const CharMngr &mngr);
void skipBlank(CharMngr &mngr);
void skipDescription(CharMngr &mngr);
void parseDomain(CharMngr &mngr, Dcontext &context);
void parseAssign(CharMngr &mngr, Dcontext &context, const Dstring &name);
Dstring readIdentifer(CharMngr &mngr);
Dstring readOperator(CharMngr &mngr);


void parseDomain(CharMngr &mngr, Dcontext &context){
    while(mngr.valid()){
        skipBlank(mngr);
        skipDescription(mngr);

        

        Dstring id = readIdentifer(mngr);
        if(!mngr.valid() || id.size() == 0){
            showError("Error: excepted identifier.", mngr);
            return;
        }

        skipBlank(mngr);
        skipDescription(mngr);
        Dstring optor = readOperator(mngr);
        if(!mngr.valid() || optor.size() == 0){
            showError("Error: excepted operator.", mngr);
        }

        if(optor == "::"){
            context.makeDomain(id);
            context.enterDomain(id);
            parseDomain(mngr, context);
            context.exitDomain();
        }else if(optor == "="){
            parseAssign(mngr, context, id);
        }
    }
}

void parseAssign(CharMngr &mngr, Dcontext &context, const Dstring &name){

}

void showError(const Dstring &err, const CharMngr &mngr){
    std::cout << err << std::endl;
    Locator locator(mngr.str(), mngr.index());
    std::cout << "At: col " << locator.col() << ", row: " <<locator.row() << std::endl;
}

void skipBlank(CharMngr &mngr){
    while(mngr.valid() && isBlank(mngr.getch())){
        mngr.forward();
    }
}

void skipDescription(CharMngr &mngr){
    if(mngr.getch() == ';'){
        while(mngr.valid() && !isNewLine(mngr.getch())){
            mngr.forward();
        }
    }
}

int main(void){
    std::ifstream istream("myconfig.dbc");
    Dstring str((std::istreambuf_iterator<Dchar>(istream)), std::istreambuf_iterator<Dchar>());

    CharMngr mngr(str);
    
}