#ifndef GRAMMAR_FROM_TREE_RULE_PARSER
#define GRAMMAR_FROM_TREE_RULE_PARSER

#include <string>
#include <vector>
#include <stack>
#include <future>

#include "grammar.h"


/** \brief creates grammar from rules represented as input strings
 *
 */

class Rule_parser
{
//    Buffer<std::string> * input_buffer/**< source */;
//    Buffer<Grammar_from_tree> * output_buffer /**< destination; there will be only one grammar, so it functions as std::promise/future */;
public:
//    /** \brief constructor
//     * requires providing both buffers as without it cannot work
//     * \param input buffer
//     * \param output buffer
//     *
//     */
//    Rule_parser(Buffer<std::string> *, Buffer<Grammar_from_tree> *);
//    /** \brief initializes the process
//     * takes input from input_buffer until input_buffer->is_eof()==true; after everithing's processes sets output_buffer->set_end_of_input()
//     *
//     */
    Grammar_from_tree parse(const std::vector<std::string> & input);

};

#endif // GRAMMAR_FROM_TREE_RULE_PARSER
