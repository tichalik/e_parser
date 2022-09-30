#ifndef GRAMMAR_FROM_TREE_LOADER
#define GRAMMAR_FROM_TREE_LOADER

#include "../grammar_loader.h"
#include "../reader.h"
#include "rule_parser.h"
#include "rule_transformer.h"


class Grammar_from_tree_loader: public Grammar_loader
{
public:
    Grammar_from_tree_loader(Logger *&);
    virtual Grammar* load(const std::string &path);
};


#endif // GRAMMAR_FROM_TREE_LOADER
