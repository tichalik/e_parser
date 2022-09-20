#ifndef GRAMMAR_LOADER
#define GRAMMAR_LOADER

#include "grammar.h"

#include <fstream>
#include <string>


class Grammar_loader
{
protected:
    Grammar_loader();
public:
    virtual Grammar* read(const std::string &path)=0;
};



#endif // GRAMMAR_LOADER
