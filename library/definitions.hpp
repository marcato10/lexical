#ifndef LEXICAL_DEFINITIONS_HPP
#define LEXICAL_DEFINITIONS_HPP

#endif //LEXICAL_DEFINITIONS_HPP
#include <iostream>
#include <string>
namespace lexical{
    enum class TokenSymbol : char {
        programa,
        inicio,
        fim,
        procedimento,
        funcao,
        se,
        entao,
        senao,
        enquanto,
        faca,
        atribuicao,
        escreva,
        leia,
        var,
        inteiro,
        booleano,
        identificador,
        numero,
        ponto,
        ponto_virgula,
        abre_parenteses,
        fecha_parenteses,
        maior,
        maior_igual,
        igual,
        menor,
        menor_igual,
        dif,
        mais,
        menos,
        mult,
        div,
        e,
        ou,
        nao,
        doispontos,
        verdadeiro,
        falso
    };

    class Token{
    public:
        std::string lexical;
        TokenSymbol symbol;
    };

    enum class State{
        Comment_active,
        Reading_lexeme
    };
}