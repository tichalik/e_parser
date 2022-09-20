#ifndef READER
#define READER

#include <filesystem>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>


class Reader
{
//    Buffer<std::string>* output; /**< output */
public:

    /** \brief initializes reading process of files within the given directory
     * \param directory storing the source files
     *
     */

    std::vector<std::string> read(const std::string& directory);
};

#endif // READER
