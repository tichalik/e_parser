#include "normalizer.h"
Normalizer::Normalizer(Logger * l): logger(l)
{

}
Half_chomskyficator::Half_chomskyficator(Logger * l): Normalizer(l)
{

}
Chomskyficator::Chomskyficator(Logger * l): Normalizer(l)
{

}


bool Half_chomskyficator::normalize(Grammar * original_grammar)
{
    std::unordered_set<std::string> old_nonterminals;
    for (std::string v:original_grammar->get_nonterminals())
        old_nonterminals.insert(v);


    std::vector<Rule> rules;
    std::unordered_set<std::string> added_nonterminals;


    bool all_ok = true;

    for (const Rule &r: original_grammar->get_rules())
    {
        if (r.right.size()<3)
            rules.push_back(r);
        else
        {
            std::string old_head = r.left;
            std::string new_head = r.left + "'";
            for (int i=0; i<r.right.size()-2; i++)
            {

                added_nonterminals.insert(new_head);
                rules.push_back({old_head, {r.right[i], new_head}});
                old_head = new_head;
                new_head += "'";


            }
            rules.push_back({old_head, {r.right[r.right.size()-2], r.right[r.right.size()-1]}});

        }
    }

    std::vector<std::string> new_nonterminals;

    for (std::string v: added_nonterminals)
        if (old_nonterminals.contains(v))
        {
            //errrorrr!!!!
            all_ok = false;
        }
        else
            new_nonterminals.push_back(v);


    for (std::string v: old_nonterminals)
        new_nonterminals.push_back(v);

    if (all_ok)
    {
        original_grammar->set_nonterminals(new_nonterminals);
        original_grammar->set_rules(rules);
    }

    return all_ok;
}

//std::string to_chomsky_nonterminal(const std::string & current, const std::string & name;
//                                       const std::unordered_map<std::string, std::vector<std::vector<std::string>>> &rules,
//                                       const std::unordered_set<std::string> & terminals)
//{
//   if (rules[current].size()==1) //only one possibility
//   {
//       if (rules[current][0].size()==2 //assuming it's not 2 terminals
//           || terminals.contains(rules[current][0][0]))
//                return "";
//       else
//       {
//           std::string new_name;
//           for (std::vector<std::string> child: rules[current])
//           {
//               for (std::string symbol: child)
//                    new_name += to_chomsky_nonterminal(symbol, name + current, rules, terminals) + "+";
//
//
//           }
//       }
//
//   }
//
//
//}


bool Chomskyficator::normalize(Grammar * original_grammar)
{
//    std::unordered_set<std::string> old_nonterminals;
//    for (std::string v:original_grammar->get_nonterminals())
//        old_nonterminals.insert(v);
//
//
//        //              rule.left       alternatives      visited?  the word   symbol
////    std::unordered_map<std::string, std::vector<std::pair<bool,std::vector<std::string>>>> rules;
//    std::unordered_map<std::string, Rule_RHS> rules;
//    std::unordered_set<std::string> added_nonterminals;
//
//    std::unordered_set<std::string> terminals;
//    for (std::string t: original_grammar->get_terminals())
//        terminals.insert(t);
//
//
//    bool all_ok = true;
//
//    std::vector<Rule> fixed_terminals_rules;
//
//    //removing terminals from nonsingular rules
//    for (Rule r: original_grammar->get_rules())
//    {
//        if (r.right.size()!=1)
//        {
//            for (int i=0; i<r.right.size(); i++)
//            {
//                if (terminals.contains(r.right[i]))
//                {
//                    std::string tmp = r.right[i];
//                    r.right[i] += "'";
//                    added_nonterminals.insert(r.right[i]);
//                    fixed_terminals_rules.push_back({r.right[i], tmp});
//                }
//            }
//        }
//        fixed_terminals_rules.push_back(r);
//
//    }
//
//
//    //binarizing the rules
//    for (const Rule &r: fixed_terminals_rules)
//    {
//        if (r.right.size()<3)
//        {
//            rules[r.left].alternatives.push_back(r.right);
//            rules[r.left].visited.push_back(false);
//        }
//        else
//        {
//            std::string old_head = r.left;
//            std::string new_head = r.left + "'";
//            for (int i=0; i<r.right.size()-2; i++)
//            {
//
//                added_nonterminals.insert(new_head);
////                rules[old_head].push_back({false,});
////
//                rules[old_head].alternatives.push_back({r.right[i], new_head});
//                rules[old_head].visited.push_back(false);
//
//                old_head = new_head;
//                new_head += "'";
//
//
//            }
////            rules[old_head].push_back({false, });
//
//            rules[old_head].alternatives.push_back({r.right[r.right.size()-2], r.right[r.right.size()-1]});
//            rules[old_head].visited.push_back(false);
//
//        }
//    }
//
//
//
//
//    std::string current = original_grammar->get_head();
//    std::stack<std::string> path;
//
//    do
//    {
//        //gettting to the botttom
//        bool bottom = false;
//        int pos = 0;
//        while(!bottom)
//        {
//            bool all_visited = true;
//            for (; pos<rules[current].visited.size(); pos++)
//            {
//                if (rules[current].visited[pos]==false)
//                {
//                    if (rules[current].alternatives[pos].size()==2 || terminals.contains(rules[current].alternatives[pos][0]))
//                    {
//                        bottom = true;
//                        rules[current].visited[pos]= true;
//                        break;
//                    }
//                    else
//                    {
//                        all_visited = false;
//                        rules[current].visited[pos]= true;
//                        path.push(current);
//                        current = rules[current].alternatives[pos][0];
//                        break;
//                    }
//
//                }
//            }
//            if (all_visited)
//                bottom = true;
//        }
//
//        //we arrived at the bottom
//
//        if (terminals.contains(rules[current].alternatives[pos][0]))
//        {
//            rules[current].paths_to_leaves.push_back(current);
//        }
//        else
//        {
//            std::string first = rules[current].alternatives[pos][0];
//            for (std::string s: rules[first].paths_to_leaves)
//                rules[current].paths_to_leaves.push_back(s+ "+" + current)
//
//            if (rules[current].alternatives[pos].size() == 2)
//            {
//                std::string second = rules[current].alternatives[pos][1];
//                for (std::string s: rules[second].paths_to_leaves)
//                    rules[current].paths_to_leaves.push_back(s+ "+" + current)
//            }
//        }
//
//
//    }




}
