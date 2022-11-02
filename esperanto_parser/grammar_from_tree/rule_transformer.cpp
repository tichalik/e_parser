#include "grammar_from_tree/rule_transformer.h"

Rule_transformer::Rule_transformer(Logger *l): logger(l)
{

}

Terminal_tagger::Terminal_tagger(Logger *l ): Rule_transformer(l), Part_of_speech_tagger(l)
{

}

//#include <iostream>

Grammar_from_tree* Terminal_tagger::transform( Grammar_from_tree* & grammar)
{

    ///obtaining a set of terminals for further reference
    std::unordered_set<std::string> terminals;
    for (std::string vt: grammar->get_terminals())
        terminals.insert(vt);


    ///going through each of the rules
    std::vector<std::pair<int, Rule>> rules = grammar->get_rules_with_id();

    for (int i = 0; i<rules.size(); i++)
    {
//        std::cout << rules[i].first << ". " << rules[i].second.left << " -> " << rules[i].second.right[0] << " " << rules[i].second.right[1] << "\n";
        bool all_ok = true;
        std::vector<std::string> new_symbols; /// symbols to which RHS will be rewritten

        for (int j=0; j<rules[i].second.right.size(); j++) ///going through each of the RHS (LHS cannot be terminal)
        {
            std::string symbol = rules[i].second.right[j];
            if (terminals.contains(symbol)) ///checking whether it is terminals
            {
                bool tagged = false;

                for (std::pair<std::regex, std::string> classificator: classificators) ///finding the right tag
                {
                    if (!tagged)
                        if (std::regex_match(symbol, classificator.first))
                        {
                            tagged = true;
                            new_symbols.push_back(classificator.second);
                        }
                }
                if (!tagged) /// no tag can be found
                {
                    all_ok = false;
                    Part_of_speech_tagger::logger->log_error(rules[i].first, "Grammar parsing error! can't tokenize " + symbol + "\n");
                    break;
                }

            }
            else
                new_symbols.push_back(symbol); /// if it's not terminal the the new symbol is identical to the old
        }
        if (all_ok) ///if no errors occurred RHS is replaced
        {
            rules[i].second.right = new_symbols;
        }
    }

//    std::cout << "all tagged\n";

    if (!rules.empty()) /// if there was at least one line that was read correctly
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

    return grammar;
  }
