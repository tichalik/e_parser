#ifndef NORMALIZER
#define NORMALIZER

#include "grammar.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>

class Normalizer
{
    //changelog
public:
    virtual bool normalize(Grammar* grammar)=0;
};

class Half_chomskyficator: public Normalizer
{
public:
    virtual bool normalize(Grammar* grammar);
};

class Chomskyficator: public Normalizer
{
    struct Rule_RHS
    {
        std::vector<std::vector<std::string>> alternatives;
        std::vector<bool> visited;
        std::vector<std::string> paths_to_leaves;
    };

//    std::string to_chomsky_nonterminal(const std::string & current,
//                                       const std::unordered_map<std::string, std::vector<std::vector<std::string>>> &rules,
//                                       const std::unordered_set<std::string> & terminals);
public:
    virtual bool normalize(Grammar* grammar);
};

#endif // NORMALIZER
