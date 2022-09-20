#ifndef GRAMMAR_FROM_TREE_GRAMMAR
#define GRAMMAR_FROM_TREE_GRAMMAR

#include <unordered_map>
#include <unordered_set>


#include "../grammar.h"
#include "../tagger.h"
#include "../word.h"


class Grammar_from_tree: public Grammar
{
    std::unordered_map<std::string, std::unordered_set<int>> nonterminals; /**< symbol and the indexes of rules in which it appears */
    std::unordered_map<std::string, std::unordered_set<int>> terminals; /**< symbol and the indexes of rules in which it appears */
    std::string head; /**< it exists for the sake of formality, not used for now */
    std::vector<Rule> rules;

    Tagger * transforming_tagger;
public:

    virtual void set_nonterminals(const std::vector<std::string> & _nonterminals);
    virtual void set_terminals(const std::vector<std::string> & _terminals);
    virtual void set_head(const std::string & _head);
    virtual void set_rules(const std::vector<Rule> & _rules);

    virtual std::vector<std::string> get_nonterminals();
    virtual std::vector<std::string> get_terminals();



    /** \brief  adds rules to grammar. The grammar is derranged afterwards
     * "deranged" means:
     * -> may have duplicate rules
     * -> may miss terminals and nonterminals
     *
     * \param the rules to add
     *
     */

     /** \brief turns out the head is usefull
      *
      */

     virtual std::string get_head();


    /** \brief Orders the grammar
     * -> removes duplicate rules
     * -> updates terminals and nonterminals
     * takes some time to compute and as so must be called manually so, as often the rules are inserted one by one
     * \param
     * \return
     *
     */

    void update();
    /** \brief exports terminal symbols as a word
     * order does not matter, it's just a convenient format
     * \return the exported terminals
     *
     */

    Word terminals_to_word();
     /** \brief transforms terminals according to given function dictionary
      *
      * \param dictionary of the function
      *
      */

    void transform_terminals( std::unordered_map<std::string, std::string>);


    /** \brief used by parser
     *
     */

    virtual std::vector<Rule> get_rules();

//    /** \brief required for grammar to be stored in a buffer
//     */
//
//    bool operator==(Grammar_from_tree&);

    /** \brief shows all the info about grammar
     *
     *
     */
    friend std::ostream&  operator << (std::ostream& , const Grammar_from_tree &);
};

#endif // GRAMMAR_FROM_TREE

