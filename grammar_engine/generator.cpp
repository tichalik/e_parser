#include "generator.h"

Generator::Generator(const Logger& _logger, const Interface& _interface): logger(_logger), interface(_interface), ok(true)
{

}

bool Generator::is_ok()
{
    return ok;
}

Word Generator::generate__word(Grammar & grammar, const bool auto_picking)
{
    logger.log_message("------------------------------------------\n");

    ok = true;
    Word result(grammar.get_head());
    std::string prev_word = result.to_string();
    while (!result.is_end()&&ok)
    {
        Node & current = result.get_leftmost_leaf();
//      std::cout  << "ouo" << current.head << "\n";

//          std::cout << current.head << "\n";

        if (grammar.is_nonterminal(current.head))
        {
            int no_candidates = grammar.get_no_candidates(current.head);
            std::vector<std::string> choice;

            if (no_candidates==0)
            {
                ok = false;
                logger.log_error(-1,"no way to change " + current.head + " into a terminal symbol");
            }
            else
            {

                std::string mes1 = prev_word;
                std::string mes2 = current.head + " -> ";

                if (no_candidates==1)
                {
                    choice = grammar.get_candidates(current.head)[0];
                }
                else
                {
                    if (auto_picking)
                    {
                        choice = grammar.choose_random(current.head);
                    }
                    else
                    {
                        std::vector<std::vector<std::string>> candidates = grammar.get_candidates(current.head);
                        choice = candidates[interface.choose_candidate( mes1, current.head,candidates)];
                    }

                }


                for (std::string s: choice)
                {
                    current.children.push_back(Node(s));
                    mes2 += s + " ";
                }
                prev_word = result.to_string();
                logger.log_message(mes1 + " => " + prev_word + "\t("+mes2+")");


            }
        }
        result.next();
//        std::cout << ok << result.is_end() << "\n";
    }
    return result;
}

