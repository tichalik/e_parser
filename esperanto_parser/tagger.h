#ifndef TAGGER
#define TAGGER

#include <string>
#include <regex>

#include "word.h"
#include "logger.h"

/** \brief interface for tagging of 'Word` objects
 *
 */

class Tagger
{
protected:
    Logger * logger; /**< needed for user communication */
public:
    /** \brief constructor
     * logger serves as output stream
     *
     */

    Tagger(Logger * _logger);

    /** \brief tags a single `Word`
     * \param input pair of line_id and pointer to untagged 'Word' object
     * \return pair of line_id and pointer to tagged 'Word' object. in case of critical failure the pointer is set to nullptr
     */

    virtual std::pair<int, Word*> tag(std::pair<int, Word*> input)=0;

//    virtual void tag_one( Word&)=0;
};

/** \brief tags `Word`s according to Esperanto parts of speech
 * adds only a single tag
 */

class Part_of_speech_tagger: public Tagger
{
protected:
    std::vector<std::pair<std::regex, std::string>> classificators = { //includes priorities
        std::pair<std::regex, std::string>("la", "Det"),                  //determinant
        std::pair<std::regex, std::string>("(k|t||cx|nen)i(((u|o|a)j?n?)|e|am|en|al|el)", "Par"),                  //particle?
        std::pair<std::regex, std::string>("al|el|en|ek|tra|sur|sub|inter|post|antaux", "Prep"),               //prepositions
        std::pair<std::regex, std::string>("(m|v|sx|l|gx|n|on|il)i", "N"),       //pronouns treated like nouns
        std::pair<std::regex, std::string>("(m|v|sx|l|gx|n|on|il)in", "N-acc"),       //accusative pronouns treated like nouns
        std::pair<std::regex, std::string>("\\w*oj?", "N"),                     //non-accusative nouns
        std::pair<std::regex, std::string>("\\w*oj?n", "N-acc"),                //accusative nouns
        std::pair<std::regex, std::string>("\\w*aj?", "Adj"),                   //non-accusative adjectives
        std::pair<std::regex, std::string>("\\w*aj?n", "Adj-acc"),              //accusative adjectives
        std::pair<std::regex, std::string>("\\w*(is|as|os|us)", "V"),            //non-infinitive verbs
        std::pair<std::regex, std::string>("\\w*u", "V-irr"),                     //irrealis verbs
        std::pair<std::regex, std::string>("\\w*i", "V-inf"),                 //infinitive verbs
        std::pair<std::regex, std::string>("\\w*e", "Adv"),                   //adverb
        std::pair<std::regex, std::string>("\\w*en", "Adv-acc"),              //accusative adverb
        std::pair<std::regex, std::string>("\\w*", "unknown")                 //UNKNOWN SYMBOL
    }; /**< collection of regex expression and tag to give in case of match.
        * Expressions closer to 0 have higher priority  */
public:
    /** \brief constructor
     * logger serves as output stream
     *
     */
    Part_of_speech_tagger(Logger * _logger);

    /** \brief tags a single `Word`
     * the word going in and coming out is the same object, just with a new pointer
     * \param input pair of line_id and pointer to untagged 'Word' object. if there is already a tag in the Word, it is ignored.
     * \return pair of line_id and pointer to tagged 'Word' object. in case of critical failure the pointer is set to nullptr
     */
    virtual std::pair<int, Word*> tag(std::pair<int, Word*> input);
};

#endif // TAGGER
