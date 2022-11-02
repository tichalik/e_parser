#ifndef GRAMMAR_FROM_TREE_GRAMMAR
#define GRAMMAR_FROM_TREE_GRAMMAR

#include <unordered_map>
#include <unordered_set>


#include "../grammar.h"
#include "../tagger.h"
#include "../word.h"


/** \brief Grammar implementation used in tree processing
 *
 * Generating a grammar from a treebank requires few specific steps. Making a child implementation of grammar allows to simplify the code's structure
 */

class Grammar_from_tree: public Grammar
{
    std::unordered_map<std::string, std::unordered_set<int>> nonterminals; /**< symbol and the indexes of rules in which it appears */
    std::unordered_map<std::string, std::unordered_set<int>> terminals; /**< symbol and the indexes of rules in which it appears */
    std::string head; /**< the head belonging to nonterminals */
    std::vector<std::pair<int, Rule>> rules; /**< line_id of the source line and the rule itself  */
    //line id of of from where the rule originated and the rule itself

//    Tagger * transforming_tagger; /**< used in transformation of terminals */
public:

    /** \brief redundant!
     * in Grammar_from_tree nonterminals are inferred from the rules in `update()` method
     *
     */
    virtual void set_nonterminals(const std::vector<std::string> & _nonterminals); /**< redundant! */

    /** \brief redundant!
     * in Grammar_from_tree terminals are inferred from the rules in `update()` method
     *
     */

    virtual void set_terminals(const std::vector<std::string> & _terminals);

    /** \brief sets the head
     * grammar cannot detect whihc nonterminals is the head by itself in the `update()` method, it needs to be done manually
     *
     */

    virtual void set_head(const std::string & _head);

    /** \brief redundant!
     * in Grammar_from_tree rules are stored as pairs of the rule itself and the line_id it comes from, so leaving out the latter is impossible!
     *
     */

    virtual void set_rules(const std::vector<Rule> & _rules);

    virtual std::vector<std::string> get_nonterminals();
    virtual std::vector<std::string> get_terminals();


    /** \brief returns rules in the format defined by `Grammar`
     *
     */

    virtual std::vector<Rule> get_rules();

    /** \brief turns out the head is usefull
      *
      */

    virtual std::string get_head();


    /** \brief  adds rules and their source line_id
     * the grammar afterwards may have duplicate rules and miss non/terminals. calling `update()` is necessary to fix this. `update()` takes some time so it has to be called manually.
     * the rules already present in the grammar are not modified by any means.
     * \param the rules to add
     *
     */
    void add_rules_with_id(const std::vector<std::pair<int, Rule>>& new_rules );

    /** \brief returns the Rule-line_id pair
     *
     */

    std::vector<std::pair<int, Rule>>  get_rules_with_id();

    /** \brief deletes all the rules
     *
     */

    void clear_rules();


    /** \brief cleans up the grammar
     * -> removes duplicate rules
     * -> updates terminals and nonterminals
     * takes some time to compute and as so must be called manually, as the rules are often inserted one by one
     *
     */

    void update();



    /** \brief turns grammar into formated string
     *
     *
     */
    std::string get_string_description();
};

#endif // GRAMMAR_FROM_TREE

