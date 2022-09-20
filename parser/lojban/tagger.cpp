#include "lojban/tagger.h"

Word Lojban_tagger::tag( const Word & input)
{
    Word output_word(input);

    std::vector<int> degree(output_word.get_size(),1);


    //the loop starts from the second element so the first and last are computed manually

    std::string symbol = output_word.get_symbol_at(0);

    if (symbol == "&")
    {
            degree[1]=2;
    }
    else if (symbol!="("&&symbol!=")"&&symbol!="["&&symbol!="]"&&symbol!="="&&symbol!="/"&&symbol!="..."&&symbol!="|")
    {
            degree[1]=3;
    }


    for (int i=1; i<output_word.get_size()-1; i++)
    {
        std::string symbol = output_word.get_symbol_at(i);

        if (symbol == "|")
        {
            if (degree[i-1]<1)
                degree[i-1]=1;
            if (degree[i+1]<1)
                degree[i+1]=1;
        }
        else if (symbol == "&")
        {
            if (degree[i-1]<2)
                degree[i-1]=2;
            if (degree[i+1]<2)
                degree[i+1]=2;
        }
        else if (symbol == "...")
        {
            if (degree[i-1]<4)
                degree[i-1]=4;
        }
        else if (symbol!="("&&symbol!=")"&&symbol!="["&&symbol!="]"&&symbol!="="&&symbol!="/")
        {
            if (degree[i-1]<3)
                degree[i-1]=3;
            if (degree[i+1]<3)
                degree[i+1]=3;
        }

    }

    if (symbol == "|")
    {
        if (degree.back()<1)
            degree.back()=1;
    }
    else if (symbol == "&")
    {
        if (degree.back()<2)
            degree.back()=2;
    }
    else if (symbol == "...")
    {
        if (degree.back()<4)
            degree.back()=4;
    }
    else if (symbol!="("&&symbol!=")"&&symbol!="["&&symbol!="]"&&symbol!="="&&symbol!="/")
    {
        if (degree.back()<3)
            degree.back()=3;
    }



    for(int i=0; i<output_word.get_size();i++)
    {
        std::string symbol = output_word.get_symbol_at(i);
        if (symbol == "(")
            output_word.tag_at(i, "BRACKET_L");
        else if (symbol == ")")
            output_word.tag_at(i, "BRACKET_R");
        else if (symbol == "[")
            output_word.tag_at(i, "OPTION_L");
        else if (symbol == "]")
            output_word.tag_at(i, "OPTION_R");
        else if (symbol == "/")
            output_word.tag_at(i, "SLASH");
        else if (symbol == "=")
            output_word.tag_at(i, "SEPARATOR");
        else if (symbol == "...")
            output_word.tag_at(i, "OPTIONAL_REPETITION");
        else
            output_word.tag_at(i, ("S"+std::to_string(degree[i])));
    }

    return output_word;
}
