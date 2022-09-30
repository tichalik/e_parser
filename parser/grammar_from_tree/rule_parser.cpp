#include "grammar_from_tree/rule_parser.h"

#include <iostream>



Rule_parser::Rule_parser(Logger * l): logger(l)
{

}

void Rule_parser::add_valency(std::list<std::pair<std::string, int>> & stack)
{

    auto i = stack.rbegin();
//    std::cout << "\tadding valency, the current top is " << i->first << "\n";
    i++; //skipping the current top
    auto j = i;
    while( i!=stack.rend() && (j->second==-1 || j->second==2))
    {
        j = i;
        i++;
    }

    j->second ++;
}

Grammar_from_tree* Rule_parser::parse(const std::vector<std::pair<int, std::string>> & input)
{
    Grammar_from_tree* output_grammar = new Grammar_from_tree;
    for (int i=0; i<input.size(); i++)
    {
        std::string input_string = input[i].second;

        std::list<std::pair<std::string, int>> parsing_stack;
        bool corrupted = false;

        std::string current;

        std::vector<std::pair<int, Rule>> obtained_rules;
        int pos = 0;

//
        for(char c: input_string)
        {

            if (c=='[')
            {
                if (!current.empty())
                {
                    parsing_stack.push_back({current, 0});
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
            else if (c==']')
            {
                if (parsing_stack.size()>=3)
                {

                    if (!current.empty())
                    {
                        parsing_stack.push_back({current, -1});
                        current.clear();
                        add_valency(parsing_stack);
                    }

                    std::pair<std::string, int> left, right1, right2;

                    right2 = parsing_stack.back();
                    parsing_stack.pop_back();

                    right1 = parsing_stack.back();
                    parsing_stack.pop_back();

                    left = parsing_stack.back();
                    //parsing_stack.pop(); //the tag must reamain on top

                    if (right1.second ==1)
                    {
                        logger->log_error(input[i].first, "Grammar parsing error! " + input_string.substr(0,pos+1) + " " + right1.first + " has only 1 argument provided\n" ) ;
                        corrupted = true;
                        break;
                    }
                    else if (right1.second ==0)
                    {
                        logger->log_error(input[i].first, "Grammar parsing error! " + input_string.substr(0,pos+1) + " no arguments provided to " + right1.first +  "  which was marked as nonterminal provided\n" ) ;
                        corrupted = true;
                        break;
                    }
                    else if (right2.second ==1)
                    {
                        logger->log_error(input[i].first, "Grammar parsing error! " + input_string.substr(0,pos+1) + " " + right2.first + " has only 1 argument provided\n" ) ;
                        corrupted = true;
                        break;
                    }
                    else if (right2.second ==0)
                    {
                        logger->log_error(input[i].first, "Grammar parsing error! " + input_string.substr(0,pos+1) + " no arguments provided to " + right2.first +  "  which was marked as nonterminal provided\n" ) ;
                        corrupted = true;
                        break;
                    }
                    else if (left.second == 2)
                    {
                        obtained_rules.push_back({input[i].first, {left.first, {right1.first, right2.first}}});
                    }
                    else
                    {
                        logger->log_error(input[i].first, "Grammar parsing error! " + input_string.substr(0,pos+1) + "      required 2 arguments for " + left.first + ", " + std::to_string(left.second) + " provided\n" ) ;
                        corrupted = true;
                        break;
                    }

//                    std::cout <<( "making new rule: " + left.first + "(" + std::to_string(left.second) + ") -> "+ right1.first +"(" +std::to_string(right1.second ) + ") "  +right2.first + "("+std::to_string(right2.second)+")\n");


                }
                else
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
            else if (c==' ')
            {
                if (!current.empty())
                {
                    parsing_stack.push_back({current, -1});
                    current.clear();
                    add_valency(parsing_stack);
                }
            }
            else //any other character
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
