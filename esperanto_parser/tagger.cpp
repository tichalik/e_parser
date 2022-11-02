#include "tagger.h"

Tagger::Tagger(Logger * _logger):logger(_logger)
{

}


Part_of_speech_tagger::Part_of_speech_tagger(Logger * _logger): Tagger(_logger)
{

}

std::pair<int, Word*> Part_of_speech_tagger::tag(std::pair<int, Word*> input)
{
    Word* output_word  = input.second;
    ///no critical error occurs
    bool all_ok = true;

    ///for each symbol
    for (int i=0; i<output_word->get_size(); i++)
    {
        bool tagged = false;
        ///trying to match it to any regex
        for (std::pair<std::regex, std::string> classificator: classificators)
        {
//            if (output_word->get_tag_at(i)=="")
                ///match found
                if (std::regex_match(output_word->get_symbol_at(i), classificator.first))
                {
                    tagged = true;
                    ///insert the tag
                    output_word->tag_at(i, classificator.second);
                    ///no need to check for other regexes
                    break;
                }
        }
        ///there was no regex fitting
        if (!tagged)
        {
            ///critical error
            all_ok = false;
            logger->log_error(input.first, "Error! can't tokenize " + output_word->get_symbol_at(i)+ "\n");
            ///deallocating corrupted word
            delete output_word;
            output_word = nullptr;
            ///if one symbol is corrupted, no need to check for other
            break;
        }

    }


    return {input.first, output_word};
}
