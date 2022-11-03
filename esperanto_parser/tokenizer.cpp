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

Between_spaces_with_normalization::Between_spaces_with_normalization(Logger * _logger): Tokenizer(_logger)
{

}

std::pair<int, Word*> Between_spaces_with_normalization::tokenize(const std::pair<int, std::string> & input)
{
    Word* output_word = new Word;
    std::string current;
    ///input string has no leading space
    for (const char c: input.second)
    {
        ///lowercase alphabet
        if (c<='z'&&c>='a')
            ///extends current string
            current += c;
        ///upercase character
        else if (c<='Z'&&c>='A')
            ///converted to lowercase extends the current string
            current += c + ('a'-'A');
        ///token separator
        else if (c==' ')
        {
            ///the token is complete
            output_word->insert_symbol(current);
            ///finding new token
            current.clear();
        }
    }
    ///input string has no trailing space
    ///inserting the last token
    output_word->insert_symbol(current);

    return {input.first, output_word};


}
