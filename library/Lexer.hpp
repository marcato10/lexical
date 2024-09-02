
#ifndef LEXICAL_LEXER_HPP
#define LEXICAL_LEXER_HPP

#endif //LEXICAL_LEXER_HPP
#include "Token.hpp"

//PegaToken
Token tokenize(const std::string& str);

//Trata digito
void handle_digit(const std::string& str);


void atribuicao(Token& token);
void operador_aritmetico(Token& token);
void operador_relacional(Token& token);
void pontuacao(Token& token);
