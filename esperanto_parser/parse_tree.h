#ifndef PARSE_TREE
#define PARSE_TREE

#include <string>

#include "parsing_node.h"

/** \brief wrapper for parsing results
 * important for its destructor which allows not to worry about how `Parsing_node` should be destructed
 */

class Parse_tree
{
    Parsing_node *  root; /**< the root of the parsing tree */
public:
    /** \brief constructor
     *
     * \param _root pointer to the root node. The tree should be the only object having access to it
     *
     */

    Parse_tree(Parsing_node * _root);
    /** \brief destructor
     * need to deallocate the root and start the destruction process for all its children
     *
     */

    ~Parse_tree();

    /** \brief returns textual representation of the tree
     * see the documentation for `Parsing_node::to_string()` to see the style
     * \return textual representation of the tree
     *
     */

    std::string to_string();
};

#endif // PARSE_TREE
