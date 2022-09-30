#ifndef TAGGER
#define TAGGER
//THERE MIGHT BE A PROBLEM!!
#include <string>
#include <regex>
#include <ranges>

#include "word.h"
#include "logger.h"

/** \brief interface for concurrent tagging of words
 *
 * \param
 * \param
 * \return
 *
 */

class Tagger
{
protected:
    Logger * logger;
public:
    Tagger(Logger * _logger);

    /** \brief initializes the tagging process
     * takes input from input_buffer until input_buffer->is_eof()==true; after everithing's processes sets output_buffer->set_end_of_input()
     *
     */

    virtual std::pair<int, Word*> tag(std::pair<int, Word*> input)=0;

//    virtual void tag_one( Word&)=0;
};

/** \brief implementation of interface; tags according to regex matches
 *
 * \param
 * \param
 * \return
 *
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
    };/**< collection of regex expression and tag to give in case of match. Matching with any causes to terminate the iteration, so expressions closer to 0 have higher priority  */
public:
    Part_of_speech_tagger(Logger * _logger);
    virtual std::pair<int, Word*> tag(std::pair<int, Word*> input);
//    virtual void tag_one( Word&);
};

#endif // TAGGER
