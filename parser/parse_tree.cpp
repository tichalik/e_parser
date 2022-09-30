#include "parse_tree.h"


Parse_tree::Parse_tree(Parsing_node * _root): root(_root)
{

}

#include <iostream>
Parse_tree::~Parse_tree()
{
    root->delete_children();
    delete root;
}

std::string Parse_tree::to_string()
{
    return root->to_string();
}
