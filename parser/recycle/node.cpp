
#include "node.h"
Node::Node(const Word & input): content(input), visited(false), deepest_occurence(-1)
{

}
Node::~Node()
{
    //nie musimy bawi� si� w rekursywne schodzenie po drzewie, skoro mamy tablic� wszystkich w�z��w
//    for (int i=0; i<children.size(); i++)
//        if (children[i]!=nullptr)
//    {
//        delete children[i]; //usuni�cie automatycznie wywo�uje destruktor
//        children[i] = nullptr;
//    }
}
void Node::add_child( Node* child)
{
    children.push_back(child);
 //   std::cout <<"i am "<<this->content <<" and my child " <<  child->content <<std::endl;
}
