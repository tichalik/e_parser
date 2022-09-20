#include "grammar.h"

#include <iostream>

Grammar::Grammar(const std::unordered_set<std::string> & _nonterminals,
            const std::unordered_set<std::string> & _terminals,
            const std::string & _head,
            const std::vector<std::pair<std::string, std::vector<std::string>>> & _rules):
                nonterminals(_nonterminals), terminals(_terminals), head(_head)
{
    for (std::pair<std::string, std::vector<std::string>> r: _rules)
    {
        rules[r.first].push_back(r.second);
    }

}
std::unordered_set<std::string> Grammar::get_nonterminals()
{
    return nonterminals;
}
std::unordered_set<std::string> Grammar::get_terminals()
{
    return terminals;
}
std::string Grammar::get_head()
{
    return head;
}
std::vector<std::pair<std::string, std::vector<std::string>>> Grammar::get_rules()
{
    std::vector<std::pair<std::string, std::vector<std::string>>> result;
    for (std::pair<std::string, std::vector<std::vector<std::string>>> r: rules)
    {
        for (std::vector<std::string> rhs: r.second)
            result.push_back({r.first, rhs});
    }
    return result;
}

std::vector<std::vector<std::string>> Grammar::get_candidates(const std::string & r_head)
{
    return rules[r_head];
}
std::vector<std::string> Grammar::choose_random(const std::string & r_head)
{
    int random_index = (int) (d(engine) * rules[r_head].size());
    return rules[r_head][random_index];
}
bool Grammar::is_nonterminal(const std::string & s)
{
    return nonterminals.contains(s);
}

int Grammar::get_no_candidates(const std::string& r_head)
{
    return rules[r_head].size();
}

std::ostream& operator << (std::ostream &s, const Grammar &g)
{
    s << "nonterminals: ";
    for (std::string vn: g.nonterminals)
        s << "\n\t" << vn;
    s << "\nterminals: ";
    for (std::string vt: g.terminals)
        s << "\n\t" << vt;
    s << "\nhead: " <<g.head;
    s << "\nrules:";
    for (std::pair<std::string, std::vector<std::vector<std::string>>> rule: g.rules )
    {
        for (std::vector<std::string> rhs: rule.second)
        {
            s << "\n\t" << rule.first << " ::= ";
            for (std::string str: rhs)
                s << str << " ";
        }

    }

    return s;
}


