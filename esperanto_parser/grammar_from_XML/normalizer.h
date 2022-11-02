#ifndef GRAMMAR_FROM_XML_NORMALIZER
#define GRAMMAR_FROM_XML_NORMALIZER

#include "grammar.h"
#include "../logger.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <stack>

/** \brief interface for classes changing form of a grammar to a given normal representation
 *
 */

class Normalizer
{
protected:
    Logger * logger;/**< in case of errors */

public:
    /** \brief constructor
     * Logger needed for communication with the user
     *
     */

    Normalizer(Logger*);

    /** \brief perform the modification
     * operates directly on the given grammar
     * \param [in,out] Grammar* grammar to be transformed, both as input and as output. If critical error occurs the grammar is deleted and the pointer set to nullptr
     * \return true if no critical error occurred, false otherwise.
     *
     */

    virtual bool normalize(Grammar_from_XML* & grammar)=0;
};

/** \brief replaces rules with RHS length >2 into equivalent set of rules with RSH lenght = 2
 * WARNING! RULES IN FORM symbol -> symbol (SINGLE SYMBOL RHS) ARE NOT MODIFIED!
 */

class Binarizer: public Normalizer
{
public:
    Binarizer(Logger*);
    /** \brief perform the modification
     * operates directly on the given grammar. for each rule in form X -> Y Z W creates new nonterminal X' and replaces the original rule with X -> Y X' and X' -> Z W
     * in  case that X' already belongs to the nonterminals, unpredicted behavior may occur.
     * \param [in,out] Grammar_from_XML* grammar to be transformed, both as input and as output. If critical error occurs the grammar is deleted and the pointer set to nullptr
     * \return true if no critical error occurred, false otherwise.
     *
     */
    virtual bool normalize(Grammar_from_XML* & grammar);
};



#endif // GRAMMAR_FROM_XML_NORMALIZER
