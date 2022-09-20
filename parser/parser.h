#ifndef PARSER
#define PARSER

#include "grammar.h"
#include "word.h"
#include "parsing_node.h"

#include <string>
#include <unordered_map>


/** \brief interface for creating a parse tree for given words from given grammar
 *
 */

class Parser
{
protected:
    Grammar* grammar;/**< grammar accroding to which teh parse tree is created */
//    Buffer<Word> * input_buffer; /**< source */
//    Buffer<Parsing_node> * output_buffer;/**< destination */
public:
    /** \brief constructor
     * requires providing both buffers and grammar as without it cannot work
     * \param grammar grammar
     *
     */
//    Parser(Grammar*, Buffer<Word> *, Buffer<Parsing_node>*);
    Parser(Grammar*);
    virtual Parsing_node parse( Word & input)=0;
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
    CYK_parser(Grammar*);
    virtual Parsing_node parse( Word & input);

};


#endif // PARSER
