#ifndef LOJBAN_TOKENIZER
#define LOJBAN_TOKENIZER

#include "../tokenizer.h"

class Lojban_tokenizer: public Tokenizer
{
    virtual Word tokenize(const std::string & input);
};

#endif // LOJBAN_TOKENIZER
