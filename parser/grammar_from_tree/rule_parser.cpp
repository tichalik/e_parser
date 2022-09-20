#include "grammar_from_tree/rule_parser.h"

#include <iostream>



//Rule_parser::Rule_parser(Buffer<std::string> * _input, Buffer<Grammar_from_tree> * _output): input_buffer(_input), output_buffer(_output)
//{
//
//}


Grammar_from_tree Rule_parser::parse(const std::vector<std::string> & input)
{
    Grammar_from_tree output_grammar;
    for (std::string input_string: input)
    {
        std::stack<std::string> parsing_stack; //name of symbol and whether its terminal
        parsing_stack.push({"", false});
 //       std::cout << "processing " << input_string <<"\n";

        bool corrupted = false;

        std::vector<Rule> obtained_rules;
        int pos = 0;

        for(char c: input_string)
        {

            if (c=='[')
            {
                if (!parsing_stack.empty())
                {
                    parsing_stack.push("");
                }
                else
                {
                    std::cout << "Parsing error! \n"<< input_string.substr(0,pos+1) << " <---- nothing on top of the stack\n"  ;
                    corrupted = true;
                }
            }
            else if (c==']')
            {
                if (parsing_stack.size()>=3)
                {

                    std::string left, right1, right2;

                    right2 = parsing_stack.top();
                    parsing_stack.pop();

                    right1 = parsing_stack.top();
                    parsing_stack.pop();

                    left = parsing_stack.top();
                    //parsing_stack.pop(); //the tag must reamain on top


                    obtained_rules.push_back({left, {right1, right2}});
                }
                else
                {
                    std::cout << "Parsing error! \n"<< input_string.substr(0,pos+1) << " <---- Not enough arguments\n"  ;
                    corrupted = true;
                }
            }
            else if (c==' ')
            {
                parsing_stack.push("");
            }
            else //any other character
            {
                if(!parsing_stack.empty())
                    parsing_stack.top() += c;
                else
                {
                    std::cout << "Parsing error! \n"<< input_string.substr(0,pos+1) << " <---- nothing on top of the stack\n"  ;
                    corrupted=true;
                }
            }
             pos++;
        }
        if (!corrupted)
            output_grammar.set_rules(obtained_rules);

    }



  //  output_grammar.print_all();

    output_grammar.update();

    return output_grammar;
}
