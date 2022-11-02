
Binary_parser::Binary_parser(Grammar g, Buffer<Word>* _input, Buffer<Parsing_node> * _output): Parser(g, _input, _output)
{

}


void Binary_parser::parse()
{
    std::cout << "parsing!\n";
    std::unordered_map< std::string, std::string> rule_map;
    for (Rule r: grammar.get_rules())
    {
        rule_map[{r.right[0]+" "+ r.right[1]}] = r.left;
    }

    input_buffer -> print_all();
    Word input = input_buffer->pop();
    while(!input_buffer->is_eof())
    {
        std::string output;
        std::vector<Parsing_node> parsing_stack;

        parsing_stack.push_back({input.get_tag_at(0), {{input.get_symbol_at(0), {}}}});
        for(int j=1; j<input.get_size(); j++)
        {
            parsing_stack.push_back({input.get_tag_at(j), {{input.get_symbol_at(j), {}}}});

            Parsing_node n_left = parsing_stack[parsing_stack.size()-2];
            Parsing_node n_right = parsing_stack[parsing_stack.size()-1];


            while (rule_map.contains(n_left.tag +" "+ n_right.tag)&&parsing_stack.size()>1)
            {
                Parsing_node result;
                result.tag = rule_map[n_left.tag +" "+ n_right.tag];
                result.children.push_back(n_left);
                result.children.push_back(n_right);

                parsing_stack.pop_back();
                parsing_stack.pop_back();

                if(!parsing_stack.empty())
                {
                    n_right = result;
                    n_left = parsing_stack[parsing_stack.size()-1];
                }

                parsing_stack.push_back(result);
            }
        }

        Parsing_node result;
        if (parsing_stack.size()!=1)
        {
            result.tag = "STACK_NOT_REDUCED";
            for (Parsing_node p: parsing_stack)
                result.children.push_back(p);
        }
        else
            result = parsing_stack[0];


        output_buffer->push(result);

        input = input_buffer->pop();
    }

    output_buffer->set_end_of_input();

}
