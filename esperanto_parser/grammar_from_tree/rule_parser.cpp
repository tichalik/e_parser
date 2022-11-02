#include "grammar_from_tree/rule_parser.h"

#include <iostream>



Rule_parser::Rule_parser(Logger * l): logger(l)
{

}

void Rule_parser::add_valency(std::list<std::pair<std::string, int>> & stack)
{
    auto i = stack.rbegin(); ///starting at the top
    i++; /// we don't care about the current top -- need to increment the value of the preceeding nonterminal
    auto j = i;
    while( i!=stack.rend() && (j->second==-1 || j->second==2)) ///we do not increment the valency of nonterminals (-1) and terminals with full arguments
    {
        j = i;
        i++;
    }

    j->second ++;
}

Grammar_from_tree* Rule_parser::parse(const std::vector<std::pair<int, std::string>> & input)
{
    Grammar_from_tree* output_grammar = new Grammar_from_tree;
    for (int i=0; i<input.size(); i++) ///for each line
    {
        std::string input_string = input[i].second;

        std::list<std::pair<std::string, int>> parsing_stack; ///pairs of symbol and valency (number of arguments provided)
        bool corrupted = false;

        std::string current;

        std::vector<std::pair<int, Rule>> obtained_rules;
        int pos = 0;

//
        for(char c: input_string)
        {

            if (c=='[')  ///new subtree beginning -- pushing the current tag onto stack
            {
                if (!current.empty())
                {
                    parsing_stack.push_back({current, 0}); /// 0 means that the symbol is nonterminal
                    current.clear();
                    add_valency(parsing_stack);
                }
                else
                {
                    logger->log_error(input[i].first, "Grammar parsing error! \n" + input_string.substr(0,pos+1) + " unexpected bracket \n" ) ;
                    corrupted = true;
                    break;
                }
            }
            else if (c==']') ///subtree ending -- stack reduction
            {
                if (parsing_stack.size()>=2) ///required at least LHS RHS1
                {

                    if (!current.empty()) ///pushing the last read word to the stack (required for updating valency)
                    {
                        parsing_stack.push_back({current, -1}); /// -1 means that the symbol is terminal
                        current.clear();
                        add_valency(parsing_stack);
                    }

                    std::pair<std::string, int> left, right1, right2;

                    right2 = parsing_stack.back();
                    parsing_stack.pop_back();

                    right1 = parsing_stack.back();
                    parsing_stack.pop_back();

                    left = parsing_stack.back();
                    //parsing_stack.pop();
                    /// no popping! the tag must reamain on top

                    ///checking for valency errors (tokens having too few arguments)
                    if (right1.second ==1) ///only one argument provided
                    {
                        logger->log_error(input[i].first, "Grammar parsing error! " + input_string.substr(0,pos+1) + " " + right1.first + " has only 1 argument provided\n" ) ;
                        corrupted = true;
//                        break;
                    }
                    else if (right1.second ==0) ///opened a bracket but no argument provided
                    {
                        logger->log_error(input[i].first, "Grammar parsing error! " + input_string.substr(0,pos+1) + " no arguments provided to " + right1.first +  "  which was marked as nonterminal\n" ) ;
                        corrupted = true;
//                        break;
                    }
                    if (right2.second ==1)
                    {
                        logger->log_error(input[i].first, "Grammar parsing error! " + input_string.substr(0,pos+1) + " " + right2.first + " has only 1 argument provided\n" ) ;
                        corrupted = true;
//                        break;
                    }
                    else if (right2.second ==0)
                    {
                        logger->log_error(input[i].first, "Grammar parsing error! " + input_string.substr(0,pos+1) + " no arguments provided to " + right2.first +  "  which was marked as nonterminal\n" ) ;
                        corrupted = true;
//                        break;
                    }
                    else if (!corrupted && left.second == 2) ///everything's ok
                    {
                        obtained_rules.push_back({input[i].first, {left.first, {right1.first, right2.first}}});
                    }
                    else ///some other problem
                    {
                        logger->log_error(input[i].first, "Grammar parsing error! " + input_string.substr(0,pos+1) + " required 2 arguments for " + left.first + "\n" ) ;
                        corrupted = true;
//                        break;
                    }

                    if (corrupted)
                        break;

//                    std::cout <<( "making new rule: " + left.first + "(" + std::to_string(left.second) + ") -> "+ right1.first +"(" +std::to_string(right1.second ) + ") "  +right2.first + "("+std::to_string(right2.second)+")\n");


                }
                else ///there aren't enough tokens on the stack to get a rule
                {

                    std::string message = "Grammar parsing error! " + input_string.substr(0,pos+1) +" <---- Not enough arguments, contents of the stack: " ;

                    while(!parsing_stack.empty())
                    {
                        message += parsing_stack.back().first + ",";
                        parsing_stack.pop_back();
                    }
                    message = message.substr(0,message.size()-1) +"\n";

//                    std::cout << message;

                    logger->log_error(input[i].first, message) ;
                    corrupted = true;
                    break;
                }
            }
            else if (c==' ') ///pushing current token to the stack
            {
                if (!current.empty())
                {
                    parsing_stack.push_back({current, -1});
                    current.clear();
                    add_valency(parsing_stack);
                }
            }
            else /// any other character -- concatenation to current
            {
                current += c;
            }
             pos++;
        }
        if (!corrupted)
        {
            output_grammar->add_rules_with_id(obtained_rules);
        }
//        std::cout << "parsed " << i+1 << "/" << input.size() << "\n";

    }
//
//    std::cout << "all rules parsed\n";

  //  output_grammar.print_all();

    output_grammar->update();

    return output_grammar;
}
