#include "parser.h"


//Parser::Parser(Grammar* g, Buffer<Word>* _input, Buffer<Parsing_node> * _output): grammar(g), input_buffer(_input), output_buffer(_output)
//{
//
//}
Parser::Parser(Grammar* g, Logger * l): grammar(g), logger(l), is_ok(true)
{

}


CYK_parser::CYK_parser(Grammar* g, Logger * l): Parser(g,l)
{
    ///creating the rule map
    for (Rule r: grammar->get_rules())
    {
        ///all grammar rules should have 2 RHS symbols
        if (r.right.size()==2)
        {
             ///defining the key
            std::string rule_body = r.right[0]+" "+ r.right[1];
            ///connecting the head
            rule_map[rule_body].push_back(r.left);
        }
        ///there's a nonnormative rule
        else
        {
            is_ok = false;
            ///converting the rule to a text message
            std::string message = r.left + " -> ";
            for (const std::string & s: r.right)
                message+=s+" ";
            ///notifying the user
            logger->log_error("CRITICAL PARSING ERROR: The rule " + message + "cannot be parsed by CYK parser. \n");
        }

    }
}

Parser* CYK_parser::clone()
{
    CYK_parser * tmp = new CYK_parser(grammar, logger);
    tmp->rule_map = rule_map;

    return tmp;
}

std::vector<std::pair<int, Parse_tree*>> CYK_parser::parse(std::pair<int, Word*> input)
{

    ///size of the word
    const int n = input.second->get_size();

    ///matrix for parsing nodes
    ///triangle in first two dimensions represent all nodes of the tree
    ///last dimension is a vector of possible roots of subtrees
    std::vector<std::vector<std::vector<Parsing_node*>>> parsing_matrix;

    ///initializing the lowest row
    ///for each symbol of the input word
    for (int i=0; i<n; i++)
    {
        ///initializing the matrix cell
        parsing_matrix.push_back(std::vector<std::vector<Parsing_node*>>(n));

        ///creating a node for the nonterminal
        Parsing_node* tmp = new Parsing_node;
        tmp->tag = input.second->get_tag_at(i);
        ///creating a node for the terminal
        Parsing_node * leaf = new Parsing_node;
        leaf->tag = input.second->get_symbol_at(i);

        ///in parsing terminal turns into terminal
        tmp->children.push_back(leaf);

        ///placing it in place
        parsing_matrix[0][i].push_back(tmp);

    }

    ///for each level of the tree
    for (int i=1; i<n; i++)
    {
        ///for all the lower subtrees
        for (int j=0; j<n-i; j++)
        {
            for (int k=0; k<i; k++)
            {
                ///checking whether X -> Y Z

                ///coordinates of X
                int dest_y = i;
                int dest_x = j;

                ///coordinates of Y
                int sour1_y = k;
                int sour1_x = j;

                ///coordinates of Z
                int sour2_y = i-k-1;
                int sour2_x = j+k+1;


                ///checking every combination of previously found subtrees for Y and Z
                 for (Parsing_node* sour1: parsing_matrix[sour1_y][sour1_x])
                 {
                     for (Parsing_node* sour2: parsing_matrix[sour2_y][sour2_x])
                     {
                         ///key to `rule_map`
                         std::string id = sour1->tag + " " +sour2->tag;
                         ///checking whether Y and Z can turn into something in the given grammar
                         if (rule_map.contains(id))
                         {
                             ///if there are many possibilities of X, going through each of them
                             for (std::string result: rule_map[id])
                             {
                                ///adding new parse results to the matrix
                                 Parsing_node* dest = new Parsing_node;
                                 ///setting LHS
                                 dest->tag = result;
                                 ///setting RHS
                                 dest->children.push_back(sour1);
                                 dest->children.push_back(sour2);

                                 ///putting new node in place
                                 parsing_matrix[dest_y][dest_x].push_back(dest);

                             }
                         }
                     }
                 }
             }
         }
    }

    ///preparing the output variable
    std::vector<std::pair<int, Parse_tree*>> output;
    ///whether parsing was successful
    bool all_ok = false;

    ///if there is a root of the tree
    if (parsing_matrix[n-1][0].size()!=0)
    {
        ///for many roots -- ambiguous parses going through each of them
        for (int i=0; i<parsing_matrix[n-1][0].size(); i++)
            ///only allowed root is the head of the grammar
            if (parsing_matrix[n-1][0][i]->tag == grammar->get_head())
            {
                ///adding parse tree to the result
                ///creating a copy of all the nodes -- so that trees originating from the same sentence
                ///can be fully independent from each other
                Parse_tree * tmp = new Parse_tree(parsing_matrix[n-1][0][i]->clone());
                ///setting the result and the id of the line of its origin
                output.push_back({input.first, tmp});
                ///the parsing was successful
                all_ok = true;
            }

    }
    ///the tree has no root -- word could not be parsed
    else
    {
        ///preparing error message
        std::string message = "PARSING ERROR! found nodes:\n";
        ///for each parsing node
        for (int i=1; i<n; i++)
        {
            for (int j=0; j<n-i; j++)
            {
                for (Parsing_node * p: parsing_matrix[i][j])
                {
                    ///adding it to message
                    message += p->to_string() + "\n";
                }
            }
        }
        ///sending error message to the logger
        logger->log_error(input.first, message);
    }

    ///deallocating nodes in the parsing matrix
    for (int i=1; i<n; i++)
    {
        for (int j=0; j<n-i; j++)
        {
            for (Parsing_node * p: parsing_matrix[i][j])
            {
                ///do not delete its children -- they will be deallocated
                ///once the iterators reach them
                delete p;
            }
        }
    }

    return output;
}


bool CYK_parser::is_everything_ok()
{
    return is_ok;
}
