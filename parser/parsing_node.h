#ifndef PARSING_NODE
#define PARSING_NODE

#include <string>
#include <vector>

class Parsing_node
{
public:
    std::string tag; /**< the "body' of node */
    std::vector<Parsing_node> children; /**< all the dependant nodes */
    /** \brief turns the node into string representation
     * string representation goes TAG[child1 child2] and is recursive
     * \return string representation
     *
     */

    std::string to_string();

    bool operator==(Parsing_node&); /**< required for Parsing node to be stored in Buffer */
    friend bool operator==(const Parsing_node&, const Parsing_node&);/**< required for Parsing node to be stored in Buffer */
};


#endif // PARSING_NODE
