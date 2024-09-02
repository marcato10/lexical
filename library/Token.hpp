#include "definitions.hpp"
#ifndef LEXICAL_TOKEN_HPP
#define LEXICAL_TOKEN_HPP

#endif //LEXICAL_TOKEN_HPP


class Token{
    std::string lexema;
    lexical::TokenSymbol symbol;
public:

    std::string getLexeme();
    void setValue(const std::string& string);
    lexical::TokenSymbol getSymbol();
    void setSymbol(lexical::TokenSymbol symbol);
};


