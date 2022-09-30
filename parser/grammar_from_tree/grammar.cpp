#include "grammar_from_tree/grammar.h"


 std::ostream&  operator << (std::ostream& s, const Grammar_from_tree &g)
{
    s << "Nonterminals: ";
    for (std::pair<std::string, std::unordered_set<int>> vn: g.nonterminals)
        s<< vn.first << ", ";
    s << "\nTerminals: ";
    for (std::pair<std::string, std::unordered_set<int>> vt: g.terminals)
        s<< vt.first << ", ";

    s << "\nHead: " << g.head << "\n";

    s<< "\n";
    for( std::pair<int, Rule> r: g.rules)
    {
        s<< r.second.left << " -> ";
        for (std::string str: r.second.right)
            s<< str <<" ";
        s<< "\n";
    }
    return s;
}

Word Grammar_from_tree::terminals_to_word()
{
    Word output;
//    std::cout << "------------terminals2word-------------\n";
    for (std::pair<std::string, std::unordered_set<int>> t:terminals)
    {
        output.insert_symbol(t.first);
//        std::cout << t.first <<"\n";
    }

//    std::cout << "----------finishing terminals2word---------\n";
    return output;
}

void Grammar_from_tree::transform_terminals( std::unordered_map<std::string, std::string> transforming_dictionary)
{

    for(std::pair<int, Rule> &rule: rules)
    {
        for (std::string &symbol: rule.second.right)
        {
            if(transforming_dictionary.contains(symbol))
                symbol = transforming_dictionary[symbol];
        }
    }

    terminals.clear();

    update(); //the new terminals will be generated again from the rules, just as in case of first rule creationn
}

void Grammar_from_tree::add_rules_with_id(const std::vector<std::pair<int, Rule>>& new_rules )
{
    for (std::pair<int, Rule> r: new_rules)
        rules.push_back(r);
}

std::vector<std::pair<int, Rule>>  Grammar_from_tree::get_rules_with_id()
{
    return rules;
}

void Grammar_from_tree::clear_rules()
{
    rules.clear();
}

void Grammar_from_tree::set_rules(const std::vector<Rule> & input_rules)
{
    for (Rule r: input_rules)
        rules.push_back({-1,r});
}

void Grammar_from_tree::update()
{
    //does all the below and also adds mapping between symbols and the rules where they're present

    //remove duplicate rules


    std::vector<std::pair<int, Rule>> new_rules;

    for (int i=0; i<rules.size(); i++)
    {
        bool already_there = false;
        for (int j=0; j<i; j++)
            if (rules[i].second.left == rules[j].second.left && rules[i].second.right == rules[j].second.right)
        {
            already_there = true;
//            std::cout << "found duplicate " << rules[i].second.left << " -> " << rules[i].second.right[0] << " " << rules[i].second.right[1] <<"\n";
        }
        if (!already_there)
            new_rules.push_back(rules[i]);

    }

    rules = new_rules;
    nonterminals.clear();
    terminals.clear();

//    std::sort(rules.begin(), rules.end());
//    std::unique(rules.begin(), rules.end());

    //adding symbols to terminals
    for (int i = 0; i<rules.size(); i++)
    {
        nonterminals[rules[i].second.left].insert(i);
        for (std::string r: rules[i].second.right)
            terminals[r].insert(i);
    }

    //update nonterminals

    for (std::pair<int, Rule> r: rules)
    {
        if (terminals.contains(r.second.left)) //the symbols to the left cannot be terminal
        {
            for (int rule_id: terminals[r.second.left])
                nonterminals[r.second.left].insert(rule_id);
            terminals.erase(r.second.left);
        }
    }

}

std::vector<Rule> Grammar_from_tree::get_rules()
{
    std::vector<Rule> clean_rules;
    for (std::pair<int, Rule> r: rules)
        clean_rules.push_back(r.second);
    return clean_rules;
}

std::string Grammar_from_tree::get_head()
{
    return head;
}


std::vector<std::string> Grammar_from_tree::get_nonterminals()
{
    std::vector<std::string> result;
    for (std::pair<std::string, std::unordered_set<int>> vn: nonterminals)
        result.push_back(vn.first);
    return result;
}
std::vector<std::string> Grammar_from_tree::get_terminals()
{
    std::vector<std::string> result;
    for (std::pair<std::string, std::unordered_set<int>> vt: terminals)
        result.push_back(vt.first);
    return result;
}


void Grammar_from_tree::set_head(const std::string&h)
{
    head = h;
}

void Grammar_from_tree::set_nonterminals(const std::vector<std::string> & _nonterminals)
{
    //TO DO
}
void Grammar_from_tree::set_terminals(const std::vector<std::string> & _terminals)
{
    //TO DO
}
