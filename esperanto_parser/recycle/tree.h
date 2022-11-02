#ifndef TREE
#define TREE

#include <vector>
#include <fstream>

#include "node.h"
/** \brief tree of transitive relations
 *
 *
 */

class Tree
{
    std::vector<Node*> all_nodes;/**< storing them in vector helps in deletion; nodes reference pointers to decrease redundancy */
    std::vector<Node*> roots;

    /** \brief check whether node is the tree of root root
     *
     * \param root const Node* the root of sought-through tree
     * \param node const Node* the node that is sought
     * \return bool true if found
     *
     */
    bool is_in_subtree(const Node* root, const Node* node);
    /** \brief check whether node can be found in other subtrees of the same parent
     *
     * \param parent const Node* the parent of node
     * \param node const Node * node which is sought
     * \return bool true if found
     *
     */

    bool is_in_parrarel_tree(const Node* parent, const Node* node);

    /** \brief marks the deepest tree level at which node can be found
     *
     * \param node Node* sought node
     * \param i const int value marking the root of the tree
     * \return
     *
     */

    void mark_deepest_occurence(Node* node, const int &i);

    void clear_visited();
public:
    /** \brief constructor
     * creates nodes from provided vector
     * \param provided vector
     */

    Tree(const std::vector<Word>&);
    /** \brief for debugging
     *
     */

    void present(); // just for show

    /** \brief destructor
     * should delete all_nodes
     *
     */

    ~Tree();
};

#endif // TREE
