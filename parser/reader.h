#ifndef READER
#define READER

#include <filesystem>
#include <fstream>
#include <string>
#include <sstream>

#include "logger.h"

class Reader
{
//    Buffer<std::string>* output; /**< output */
    Logger * logger;
public:

    /** \brief initializes reading process of files within the given directory
     * \param directory storing the source files
     *
     */

     Reader(Logger * _logger);
    std::vector<std::pair<int, std::string>> read(const std::string& directory);
};

#endif // READER
