#include "grammar_from_tree/grammar.h"


std::string Grammar_from_tree::get_string_description()
{
    std::string s;
    s += "Nonterminals: ";
    for (std::pair<std::string, std::unordered_set<int>> vn: nonterminals)
        s+= vn.first + ", ";
    s += "\nTerminals: ";
    for (std::pair<std::string, std::unordered_set<int>> vt: terminals)
        s+= vt.first + ", ";

    s += "\nHead: " + head + "\n";

    s+= "\n";
    for( std::pair<int, Rule> r: rules)
    {
        s+= r.second.left + " -> ";
        for (std::string str: r.second.right)
            s+= str +" ";
        s+= "\n";
    }
    return s;
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
// to do
}

void Grammar_from_tree::update()
{
    //does all the below and also adds mapping between symbols and the rules where they're present

    ///remove duplicate rules


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


    ///updating nonterminals and terminals
    nonterminals.clear();
    terminals.clear();
    std::unordered_map<std::string, std::unordered_set<int>> possible_terminals;

    for (int i = 0; i<rules.size(); i++)
    {
        nonterminals[rules[i].second.left].insert(i); ///if it's on LHS it is a nonterminal
        for (std::string r: rules[i].second.right)
            possible_terminals[r].insert(i); ///if it's on RHS it might be a terminal
    }

    ///adding symbols to terminals
    for (std::pair<std::string, std::unordered_set<int>> v: possible_terminals )
    {
        if (!nonterminals.contains(v.first)) ///if the symbol is present in nonterminals it cannot be terminal
            terminals[v.first] = v.second;
    }


}

std::vector<Rule> Grammar_from_tree::get_rules()
{
    ///converting from internal representation to one dictated by interface
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
    ///converting from internal representation to one dictated by interface
    std::vector<std::string> result;
    for (std::pair<std::string, std::unordered_set<int>> vn: nonterminals)
        result.push_back(vn.first);
    return result;
}
std::vector<std::string> Grammar_from_tree::get_terminals()
{
    ///converting from internal representation to one dictated by interface
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
