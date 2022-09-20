#include "word.h"



#include <iostream>
Node::Node(const std::string& _head): head(_head)
{

}
Node::Node()
{

}

void Node::clear_visited()
{
//    std::cout << "cleaning " <<head << "\n";
    visited = false;
    for (int i=0; i<children.size(); i++)
        children[i].clear_visited();
}
std::string Node::leaves_to_string()
{
    std::string result;
    if (children.empty())
    {
        result =  head;
    }
    else
    {

        for (Node child: children)
            result += child.leaves_to_string() + " ";
        result = result.substr(0,result.size()-1);
    }
    return result;
}

std::string Node::to_string()
{
    std::string result;
    if (children.empty())
    {
        result =  head;
    }
    else
    {
        result = head +"[ ";

        for (Node child: children)
            result += child.to_string() + " ";
        result += "]";
    }
    return result;
}

Word::Word(const std::string & _root): end(false), current(&root)
{
    root.head = _root;
}
Word::Word(const Word & w): end(w.end), root(w.root) //does it work? idk, just remember that current is a pointer and when a new tree is made copying it directly wold have both currents point to the same tree
{
    current = & root;
    while(path!=w.path)
        next_node();

}

Node& Word::get_leftmost_leaf()
{
    return *current;
}
bool Word::is_end()
{
    return end;
}

void Word::next()
{
    do
    {
//        std::cout << current->head << "is not a leaf\n";
        next_node();
    }
    while (!end && current->children.size()!=0);
}

void Word::next_node()
{
    if (!root.visited)
    {
        bool moved = false;
//        std::cout << "jumps: ";
        for (int i=0; i<current->children.size(); i++)
        {

            if (!current->children[i].visited)
            {
//                std::cout << "+";
                moved = true;
                path.push(current);
                current = &(current->children[i]);
                i = -1;//because we've moved we need to reset the position
//                    std::cout << "moving to " << current->head << "\n";
            }
        }
//         std::cout << "\n";
        if (!moved)
        {
//                std::cout << "marking " << current->head << "as visited and moving to ";
            current->visited = true;
            if (!path.empty())
            {
                current = path.top();
//                std::cout << current->head << "\n";
                path.pop();
            }
            else
            {
                current = nullptr;
                end = true;
            }
        }
    }
    else
    {
        current = nullptr;
        end = true;
    }
}

std::string Word::to_string()
{
    return root.leaves_to_string();
}

std::string Word::to_tree_string()
{
    return root.to_string();
}
void Word::reset_progress()
{
    end = false;
    root.clear_visited();
    current = &root;
    next();
}
