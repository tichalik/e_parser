#ifndef TOKENIZER
#define TOKENIZER

#include "word.h"
#include "logger.h"


#include <string>
#include <sstream>

/** \brief tokenization interface
 * transforms text into a sequence of symbols
 */

class Tokenizer
{
protected:
    Logger * logger; /**< for error handling */

public:
    /** \brief constructor
     * requires logger for error handling
     */

    Tokenizer(Logger * _logger);

    /** \brief divides a line into a list of tokens
     *
     * \param input pair of line_id and line to be tokenized
     * \return pair of line_id and tokenization results as a WORD; in case of critical error the pointer is set to nullptr
     *
     */

    virtual std::pair<int, Word*> tokenize(const std::pair<int, std::string> & input)=0;
};


/** \brief uses whitespace as division between tokens
 *
 */

class Between_whitespaces_tokenizer: public Tokenizer
{
public:
    /** \brief constructor
     * requires logger for error handling
     */
    Between_whitespaces_tokenizer(Logger * _logger);
    /** \brief divides a line into a list of tokens
     *
     * \param input pair of line_id and line to be tokenized
     * \return pair of line_id and tokenization results as a WORD; NO CRITICALL ERRORS COULD ARISE HERE
     *
     */
    virtual std::pair<int, Word*> tokenize(const std::pair<int, std::string> & input);
};

/** \brief splits tokens at the space character. Sets everything in lowercase, removes nonalphanumeric characters
 *
 */


class Between_spaces_with_normalization: public Tokenizer
{
public:
    /** \brief constructor
     * requires logger for error handling
     */
    Between_spaces_with_normalization(Logger * _logger);
    /** \brief divides a line into a list of tokens
     *
     * \param input pair of line_id and line to be tokenized
     * \return pair of line_id and tokenization results as a WORD; NO CRITICALL ERRORS COULD ARISE HERE
     *
     */
    virtual std::pair<int, Word*> tokenize(const std::pair<int, std::string> & input);
};



#endif // TOKENIZER



