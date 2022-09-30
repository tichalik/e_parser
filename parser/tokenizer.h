#ifndef TOKENIZER
#define TOKENIZER

#include "word.h"
#include "logger.h"


#include <string>
#include <sstream>

/** \brief interface tokenization
 * transforms text into a sequence of symbols -- in most cases the input is entire sentence within which the symbols are didided by spaces
 */

class Tokenizer
{
protected:
    Logger * logger;

public:
    Tokenizer(Logger * _logger);
    virtual std::pair<int, Word*> tokenize(const std::pair<int, std::string> & input)=0;
};



class Between_whitespaces_tokenizer: public Tokenizer
{
public:
    Between_whitespaces_tokenizer(Logger * _logger);
    virtual std::pair<int, Word*> tokenize(const std::pair<int, std::string> & input);
};


#endif // TOKENIZER



