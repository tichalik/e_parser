#ifndef PARSE_TREE
#define PARSE_TREE

#include <string>

#include "parsing_node.h"

class Parse_tree
{
    Parsing_node *  root;
public:
    Parse_tree(Parsing_node * _root);
    ~Parse_tree();
    std::string to_string();
};

#endif // PARSE_TREE
