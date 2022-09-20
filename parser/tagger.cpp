#include "tagger.h"


#include <iostream>
Word Part_of_speech_tagger::tag(const Word & input)
{
    Word output_word (input);

//    for (int i=0; i<output_word.get_size(); i++)
//    {
//        std::function<bool(const std::pair<std::regex, std::string> &)> check_which_fits =
//            [&output_word,i](const std::pair<std::regex, std::string> &r)
//                {return std::regex_match(output_word.get_symbol_at(i), r.first);};
//
//        for(std::pair<std::regex, std::string> classificator: classificators
//            | std::views::filter(check_which_fits))
//                if (output_word.get_tag_at(i)=="")
//                    output_word.tag_at(i,classificator.second);
//                    //if we want to keep all the tags, then here it should just push it back to the vector of tags, nomatter the checking
//
//    }
    for (int i=0; i<output_word.get_size(); i++)
    {
        for (std::pair<std::regex, std::string> classificator: classificators)
        {
    //        std::regex r(classificator.first);
            if (output_word.get_tag_at(i)=="")
                if (std::regex_match(output_word.get_symbol_at(i), classificator.first))
                    output_word.tag_at(i, classificator.second);
        }
    }


//     std::cout << output_word << "\n-----------------------------\n";
    return output_word;
}
