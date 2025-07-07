#include "dbc/lex/structs.hpp"
#include "dbc/lex/functions.hpp"

DBC_BEGIN



Option decide(DbcChar ch, TokenType charType, TokenType lastCharType, const DbcString &buffer) noexcept{
    // Ignore blank.
    if(charType == TokenType::Blank){
        Option::Forward;
    }

    // Be sure to read first character.
    if(lastCharType == TokenType::Empty){
        return Option::PickAndForward;
    }

    // Stop to read
    if(charType != lastCharType){
        return Option::Finish;
    }

    // Normally
    return Option::PickAndForward;
}

void handleFinish(DbcChar ch, DbcString& buffer, UpdatePack &pack, TokenType charType, TokenType lastCharType){

}

void handlePick(DbcChar ch, DbcString& buffer, UpdatePack &pack, TokenType charType, TokenType lastCharType){

}

void handleForward(DbcChar ch, DbcString& buffer, UpdatePack &pack, TokenType charType, TokenType lastCharType){

}

void handlePickAndForward(DbcChar ch, DbcString& buffer, UpdatePack &pack, TokenType charType, TokenType lastCharType){

}

void handleFinishAndForward(DbcChar ch, DbcString& buffer, UpdatePack &pack, TokenType charType, TokenType lastCharType){
    
}

DBC_END