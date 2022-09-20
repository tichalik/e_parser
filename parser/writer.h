#ifndef WRITER
#define WRITER

#include "parser.h"

#include <string>
#include <fstream>
#include <filesystem>

/** \brief Interface for parallel saving Parsing_nodes into file
 *
 *
 */

class Writer
{
protected:
    std::filesystem::path path; /**< file to which results will be saved */
public:
    /** \brief Constructor
     *
     * \param std::string path to saving file (should be the file)
     * \param Buffer<std::string>* pointer to source buffer
     *
     */
    Writer(std::string);
    /** \brief starts the writing process
     *
     */

    virtual void write(const std::vector<std::string>& input)=0;
};

/** \brief the simplest realisation of the interface Writer
 *
 */

class Simple_writer: public Writer
{
public:
    Simple_writer(std::string);
    virtual void write(const std::vector<std::string>& input);
};

#endif // WRITER
