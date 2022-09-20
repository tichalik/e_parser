#ifndef GRAMMAR_READER
#define GRAMMAR_READER

#include <string>
#include <vector>
#include <regex>
#include <sstream>
#include <fstream>

#include "grammar.h"
#include "logger.h"


class Grammar_reader
{
protected:
//    Logger logger;
    std::vector<std::pair<int,std::vector<std::string>>> tokenize(std::vector<std::pair<int, std::string>>&, const std::string & _tokens);
    std::vector<std::pair<int, std::string>> normalize(const std::string & input);
    Logger logger;
    std::vector<std::pair<int, std::string>> preprocessed_input;
    bool all_ok;
public:
    Grammar_reader( Logger &_logger, std::string& input);
    bool is_ok();

    virtual Grammar read()=0;
};

class BNF_without_ors_reader: public Grammar_reader
{
//    std::vector<std::string> tokenize(const std::string&);
public:
    Grammar read();
    BNF_without_ors_reader(Logger &_logger, std::string& input);
};

#endif // GRAMMAR_READER
