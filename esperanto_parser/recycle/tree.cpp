#include "tree.h"
#include <iostream>
Tree::Tree(const std::vector<Word>&input_words)
{
//    //convert Words into Nodes
//    for (Word w: input_words)
//    {
//        all_nodes.push_back(new Node(w));
//    }
//
//
//    //finding connections
//    for (int i=0; i<all_nodes.size(); i++)
//    {
//        for (int j=0; j<all_nodes.size(); j++)
//        {
//            if (i!=j && all_nodes[i]->content.is_subsequence(all_nodes[j]->content))
//                all_nodes[i]->add_child(all_nodes[j]);
//        }
//    }
//
//
//    Tree::present();
//
//    //reducing transitivity
//    for (Node* node: all_nodes)
//    {
//        std::list<Node*>::iterator to_erase = node->children.end();
//        for (std::list<Node*>::iterator child = node->children.begin(); child != node->children.end(); )
//            if (is_in_parrarel_tree(node, *child))
//                child = node->children.erase(child);
//            else
//                child++;
//    }
//    std::cout << "========================================================================\n";
//    Tree::present();
//
//    //picking heads
//        //for all_nodes mark deepest occurence
//    for (Node * n: all_nodes)
//        mark_deepest_occurence(n, 0);
//
//    std::cout << "========================================================================\n";
//    Tree::present();
//        //pick the ones that have no parents
//    for (Node* n: all_nodes)
//        if (n->deepest_occurence==0)
//            Tree::roots.push_back(n);
//
////    std::cout << "to juz koniec :3c\n";

}
void Tree::mark_deepest_occurence(Node* node, const int &i)
{
    if (node->deepest_occurence < i)
        node->deepest_occurence=i;
    for (Node* child: node->children)
        mark_deepest_occurence(child, i+1);
}
Tree::~Tree()
{
    for (Node*& ptr: all_nodes)
    {
        delete ptr;
        ptr=nullptr;
    }
}

bool Tree::is_in_parrarel_tree(const Node* parent, const Node* node)
{
    for (Node* child: parent->children) //dla wszystkich tylko nie dla jednego -> ranges?
        if (child!=node)
            if (is_in_subtree(child, node))
                return true;
    return false;
}
bool Tree::is_in_subtree(const Node* root, const Node* node)
{
    for(Node *child: root->children)
    {
        if (child==node)
            return true;
        else
            if (is_in_subtree(child, node))
                return true;
    }
    return false;
}
void Tree::present()
{
    for (Node * n: all_nodes)
    {
        std::cout << n->content  << ", deepest occurence "<<n->deepest_occurence<<std::endl;
        for (Node * child: n->children)
            std::cout << "\t" << child->content << std::endl;
    }
}
void Tree::clear_visited()
{
    for (Node * n: all_nodes)
        n->visited = false;
}
