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
    Logger * logger; /**< for communication with the user */
    Grammar* grammar;/**< grammar according to which the parse tree is created */
    bool is_ok; /**< whether the parser is able to work */
public:
    /** \brief constructor
     *
     * \param Grammar pointer to the grammar that will be used to parse
     * \param Logger for communication with the user
     *
     */

    Parser(Grammar*, Logger*);

    virtual Parser * clone()=0;

    /** \brief interface for parsing
     *
     * \param input pair of line_id and pointer to tagged `Word` to be tagged
     * \return pair of line_id and pointer to the result of parsing. in case of critical failure it is a nullptr
     *
     */

    virtual std::vector<std::pair<int, Parse_tree*>> parse(std::pair<int, Word*> input)=0;

    /** \brief checks whether a critical error occurred
     *
     * \return true when parser is able to work, false otherwise
     *
     */

    virtual bool is_everything_ok()=0;
};

/** \brief parses according to Cocke-Younger-Kasami algorithm
 * assumes the grammar is in Chomsky's normal form;
 * (all rules are binary -- changing nonterminals into terminals is done at the level of tagger)
 * in other cases the program will fail
 */

class CYK_parser: public Parser
{
    std::unordered_map< std::string, std::vector<std::string>> rule_map; /**< reverse mapping of rules of the grammar
    * the key is the body of the rule; symbols are separated by space */
public:

    /** \brief constructor
     *  initializes also the `rule_map`
     * \param Grammar pointer to the grammar that will be used to parse
     * \param Logger for communication with the user
     *
     */
    CYK_parser(Grammar*, Logger*);

    virtual Parser * clone();

    /** \brief interface for parsing
     *
     * \param input pair of line_id and pointer to tagged `Word` to be parsed
     * \return pair of line_id and pointer to the result of parsing. in case of critical failure it is a nullptr
     *
     */
    virtual std::vector<std::pair<int, Parse_tree*>> parse( std::pair<int, Word*> input);

    /** \brief checks whether a critical error occurred
     *
     * \return true when parser is able to work, false otherwise
     *
     */

    virtual bool is_everything_ok();

};


#endif // PARSER
