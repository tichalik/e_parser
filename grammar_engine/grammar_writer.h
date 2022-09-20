#ifndef GRAMMAR_WRITER
#define GRAMMAR_WRITER


#include <string>
#include <fstream>

#include "grammar.h"
#include "logger.h"

class Grammar_writer
{
    Logger logger;
public:
    Grammar_writer( Logger  logger);
    bool write(const std::string & filepath,  Grammar & grammar);
};
#endif // GRAMMAR_WRITER
