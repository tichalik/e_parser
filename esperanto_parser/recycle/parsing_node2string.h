#ifndef PARSING_NODE2STRING
#define PARSING_NODE2STRING

#include "buffers.h"
#include "parsing_node.h"

/** \brief interface to concurrently convert parsing nodes to strings
 *
 */

class Parsing_node2string
{
protected:
    Buffer<Parsing_node> * input_buffer;
    Buffer<std::string> * output_buffer;
public:
    /** \brief constructor
     * requires providing both buffers and grammar as without it cannot work
     * \param grammar grammar
     * \param input buffer
     * \param output buffer
     *
     */
    Parsing_node2string(Buffer<Parsing_node> *, Buffer<std::string>*);
    /** \brief initializes the tagging process
     * takes input from input_buffer until input_buffer->is_eof()==true; after everithing's processes sets output_buffer->set_end_of_input()
     *
     */
    virtual void convert()=0;
};

class Simple_Parsing_node2string: public Parsing_node2string
{
public:
    Simple_Parsing_node2string(Buffer<Parsing_node> *, Buffer<std::string>*);
    virtual void convert();
};

#endif // PARSING_NODE2STRING
