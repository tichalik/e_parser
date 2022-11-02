#include "lojban/tokenizer.h"

Word* Lojban_tokenizer::tokenize(const std::string & input)
{
    std::string current;
    Word* output = new Word;
    for (char c: input)
    {
        if (c=='(' || c==')'|| c=='['|| c==']'|| c=='='|| c=='|'|| c=='&')
        {
            if (current!="")
                output->insert_symbol(current);

            current = c;
            output->insert_symbol(current);
            current = "";
        }
        else if (c==' '||c=='\t')
        {
            if (current!="")
                output->insert_symbol(current);

            current = "";
        }
        else
            current += c;
    }
    output->insert_symbol(current);
    return output;
}
