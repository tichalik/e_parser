#include "grammar_from_XML/grammar.h"

Grammar_from_XML::Grammar_from_XML(const std::unordered_set<std::string> & _nonterminals,
            const std::unordered_set<std::string> & _terminals,
            const std::string & _head,
            const std::vector<Rule> & _rules):
                nonterminals(_nonterminals), terminals(_terminals), head(_head)
{
    for (Rule r: _rules)
        rules[r.left].push_back(r.right);
}



std::vector<std::string> Grammar_from_XML::get_nonterminals()
{
    std::vector<std::string> result;
    for (std::string s : nonterminals)
        result.push_back(s);

    return result;
}
std::vector<std::string> Grammar_from_XML::get_terminals()
{
    std::vector<std::string> result;
    for (std::string s : terminals)
        result.push_back(s);

    return result;
}
std::string Grammar_from_XML::get_head()
{
    return head;
}
std::vector<Rule> Grammar_from_XML::get_rules()
{
    std::vector<Rule> result;
    for (std::pair<std::string, std::vector<std::vector<std::string>>> r: rules)
        for (std::vector<std::string> v: r.second)
            result.push_back({r.first, v});

    return result;
}

void Grammar_from_XML::set_nonterminals(const std::vector<std::string> & _nonterminals)
{
    nonterminals.clear();
    for (std::string v: _nonterminals)
        nonterminals.insert(v);
}
void Grammar_from_XML::set_terminals(const std::vector<std::string> & _terminals)
{
    terminals.clear();
    for (std::string v: _terminals)
        terminals.insert(v);
}
void Grammar_from_XML::set_head(const std::string & _head)
{
    head = _head;
}
void Grammar_from_XML::set_rules(const std::vector<Rule> & _rules)
{
    rules.clear();
    for (const Rule & r: _rules )
        rules[r.left].push_back(r.right);
}
