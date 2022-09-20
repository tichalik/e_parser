#ifndef GENERATOR
#define GENERATOR

#include <iostream>

#include "grammar.h"
#include "word.h"
#include "logger.h"
#include "interface.h"

class Generator
{
    Logger logger;
    Interface interface;
    bool ok;
public:
    Generator(const Logger& _logger, const Interface& _interface);
    bool is_ok();
    Word generate__word(Grammar & grammar, const bool auto_picking);
};
#endif // GENERATOR
