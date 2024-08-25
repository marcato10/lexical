#ifndef LEXICAL_UTILS_HPP
#define LEXICAL_UTILS_HPP

#endif //LEXICAL_UTILS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<std::string> get_file_text(std::ifstream input_file);
std::string get_line();
bool is_final_text(const std::vector<std::string>&text);
void read_char(char c);