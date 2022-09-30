#include "tokenizer.h"

Tokenizer::Tokenizer(Logger * _logger): logger(_logger)
{

}


Between_whitespaces_tokenizer::Between_whitespaces_tokenizer(Logger * _logger): Tokenizer(_logger)
{

}

std::pair<int, Word*> Between_whitespaces_tokenizer::tokenize(const std::pair<int, std::string> & input)
{
    Word* output_word = new Word;
    std::stringstream s;
    s << input.second;
    std::string tmp;

    while (s >> tmp)
        output_word->insert_symbol(tmp);

    return {input.first, output_word};

}

