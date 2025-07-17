#include "dbc/lex/LexHelper.hpp"
#include "dbc/syntax/readers.hpp"
#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::cout;
using std::endl;
using std::ifstream;

const char* typeToString(dbc::TokenType type){
    switch(type){
        case dbc::TokenType::Blank:
            return "Blank";
        case dbc::TokenType::String:
            return "String";
        case dbc::TokenType::Operator:
            return "Operator";
        default:
            return "Unknown";
    }
}

int main(void){
    ifstream ifs("myconfig.dbc");
    dbc::LexHelper helper;

    // string raw((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    // std::cout << "Read string = " << raw << std::endl << std::endl << std::endl << std::endl;

    string raw("        Hello World     \t \t \n\n\n\n          Fuck Your! \t\t\t akkfjdalfj lakflajflk ajflk jlkdajfl ajl \"");

    while(helper.hasMore(raw)){
        //dbc::Token token = helper.readToken(raw);
        dbc::Token token = helper.readToken(raw, dbc::LongStringReader());
        std::cout << "Get token `" << token.buffer << "`, type is `" << typeToString(token.type) << "`." << std::endl;
    }

    
    


    return 0;
}

