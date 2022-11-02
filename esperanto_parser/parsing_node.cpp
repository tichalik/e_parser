#include "parsing_node.h"

Parsing_node * Parsing_node::clone()
{
    Parsing_node* copy = new Parsing_node;
    copy->tag = tag;
    for (Parsing_node* child: children)
        copy->children.push_back(child->clone());
    return copy;
}

//bool Parsing_node::operator==(Parsing_node& p)
//{
//    return (p.tag==tag&&p.children==children);
//}
//bool operator==(const Parsing_node& p1, const Parsing_node& p2)
//{
//    return (p1.tag==p2.tag&&p1.children==p2.children);
//}
std::string Parsing_node::to_string()
{
    std::string tmp;
    for (Parsing_node* p: children)
        tmp += " "+p->to_string();
    if (tmp!="")
        tmp = "["+tmp.substr(1,tmp.size()-1)+"]";
    return (tag+tmp);
}

void Parsing_node::delete_children()
{
    for (Parsing_node * p: children)
    {
        p->delete_children();
        delete p;
    }
}

