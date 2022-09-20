#include "parsing_node.h"

bool Parsing_node::operator==(Parsing_node& p)
{
    return (p.tag==tag&&p.children==children);
}
bool operator==(const Parsing_node& p1, const Parsing_node& p2)
{
    return (p1.tag==p2.tag&&p1.children==p2.children);
}
std::string Parsing_node::to_string()
{
    std::string tmp;
    for (Parsing_node p: children)
        tmp += " "+p.to_string();
    if (tmp!="")
        tmp = "["+tmp.substr(1,tmp.size()-1)+"]";
    return (tag+tmp);
}

