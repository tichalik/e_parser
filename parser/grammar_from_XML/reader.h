#ifndef GRAMMAR_FROM_TREE_READER
#define GRAMMAR_FROM_TREE_READER

#include "grammar.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <regex>
#include <sstream>

class Grammar_reader_from_XML
{
    std::vector<std::pair<int,std::vector<std::string>>> tokenize(std::vector<std::pair<int, std::string>>&, const std::string & _tokens);
    std::vector<std::pair<int, std::string>> normalize(const std::string & input);
    std::vector<std::pair<int, std::string>> preprocessed_input;
    bool all_ok;
public:
    Grammar_reader_from_XML();
    Grammar_from_XML* read(const std::string &path);
};

#endif //GRAMMAR_FROM_TREE_READER
