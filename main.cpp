#include <iostream>
#include <fstream>
#include <vector>
#include "definitions.hpp"
#include <format>
#include <filesystem>

const int DEFAULT_SIZE = 32;

using namespace lexical;
int main(int argc,char *argv[]) {
    std::ifstream sourceFile(std::filesystem::current_path().string() + "/Source.txt");
    if(!sourceFile){
        std::cerr << "Cannot open source file" << std::endl;
        return EXIT_FAILURE;
    }
    std::string buffer;
    State lexicalState = State::Reading_lexeme;

    char current;
    std::vector<Token>tokens;

    //While not End of File
    while (!sourceFile.get(current).eof()){
        std::cout << current << std::endl;
        switch (lexicalState) {

            case State::Comment_active:
                if(current == '}')
                    lexicalState = State::Reading_lexeme;
                break;
            case State::Reading_lexeme:
                if(current == '{'){
                    lexicalState = State::Comment_active;
                    if(!buffer.empty()){
                        Token token;
                        token.lexical = buffer;
                        tokens.emplace_back(token);

                    }
                    buffer.clear();
                    continue;
                }

                if(isspace(current)){
                    if(!buffer.empty()){
                        Token token;
                        token.lexical = buffer;
                        tokens.emplace_back(token);

                        std::cout << buffer << std::endl;
                    }
                    buffer.clear();
                    continue;
                }
                if(isascii(current)){
                    buffer.push_back(current);
                }
                break;
        }
    }
    if(!buffer.empty()){
        Token token;
        token.lexical = buffer;
        tokens.emplace_back(token);
    }

    for (const auto &item: tokens){
        std::cout << item.lexical << std::endl;
    }
    sourceFile.close();

    return EXIT_SUCCESS;
}

