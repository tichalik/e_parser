#ifndef GRAMMAR_FROM_XML_GRAMMAR
#define GRAMMAR_FROM_XML_GRAMMAR


#include "../grammar.h"

#include <unordered_map>
#include <unordered_set>

class Grammar_from_XML: public Grammar
 {
    std::unordered_set<std::string> nonterminals;
    std::unordered_set<std::string> terminals;
    std::string head;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> rules;
 public:
     Grammar_from_XML(const std::unordered_set<std::string> & _nonterminals,
            const std::unordered_set<std::string> & _terminals,
            const std::string & _head,
            const std::vector<Rule> & _rules);

    friend std::ostream& operator << (std::ostream& s, const Grammar &g);
    virtual std::vector<std::string> get_nonterminals();
    virtual std::vector<std::string> get_terminals();
    virtual std::string get_head();
    virtual std::vector<Rule> get_rules();

    virtual void set_nonterminals(const std::vector<std::string> & _nonterminals);
    virtual void set_terminals(const std::vector<std::string> & _terminals);
    virtual void set_head(const std::string & _head);
    virtual void set_rules(const std::vector<Rule> & _rules);
 };

 #endif // GRAMMAR_FROM_XML_GRAMMAR
