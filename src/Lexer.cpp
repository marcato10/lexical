//
// Created by marcato on 27/08/24.
//
#include "Lexer.hpp"


Token tokenize(const std::string& str){
    Token token;
    if(isdigit(str.at(0))){
        handle_digit(str);
    }

    else{

    }
    return token;
}

