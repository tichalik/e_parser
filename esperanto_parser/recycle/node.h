#ifndef NODE
#define NODE

#include <string>
#include <list>

#include "word.h"
/** \brief Node for the Tree class
 *
 *
 *
 */

class Node
{
public:
    Word content;
    std::list<Node*> children;
    bool visited;
    int deepest_occurence;

    void add_child( Node*);
    Node(const Word&);
    ~Node();
};
#endif // NODE
