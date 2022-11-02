#ifndef GRAMMAR
#define GRAMMAR

#include <string>
#include <vector>


/** \brief representation of grammatical rule X -> Y0 Y1 Y2...
 */
struct Rule
{
    std::string left; /**< X */
    std::vector<std::string> right; /**< Y1 Y2 Y3 */

};


/** \brief interface for formal grammar representation
 * it does not define it's own fields, rather each individual representation does it in its own way.
 */

 class Grammar
 {
 public:

    /** \brief unified interface for getting nonterminals
     *
     */

    virtual std::vector<std::string> get_nonterminals()=0;

    /** \brief unified interface for getting terminals
     *
     */

    virtual std::vector<std::string> get_terminals()=0;

    /** \brief unified interface for getting head
     *
     */
    virtual std::string get_head()=0;

    /** \brief unified interface for getting rules
     *
     */
    virtual std::vector<Rule> get_rules()=0;

    /** \brief unified interface for setting nonterminals
     *
     */
    virtual void set_nonterminals(const std::vector<std::string> & _nonterminals) = 0;

    /** \brief unified interface for setting terminals
     *
     */
    virtual void set_terminals(const std::vector<std::string> & _terminals) = 0;

    /** \brief unified interface for setting head
     *
     */
    virtual void set_head(const std::string & _head) = 0;

    /** \brief unified interface for setting rules
     *
     */
    virtual void set_rules(const std::vector<Rule> & _rules) =0;

 };




#endif // GRAMMAR
