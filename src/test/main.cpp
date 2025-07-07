#include "dbc/lex/LexHelper.hpp"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

int main(void){

    const string raw = "a b c";
    dbc::LexHelper helper;

    helper.readToken(raw);

    return 0;
}