#ifndef GRAMMAR_FROM_TREE_LOADER
#define GRAMMAR_FROM_TREE_LOADER

#include "../grammar_loader.h"
#include "../reader.h"
#include "rule_parser.h"
#include "rule_transformer.h"

/** \brief creates an instance of `Grammmar_from_tree` from given directory
 *
 */

class Grammar_from_tree_loader: public Grammar_loader
{
public:

    /** \brief constructor
     * the logger is required in case of errors
     *
     */

    Grammar_from_tree_loader(Logger *&);

    /** \brief loads `Grammmar_from_tree` from given directory
     *
     * \param path directory in which the tree files are stored
     * \return pointer to fit into the `Grammar` interface. if critical error ocurred it is nullptr
     *
     */

    virtual Grammar* load(const std::string &path);
};


#endif // GRAMMAR_FROM_TREE_LOADER
