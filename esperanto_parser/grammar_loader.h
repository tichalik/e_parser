#ifndef GRAMMAR_LOADER
#define GRAMMAR_LOADER

#include "grammar.h"
#include "logger.h"

#include <fstream>
#include <string>

/** \brief interface for loading a grammar from a directory
 *
 */

class Grammar_loader
{
protected:
    Logger * logger; /**< for communication */
public:
    /** \brief constructor
     * The loader cannot function without possibility of reporting an error therefore a Logger is required
     *
     */

    Grammar_loader(Logger*);

    /** \brief loads a grammar from a directory
     *
     * \param path directory storing files with grammar definition
     * \return nullptr if critical error occurred, else pointer to the grammar
     *
     */

    virtual Grammar* load(const std::string &path)=0;
};



#endif // GRAMMAR_LOADER
