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

    bool operator ==(const Rule); /**< required for avoiding doubles */

};


/** \brief formal grammar representation
 *
 */

 class Grammar
 {
 public:
//    friend std::ostream& operator << (std::ostream& s, const Grammar &g);

    Grammar();

    virtual std::vector<std::string> get_nonterminals()=0;
    virtual std::vector<std::string> get_terminals()=0;
    virtual std::string get_head()=0;
    virtual std::vector<Rule> get_rules()=0;


    virtual void set_nonterminals(const std::vector<std::string> & _nonterminals) = 0;
    virtual void set_terminals(const std::vector<std::string> & _terminals) = 0;
    virtual void set_head(const std::string & _head) = 0;
    virtual void set_rules(const std::vector<Rule> & _rules) =0;

 };




#endif // GRAMMAR
