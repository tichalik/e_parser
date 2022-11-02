#ifndef GRAMMAR_FROM_XML_GRAMMAR
#define GRAMMAR_FROM_XML_GRAMMAR


#include "../grammar.h"

#include <unordered_map>
#include <unordered_set>

class Grammar_from_XML: public Grammar
 {
    std::unordered_set<std::string> nonterminals; /**< the order doesn't matter and set representation helps with checking whether nonterminals contain a symbol */
    std::unordered_set<std::string> terminals;/**< the order doesn't matter and set representation helps with checking whether nonterminals contain a symbol */
    std::string head; /**< the head */
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> rules; /**< map of rules: the key is the LHS, the value is a vector of all RHS (as vectors of symbols) with this LHS*/
 public:
     /** \brief constructor
      * the grammar is created at once, when the entire XML file is processed. In need of delayed provision of fields, just push empty object and then set them using setters
      *
      */

     Grammar_from_XML(const std::unordered_set<std::string> & _nonterminals,
            const std::unordered_set<std::string> & _terminals,
            const std::string & _head,
            const std::vector<Rule> & _rules);

    /** \brief get a formatted string description
     *
     */

    std::string get_string_description();

    /** \brief returns nonterminals in the format defined by `Grammar`
     *
     */

    virtual std::vector<std::string> get_nonterminals();

    /** \brief returns terminals in the format defined by `Grammar`
     *
     */
    virtual std::vector<std::string> get_terminals();

    /** \brief returns head in the format defined by `Grammar`
     *
     */
    virtual std::string get_head();

    /** \brief returns rules in the format defined by `Grammar`
     *
     */
    virtual std::vector<Rule> get_rules();

    /** \brief clears the current nonterminals and sets the new
     *
     */

    virtual void set_nonterminals(const std::vector<std::string> & _nonterminals);

    /** \brief clears the current terminals and sets the new
     *
     */
    virtual void set_terminals(const std::vector<std::string> & _terminals);

    /** \brief clears the current head and sets the new
     *
     */
    virtual void set_head(const std::string & _head);

    /** \brief clears the current rules and sets the new
     *
     */
    virtual void set_rules(const std::vector<Rule> & _rules);

 };

 #endif // GRAMMAR_FROM_XML_GRAMMAR
