#ifndef WORD
#define WORD

#include <string>
#include <vector>
#include <stack>

class Node
{
public:
    bool visited = false;
    std::string head;
    std::vector<Node> children;
    Node(const std::string& _head);
    Node();
    void clear_visited();
    std::string to_string();
    std::string leaves_to_string();
};

class Word
{
    bool end;
    Node root;
    Node * current;
    std::stack<Node*> path; //the node and which of it's children has been visited last
    void next_node();
public:
    Word(const Word& w);
    void reset_progress();
    bool is_end();
    Word(const std::string & _root);
    std::string to_string();
    std::string to_tree_string();
    Node& get_leftmost_leaf();
    void next();
};
#endif // WORD
