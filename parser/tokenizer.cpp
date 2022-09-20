#include "tokenizer.h"


Word Between_whitespaces_tokenizer::tokenize(const std::string & input)
{
    Word output_word;
    std::stringstream s;
    s << input;
    std::string tmp;

    while (s >> tmp)
        output_word.insert_symbol(tmp);

    return output_word;

}


Word Letter_tokenizer::tokenize(const std::string & input)
{

    Word output_word;
    std::string tmp;
    for (unsigned int i=0; i<input.size(); i++)
        if (input[i]!=' '&&input[i]!='\t'&&input[i]!='\n')
        {
            tmp = input[i]; //to jest dziwne, ale inaczej nie kompiluje :v
            output_word.insert_symbol(tmp);
        }
    return output_word;
}

Word Character_tokenizer::tokenize(const std::string & input)
{
    Word output_word;
    std::string tmp;
    for (unsigned int i=0; i<input.size(); i++)
        {
            tmp = input[i]; //to jest dziwne, ale inaczej nie kompiluje :v
            output_word.insert_symbol(tmp);
        }
    return output_word;
}

