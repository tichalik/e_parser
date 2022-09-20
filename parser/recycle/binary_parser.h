#include "../parser.h"

class Binary_parser: public Parser
{
public:
    Binary_parser(Grammar, Buffer<Word> *, Buffer<Parsing_node>*);
    virtual void parse();
};
