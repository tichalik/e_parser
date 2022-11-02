#ifndef GRAMMAR_FROM_XML_LOADER
#define GRAMMAR_FROM_XML_LOADER

#include "../grammar_loader.h"

#include "normalizer.h"
#include "saver.h"
#include "reader.h"

/** \brief creates an instance of `Grammar_from_XML` from given directory
 * it is recommended for the directory to contain a single file -- every file in the directory is read and their contents are merged before constructing the grammar, though the order of this merge is unspecified.
 */

class Grammar_from_XML_loader: public Grammar_loader
{
public:
    /** \brief constructor
     * logger is required for comminication with the user
     *
     */

    Grammar_from_XML_loader(Logger *);

    /** \brief loads `Grammmar_from_tree` from given directory
     *
     * \param path directory in which the tree files are stored
     * \return pointer to fit into the `Grammar` interface. if critical error ocurred it is nullptr
     *
     */
    virtual Grammar* load(const std::string &path);
};

#endif //GRAMMAR_FROM_XML_LOADER
