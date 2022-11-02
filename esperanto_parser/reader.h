#ifndef READER
#define READER

#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>

#include "logger.h"

/** \brief reads the contents of files from given directory
 *
 */

class Reader
{
    Logger * logger; /**< required for communication with the user */
public:

    /** \brief constructor
     *
     */

     Reader(Logger * _logger);

     /** \brief reads files within the given directory
     * automatically removes comments and uniformizes white spaces
     * \param directory storing the source files
     * \return pair of line_id-line; in case of critical failure it is empty
     */
    std::vector<std::pair<int, std::string>> read(const std::string& directory);
};

#endif // READER
