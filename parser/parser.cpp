#include "parser.h"


//Parser::Parser(Grammar* g, Buffer<Word>* _input, Buffer<Parsing_node> * _output): grammar(g), input_buffer(_input), output_buffer(_output)
//{
//
//}
Parser::Parser(Grammar* g, Logger * l): grammar(g), logger(l)
{

}


CYK_parser::CYK_parser(Grammar* g, Logger * l): Parser(g,l)
{
//    logger->log_message("creating map of rules");
    for (Rule r: grammar->get_rules())
    {
        std::string rule_body = r.right[0]+" "+ r.right[1];

//        if (rule_map[rule_body].size()!=0)
//        {
//            std::string message = "ambiguous rule detected. " + rule_body + "can turn into ";
//            for (std::string option: rule_map[rule_body])
//                message += option +", ";
//            message+="\n";
//            logger->log_message(message);
//        }
        rule_map[rule_body].push_back(r.left);
    }

//    for (std::pair< std::string, std::vector<std::string>> record: rule_map)
//    {
//        std::string tmp = record.first + " -> ";
//        for (std::string s: record.second)
//            tmp+= s +" ";
//        std::cout << tmp << "\n";
//    }

}


std::vector<std::pair<int, Parse_tree*>> CYK_parser::parse(std::pair<int, Word*> input)
{
    std::vector<std::pair<int, Parse_tree*>> output;
    bool all_ok = false;

    int n = input.second->get_size();

    std::vector<std::vector<std::vector<Parsing_node*>>> parsing_matrix;
    for (int i=0; i<n; i++)
    {
        parsing_matrix.push_back(std::vector<std::vector<Parsing_node*>>(n));

        Parsing_node* tmp = new Parsing_node;
        tmp->tag = input.second->get_tag_at(i);
        Parsing_node * leaf = new Parsing_node;
        leaf->tag = input.second->get_symbol_at(i);
        tmp->children.push_back(leaf);
        parsing_matrix[0][i].push_back(tmp);

    }
//    std::cout << "first nodes created\n";

//    for (int i=0; i<n; i++)
//        std::cout << (parsing_matrix[0][i][0]->to_string()) << " ";
//    std::cout << "\n";
//    std::cout << "\nrule map size: " << rule_map.size() << "\n";

    for (int i=1; i<n; i++)
    {
        for (int j=0; j<n-i; j++)
        {
            for (int k=0; k<i; k++)
            {
                int dest_y = i;
                int dest_x = j;

                int sour1_y = k;
                int sour1_x = j;

                int sour2_y = i-k-1;
                int sour2_x = j+k+1;




//                 std::cout << "[" << dest_y << "," << dest_x <<"] -> ["<< sour1_y <<","<<sour1_x<<"] ["<<sour2_y<<","<<sour2_x<<"]\n";

                 for (Parsing_node* sour1: parsing_matrix[sour1_y][sour1_x])
                 {
                     for (Parsing_node* sour2: parsing_matrix[sour2_y][sour2_x])
                     {
                         std::string id = sour1->tag + " " +sour2->tag;
//                         std::cout << id << "\n";
                         if (rule_map.contains(id))
                         {
//                             std::cout << "it contains id\n";
                             for (std::string result: rule_map[id])
                             {
//                                 std::cout << "found node " << result << "\n";

                                 Parsing_node* dest = new Parsing_node;
                                 dest->tag = result;
                                 dest->children.push_back(sour1);
                                 dest->children.push_back(sour2);

                                 parsing_matrix[dest_y][dest_x].push_back(dest);


                             }
                         }
                     }
                 }
             }
        }
    }

    if (parsing_matrix[n-1][0].size()!=0)
    {

        for (int i=0; i<parsing_matrix[n-1][0].size(); i++)
            if (parsing_matrix[n-1][0][i]->tag == grammar->get_head())
            {
//                std::cout << parsing_matrix[n-1][0][i]->to_string() <<"\n";
                Parse_tree * tmp = new Parse_tree(parsing_matrix[n-1][0][i]->clone());
                output.push_back({input.first, tmp});
                all_ok = true;
            }

    }
    else
    {
        all_ok = false;
        std::string message = "PARSING ERROR! found nodes:\n";
        for (int i=1; i<n; i++)
        {
            for (int j=0; j<n-i; j++)
            {
                for (Parsing_node * p: parsing_matrix[i][j])
                {
                    message += p->to_string() + "\n";
                }
            }
        }
        logger->log_error(input.first, message);
    }


    for (int i=1; i<n; i++)
    {
        for (int j=0; j<n-i; j++)
        {
            for (Parsing_node * p: parsing_matrix[i][j])
            {
                delete p;
            }
        }
    }
    return output;
}
