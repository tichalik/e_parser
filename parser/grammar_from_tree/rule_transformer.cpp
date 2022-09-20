#include "grammar_from_tree/rule_transformer.h"

Rule_transformer::Rule_transformer()
{

}

Terminal_tagger::Terminal_tagger( )
{

}

#include <iostream>

Grammar_from_tree Terminal_tagger::transform( Grammar_from_tree & grammar)
{

    Word before_word = grammar.terminals_to_word();


    Tagger * tagger = new Part_of_speech_tagger;
    Word after_word  = tagger->tag(before_word);


    std::unordered_map<std::string, std::string> transforming_dictionary;
    for (int i=0; i<after_word.get_size(); i++)
    {
        transforming_dictionary[after_word.get_symbol_at(i)] = after_word.get_tag_at(i);
    }

    grammar.transform_terminals(transforming_dictionary);
  //  grammar.update();

    delete tagger;

    return grammar;
  }
