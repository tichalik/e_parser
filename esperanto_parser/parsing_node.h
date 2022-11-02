#ifndef PARSING_NODE
#define PARSING_NODE

#include <string>
#include <vector>

/** \brief A vertex in the parse tree representation
 *
 */

class Parsing_node
{
public:
    std::string tag; /**< what the node holds */
    std::vector<Parsing_node*> children; /**< all the dependant nodes -- class supports trees of various child numbers WARNING! the nodes exist independently from main node and destruction of children has to be called manually */

    /** \brief turns the node into string representation
     * string representation goes TAG[child1 child2] and is recursive
     * \return string representation
     *
     */

    std::string to_string();


    /** \brief Manual calling for destruction of children
     * used only by `Parsing_tree` as in other places pointer to each node is stored in a table -- and they are deleted individually
     * \param
     * \param
     * \return
     *
     */

    void delete_children();

    /** \brief explicitly calling for a deep copy
     * normal copies are shallow and it's desired
     * \return pointer to a newly allocated `Parsing_node` object
     *
     */

    Parsing_node* clone();

};


#endif // PARSING_NODE
