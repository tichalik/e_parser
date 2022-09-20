#include "parser.h"


//Parser::Parser(Grammar* g, Buffer<Word>* _input, Buffer<Parsing_node> * _output): grammar(g), input_buffer(_input), output_buffer(_output)
//{
//
//}
Parser::Parser(Grammar* g): grammar(g)
{

}


CYK_parser::CYK_parser(Grammar* g): Parser(g)
{
    for (Rule r: grammar->get_rules())
    {
        if (rule_map[r.right[0]+" "+ r.right[1]].size()!=0)
            std::cout << "OHO! NIEJEDNOZNACZNOSCIA! Dodanie nowej reguly. Regula " << r.right[0]+" "+ r.right[1] << " byla " <<rule_map[r.right[0]+" "+ r.right[1]][0] << " teraz bedzie tez " << r.left <<"\n";
        rule_map[{r.right[0]+" "+ r.right[1]}].push_back(r.left);
    }

//    for (std::pair< std::string, std::vector<std::string>> record: rule_map)
//    {
//        std::cout << record.first << "\n";
//    }

}


Parsing_node CYK_parser::parse(Word& input)
{
    Parsing_node output;


    int n = input.get_size();

    std::vector<std::vector<std::vector<Parsing_node>>> parsing_matrix;
    for (int i=0; i<n; i++)
    {
        parsing_matrix.push_back(std::vector<std::vector<Parsing_node>>(n));
    }

    //join together???

    for(int i=0; i<n; i++)
    {
        Parsing_node tmp;
        tmp.tag = input.get_tag_at(i);
        tmp.children.push_back({input.get_symbol_at(i), {}});
        parsing_matrix[0][i].push_back(tmp);

    }
//
//    for (int i=0; i<n; i++)
//        std::cout << (parsing_matrix[0][i][0].to_string()) << " ";
//    std::cout << "\n";
//    std::cout << "\nrule map size: " << rule_map.size() << "\n";

    for (int i=1; i<n; i++)
    {
        for (int j=0; j<n-i; j++)
        {
            for (int k=0; k<i; k++)
            {
                for (int l1=0; l1<parsing_matrix[k][j].size(); l1++)
                {
                    for (int l2=0; l2<parsing_matrix[i-k-1][j+k+1].size(); l2++)
                    {
//                        std::cout << parsing_matrix[k][j][l1].tag+ " " + parsing_matrix[i-k-1][j+k+1][l2].tag <<std::endl;
                        if (rule_map.contains(parsing_matrix[k][j][l1].tag+ " " + parsing_matrix[i-k-1][j+k+1][l2].tag))
                        {
                            for (std::string left: rule_map[parsing_matrix[k][j][l1].tag+ " " + parsing_matrix[i-k-1][j+k+1][l2].tag])
                            {
                                Parsing_node tmp ;
                                tmp.tag = left;

//                                std::cout << "("<<i<<","<<j<<","<<k<< ") found derrivation: \t" << tmp.tag << " -> " << parsing_matrix[k][j][l1].tag <<" " <<parsing_matrix[i-k-1][j+k+1][l2].tag << "\n";

                                tmp.children.push_back(Parsing_node(parsing_matrix[k][j][l1]));
                                tmp.children.push_back(Parsing_node(parsing_matrix[i-k-1][j+k+1][l2]));

                                parsing_matrix[i][j].push_back(tmp);
                            }
                        }
                    }
                }
            }
        }
    }

    if (parsing_matrix[n-1][0].size()!=0)
    {
        std::cout << "przeparsowano!\n";
        for (int i=0; i<parsing_matrix[n-1][0].size(); i++)
            if (parsing_matrix[n-1][0][i].tag == grammar->get_head())
            {
                std::cout << parsing_matrix[n-1][0][i].to_string() <<"\n";
                output =parsing_matrix[n-1][0][i];
            }

    }
    else
    {
        std::cout << "PARSING ERROR! found nodes:\n";
        for (int i=1; i<n; i++)
        {
            for (int j=0; j<n-i; j++)
            {
                for (Parsing_node p: parsing_matrix[i][j])
                {
                    std::cout << p.to_string() << "\n";
                }
            }
        }
    }

    return output;
}
