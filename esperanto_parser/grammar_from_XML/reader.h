#ifndef GRAMMAR_FROM_XML_READER
#define GRAMMAR_FROM_XML_READER

#include "grammar.h"
#include "../logger.h"
#include "../reader.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <regex>
#include <sstream>


/** \brief constructs a grammar from given string input
 * all input is in form of pairs of line_id - line
 */

class Grammar_reader_from_XML
{
    /** \brief dividing text into bits accepted by the internal parser
     * cuts the input line into individual symbols using provided regex expression. If error occurs in some line, it is not included in the output.
     * \param input vector of pairs line_id - line
     * \param _tokens regex according to which tokenization will be done
     * \return vector of pairs line_id - vector of tokens
     *
     */

    std::vector<std::pair<int,std::vector<std::string>>> tokenize(std::vector<std::pair<int, std::string>>& input, const std::string & _tokens);

    /** \brief text normalization
     * removes: comments, empty lines, double (and more) spaces, spaces after '<', after '/', before '<'.
     */

    std::vector<std::pair<int, std::string>> normalize(const std::vector<std::pair<int, std::string>> & input);

    Logger * logger; /**< necessary for user-end communication */
public:

    /** \brief constructor
     * the logger is required
     */

    Grammar_reader_from_XML(Logger *);

    /** \brief constructs grammar from given string input
     * it works as a parser.
     * \param input vector of pairs line_id - line
     * \return constructed grammar. if critical error occurs it is a nullptr
     *
     */

    Grammar_from_XML* read(const std::vector<std::pair<int, std::string>> & input);
};

#endif //GRAMMAR_FROM_XML_READER
