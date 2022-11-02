#ifndef GRAMMAR_FROM_TREE_RULE_TRANSFORMER
#define GRAMMAR_FROM_TREE_RULE_TRANSFORMER

#include "grammar.h"
#include "../logger.h"

/** \brief transforms the rules of a grammar anyhow
 *
 */

class Rule_transformer
{
protected:
    Logger * logger; /**< required for error detection  */
public:
    Rule_transformer(Logger *);

    /** \brief transforms the rules
     *
     * \param [in, out]
     * \return nullptr if critical error occurs, else the pointer to the same grammar which was provided as the argument
     *
     */

    virtual Grammar_from_tree* transform( Grammar_from_tree * &)=0;
};

/** \brief the terminals of the grammar are tagged, using `Part_of_speech_tagger`
 *
 */

class Terminal_tagger: public Rule_transformer, public Part_of_speech_tagger
{
public:
    Terminal_tagger(Logger *);

    /** \brief transforms the rules
     * tags the terminals in the same way input is tagged in the main parsing pipeline.
     * \param [in, out] pointer to grammar to modify, the same as is returned. In case of a critical failure the pointer is deleted.
     * \return nullptr if critical error occurs, else the pointer to the same grammar which was provided as the argument
     *
     */

    Grammar_from_tree* transform( Grammar_from_tree* &);
};

#endif // GRAMMAR_FROM_TREE_RULE_TRANSFORMER
