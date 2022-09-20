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
    for( Rule r: g.rules)
    {
        s<< r.left << " -> ";
        for (std::string str: r.right)
            s<< str <<" ";
        s<< "\n";
    }
    return s;
}

Word Grammar_from_tree::terminals_to_word()
{
    Word output;
//    std::cout << "------------terminals2word-------------";
    for (std::pair<std::string, std::unordered_set<int>> t:terminals)
    {
        output.insert_symbol(t.first);
  //      std::cout << t.first <<"\n";
    }

    return output;
}

void Grammar_from_tree::transform_terminals( std::unordered_map<std::string, std::string> transforming_dictionary)
{

    for(Rule &rule: rules)
    {
        for (std::string &symbol: rule.right)
        {
            if(transforming_dictionary.contains(symbol))
                symbol = transforming_dictionary[symbol];
        }
    }

    terminals.clear();

    update(); //the new terminals will be generated again from the rules, just as in case of first rule creationn
}

void Grammar_from_tree::set_rules(const std::vector<Rule> & input_rules)
{
    for (Rule r: input_rules)
        rules.push_back(r);
}

void Grammar_from_tree::update()
{
    //does all the below and also adds mapping between symbols and the rules where they're present

    //remove duplicate rules

//    std::ranges::sort(test);

//    std::ranges::sort(rules); //teoretycznie to by siê da³o na ranges zrobiæ, ale z jakiegoœ powodu to nie dzia³a, chocia¿ dla normalnego wektora intów ju¿ tak



    std::vector<Rule> tmp_rules;
    bool aready_there;
    for (Rule r: rules)
    {
        aready_there = false;
        for (Rule ru: tmp_rules)
            if (ru == r)
                aready_there = true;
        if (!aready_there)
            tmp_rules.push_back(r);
    }
    rules = tmp_rules;

//    std::sort(rules.begin(), rules.end());
//    std::unique(rules.begin(), rules.end());

    //adding symbols to terminals
    for (int i = 0; i<rules.size(); i++)
    {
        nonterminals[rules[i].left].insert(i);
        for (std::string r: rules[i].right)
            terminals[r].insert(i);
    }

    //update nonterminals

    for (Rule r: rules)
    {
        if (terminals.contains(r.left)) //the symbols to the left cannot be terminal
        {
            for (int rule_id: terminals[r.left])
                nonterminals[r.left].insert(rule_id);
            terminals.erase(r.left);
        }
    }

}

std::vector<Rule> Grammar_from_tree::get_rules()
{
    return rules;
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
