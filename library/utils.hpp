#ifndef LEXICAL_UTILS_HPP
#define LEXICAL_UTILS_HPP

#endif //LEXICAL_UTILS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> get_file_text(std::ifstream input_file);
void tokenize(char current);
void digit_token(char c);