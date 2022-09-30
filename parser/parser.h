#ifndef PARSER
#define PARSER

#include "grammar.h"
#include "word.h"
#include "parsing_node.h"
#include "parse_tree.h"
#include "logger.h"

#include <string>
#include <unordered_map>


/** \brief interface for creating a parse tree for given words from given grammar
 *
 */

class Parser
{
protected:
    Logger * logger;
    Grammar* grammar;/**< grammar accroding to which teh parse tree is created */
public:
    Parser(Grammar*, Logger*);
    virtual std::vector<std::pair<int, Parse_tree*>> parse(std::pair<int, Word*> input)=0;
};

/** \brief parses according to COcke-Younger-Kasami algorithm
 *
 * \param
 * \param
 * \return
 *
 */

class CYK_parser: public Parser
{
    std::unordered_map< std::string, std::vector<std::string>> rule_map;
public:
    CYK_parser(Grammar*, Logger*);
    virtual std::vector<std::pair<int, Parse_tree*>> parse( std::pair<int, Word*> input);

};


#endif // PARSER
