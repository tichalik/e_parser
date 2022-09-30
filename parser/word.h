#ifndef WORD
#define WORD

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

/** \brief in the formal grammar sense
 *
 */

struct Symbol
{
    std::string symbol;/**< for processing sentences this is an individual word */
    std::string tag; /**< the tag attached to the symbol; for now only 1 */
};

/** \brief Word, in the formal language sense
 * sequence of symbols from specific alphabet, in sentence parsing it represents the entire sentence
 * \param
 * \param
 * \return
 *
 */

class Word
{
    std::vector<Symbol> symbols; /**< sequence of symbols */
public:

    Word(); /**< default constructor required for storing in Buffer */
    Word(const Word &&);

    /** \brief creates a new symbol at the end of word and sets its symbol
     *
     * \param symbol const std::string the symbol component of new symbol
     *
     */

    void insert_symbol(const std::string&);

    /** \brief returns the symbol part of the symbol at given location
     *
     * \param i const int position
     * \return Symbol::symbol at i
     *
     */

    std::string get_symbol_at(const int);

    /** \brief Sets Symbol::tag of symbol at given location
     * requires that the tagged symbol exists
     * \param i const int position
     * \param  const std::string tag to insert
     *
     */

    void tag_at(const int , const std::string );


//    bool is_subsequence(const Word& b); // is a subsequence of b

/** \brief for comparing
 *
 * \return true if the given vector has the same symbols and tags at the respective position
 *
 */

    bool operator == ( const Word& b);
    /** \brief returns the size of the word
     *
     * \return number of symbols in the word
     *
     */

    int get_size();

    /** \brief gets tag at given position
     *  if there's no tag set, gives empty string
     * \param i int position
     * \return the tag
     *
     */

    std::string get_tag_at(int i);


    /** \brief for printing out the word
     * the representation of the word is in form
     * <symbol0>[tag0]<symbol1>[tag1].....
     *
     */
    friend std::ostream&  operator << (std::ostream& s, const Word &w);

};


#endif // WORD



