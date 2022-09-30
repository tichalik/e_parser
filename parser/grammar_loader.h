#ifndef GRAMMAR_LOADER
#define GRAMMAR_LOADER

#include "grammar.h"
#include "logger.h"

#include <fstream>
#include <string>


class Grammar_loader
{
protected:
    Logger * logger;
public:
    Grammar_loader(Logger*);
    virtual Grammar* load(const std::string &path)=0;
};



#endif // GRAMMAR_LOADER
