#include "dbc/lex/LexHelper.hpp"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

int main(void){

    const string raw = "    \n     \n         \n           \n        ";
    dbc::LexHelper helper;

    if(helper.hasMore(raw)){
        dbc::Token token = helper.readToken(raw);
        std::cout << ">>>" << token.buffer << "<<<" << std::endl;
        std::cout << "row: " << helper.numberOfRow() << ", col: " << helper.numberOfCol() << std::endl;
    }
    
    return 0;
}