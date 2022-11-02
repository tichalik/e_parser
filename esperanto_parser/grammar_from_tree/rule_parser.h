#ifndef GRAMMAR_FROM_TREE_RULE_PARSER
#define GRAMMAR_FROM_TREE_RULE_PARSER

#include <string>
#include <vector>
#include <stack>
#include <future>

#include "grammar.h"
#include "../logger.h"


/** \brief reads a grammar from trees provided in input strings
 *
 */

class Rule_parser
{
    Logger * logger; /**< required for error reporting */

    /** \brief increments the valency of nonterminal symbol at the top of the stack
     *
     * \param [in, out] the stack of parsed symbols
     *
     */

    void add_valency(std::list<std::pair<std::string, int>> & stack);
public:

    /** \brief constructor
     * logger required for error reporting
     *
     */

    Rule_parser(Logger *);

    /** \brief transforms input strings into a grammar
     * if error occurrs during parsing of a line, it is raised to the logger and the line does not contribute to the output grammar.
     * \param input pairs of line-line_id
     * \return grammar with terminals as seen from the input. The grammar has been `update()`'d but lacks the head.
     *
     */


    Grammar_from_tree* parse(const std::vector<std::pair<int, std::string>> & input);

};

#endif // GRAMMAR_FROM_TREE_RULE_PARSER
