#include "grammar_from_XML/normalizer.h"
Normalizer::Normalizer(Logger * l): logger(l)
{

}
Binarizer::Binarizer(Logger * l): Normalizer(l)
{

}

bool Binarizer::normalize(Grammar_from_XML * & original_grammar)
{
    ///obtaining original nonterminals
    std::unordered_set<std::string> old_nonterminals;
    for (std::string v:original_grammar->get_nonterminals())
        old_nonterminals.insert(v);


    ///the new rules of a grammar
    std::vector<Rule> rules;
    ///nonterminals that have been added in the normalization process
    std::unordered_set<std::string> added_nonterminals;


    ///whether a critical error occured
    bool all_ok = true;

    ///going through each rule of the original grammar
    for (const Rule &r: original_grammar->get_rules())
    {
        ///if RHS has 1 or 2 symbols
        if (r.right.size()<3)
            ///the rule is included in the new rules
            rules.push_back(r);
        ///if RHS has more than  symbols
        else
        {
            ///the normalization process
            ///transforming rule X->Y Z W into X->Y X' ; X'->Z W

            ///obtaining X
            std::string old_head = r.left;
            ///obtaining X'
            std::string new_head = r.left + "'";
            ///creating new 'primed' rules until two last symbols in RHS are reached
            for (int i=0; i<r.right.size()-2; i++)
            {
                ///including new nonterminal
                added_nonterminals.insert(new_head);
                ///adding the X->Y X' rule
                rules.push_back({old_head, {r.right[i], new_head}});
                ///succesion - the next normalization step will take X' -> Z W Q into X'->Z X''; X''->W Q
                old_head = new_head;
                new_head += "'";
            }
            ///adding the X'-> Z W rule
            rules.push_back({old_head, {r.right[r.right.size()-2], r.right[r.right.size()-1]}});

        }
    }

    std::vector<std::string> new_nonterminals;

    ///looking for conflicts between old and new nonterminals
    for (std::string v: added_nonterminals)
        ///the symbol used for a new nonterminal has been used somewhere in the original grammar
        if (old_nonterminals.contains(v))
        {
            ///critical error -- transformed grammar is not equivalent to the original one
            all_ok = false;
//            std::cout << ("Normalization error: symbol " + v + " used in transformation" +
//                              "already exists in the original grammar. Please rename it to something else");
            logger->log_error("Normalization error: symbol " + v + " used in transformation" +
                              "already exists in the original grammar. Please rename it to something else");
        }
        else
            new_nonterminals.push_back(v);


    ///grammar's nonterminals will be completely cleared
    for (std::string v: old_nonterminals)
        new_nonterminals.push_back(v);

    ///no critical error occurred
    if (all_ok)
    {
        ///replacing old nonterminals
        original_grammar->set_nonterminals(new_nonterminals);
        ///replacing old rules
        original_grammar->set_rules(rules);
    }
    else
    {
        ///clearing corrupted grammar
//        std::cout << "atttempting to delete the grammar\n";
        delete original_grammar;
        original_grammar = nullptr;
    }

    return all_ok;
}
