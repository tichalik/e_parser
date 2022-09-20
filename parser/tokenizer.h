#ifndef TOKENIZER
#define TOKENIZER

#include "word.h"
#include <string>
#include <sstream>

/** \brief interface tokenization
 * transforms text into a sequence of symbols -- in most cases the input is entire sentence within which the symbols are didided by spaces
 */

class Tokenizer
{
public:
    virtual Word tokenize(const std::string & input)=0;
};

/** \brief every character of input string is its own symbol
 *
 *
 */

class Character_tokenizer: public Tokenizer
{
public:
    virtual Word tokenize(const std::string & input);
};
/** \brief every character except whitespaces of input string is its own symbol
 *
 *
 */
class Letter_tokenizer: public Tokenizer //only considers letters, no white characters
{
public:
   virtual Word tokenize(const std::string & input);
};
/** \brief the symbols are didided by spaces
 *
 */

class Between_whitespaces_tokenizer: public Tokenizer
{
public:
    virtual Word tokenize(const std::string & input);
};


#endif // TOKENIZER



