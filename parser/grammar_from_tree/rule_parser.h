#ifndef GRAMMAR_FROM_TREE_RULE_PARSER
#define GRAMMAR_FROM_TREE_RULE_PARSER

#include <string>
#include <vector>
#include <stack>
#include <future>

#include "grammar.h"
#include "../logger.h"


/** \brief creates grammar from rules represented as input strings
 *
 */

class Rule_parser
{
    Logger * logger;
    void add_valency(std::list<std::pair<std::string, int>> & stack);
public:

    Rule_parser(Logger *);
//    /** \brief initializes the process
//     * takes input from input_buffer until input_buffer->is_eof()==true; after everithing's processes sets output_buffer->set_end_of_input()
//     *
//     */
    Grammar_from_tree* parse(const std::vector<std::pair<int, std::string>> & input);

};

#endif // GRAMMAR_FROM_TREE_RULE_PARSER
