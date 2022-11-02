
#include "node.h"
Node::Node(const Word & input): content(input), visited(false), deepest_occurence(-1)
{

}
Node::~Node()
{
    //nie musimy bawiæ siê w rekursywne schodzenie po drzewie, skoro mamy tablicê wszystkich wêz³ów
//    for (int i=0; i<children.size(); i++)
//        if (children[i]!=nullptr)
//    {
//        delete children[i]; //usuniêcie automatycznie wywo³uje destruktor
//        children[i] = nullptr;
//    }
}
void Node::add_child( Node* child)
{
    children.push_back(child);
 //   std::cout <<"i am "<<this->content <<" and my child " <<  child->content <<std::endl;
}
