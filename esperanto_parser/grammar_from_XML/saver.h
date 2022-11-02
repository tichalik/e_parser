#ifndef GRAMMAR_FROM_XML_SAVER
#define GRAMMAR_FROM_XML_SAVER


#include <string>
#include <fstream>

#include "grammar.h"

class Grammar_saver
{
public:
    Grammar_saver();
    bool write(const std::string & filepath,  Grammar_from_XML & grammar);
};
#endif // GRAMMAR_FROM_XML_SAVER
