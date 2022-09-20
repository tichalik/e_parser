#ifndef GRAMMAR
#define GRAMMAR

#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <random>

class Grammar
{
    std::unordered_set<std::string> nonterminals;
    std::unordered_set<std::string> terminals;
    std::string head;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> rules;

    std::uniform_real_distribution<double> d;
    std::default_random_engine engine;

public:
    Grammar(const std::unordered_set<std::string> & _nonterminals,
            const std::unordered_set<std::string> & _terminals,
            const std::string & _head,
            const std::vector<std::pair<std::string, std::vector<std::string>>> & _rules);

    friend std::ostream& operator << (std::ostream& s, const Grammar &g);

    std::unordered_set<std::string> get_nonterminals();
    std::unordered_set<std::string> get_terminals();
    std::string get_head();
    std::vector<std::pair<std::string, std::vector<std::string>>> get_rules();

    int get_no_candidates(const std::string& r_head);
    std::vector<std::vector<std::string>> get_candidates(const std::string & r_head);
    std::vector<std::string> choose_random(const std::string & r_head);

    bool is_nonterminal(const std::string & s);

};

#endif // GRAMMAR

