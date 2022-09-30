#include "grammar_from_tree/rule_transformer.h"

Rule_transformer::Rule_transformer(Logger *l): logger(l)
{

}

Terminal_tagger::Terminal_tagger(Logger *l ): Rule_transformer(l), Part_of_speech_tagger(l)
{

}

//#include <iostream>

Grammar_from_tree* Terminal_tagger::transform( Grammar_from_tree* grammar)
{
//    std::cout << "starting to tag the grammar\n";

//    Word * terminal_word = new Word(grammar->terminals_to_word());

    Tagger * tagger = new Part_of_speech_tagger(Part_of_speech_tagger::logger);

    std::unordered_set<std::string> terminals;
    for (std::string vt: grammar->get_terminals())
        terminals.insert(vt);

//    std::cout << "created set of terminals\n";
    std::vector<std::pair<int, Rule>> rules = grammar->get_rules_with_id();

//    std::cout << "obtained the rules\n";
    for (int i = 0; i<rules.size(); i++)
    {
//        std::cout << rules[i].first << ". " << rules[i].second.left << " -> " << rules[i].second.right[0] << " " << rules[i].second.right[1] << "\n";
        bool all_ok = true;
        std::vector<std::string> tags;

        for (int j=0; j<rules[i].second.right.size(); j++)
        {

            std::string symbol = rules[i].second.right[j];
            if (terminals.contains(symbol))
            {
                bool tagged = false;

                for (std::pair<std::regex, std::string> classificator: classificators)
                {
                    if (!tagged)
                        if (std::regex_match(symbol, classificator.first))
                        {
                            tagged = true;
                            tags.push_back(classificator.second);
                        }
                }
                if (!tagged)
                {
                    all_ok = false;
                    Part_of_speech_tagger::logger->log_error(rules[i].first, "Grammar parsing error! can't tokenize " + symbol + "\n");
                    break;
                }

            }
        }
        if (all_ok)
        {
            for (int j=0; j<tags.size(); j++)
                rules[i].second.right[j] = tags[j];
        }
    }

//    std::cout << "all tagged\n";

    if (!rules.empty())
    {
        grammar->clear_rules();
        grammar->add_rules_with_id(rules);
    }
    else
    {
        delete grammar;
        grammar = nullptr;
    }

//     std::cout << "all done\n";


    delete tagger;

    return grammar;
  }
