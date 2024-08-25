#include "utils.hpp"
#include "definitions.hpp"
std::vector<std::string> get_file_text(std::ifstream input_file){
    std::vector<std::string>text;
    for(std::string line;std::getline(input_file,line);){
        text.emplace_back(line);
    }
    return text;
}

