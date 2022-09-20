#ifndef GRAMMAR_FROM_TREE_RULE_TRANSFORMER
#define GRAMMAR_FROM_TREE_RULE_TRANSFORMER

#include "grammar.h"

/** \brief transforms the rules of a grammar anyhow
 *
 */

class Rule_transformer
{
public:
    Rule_transformer();
    virtual Grammar_from_tree transform( Grammar_from_tree&)=0;
};

/** \brief the terminals of the grammar are tagged, using the class tagger
 * pointer to specific tagger used is stored in provided grammar
 */

class Terminal_tagger: public Rule_transformer
{
public:
    Terminal_tagger();
    Grammar_from_tree transform( Grammar_from_tree&);
};

#endif // GRAMMAR_FROM_TREE_RULE_TRANSFORMER
