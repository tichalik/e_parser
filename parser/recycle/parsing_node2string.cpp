#include "parsing_node2string.h"

Parsing_node2string::Parsing_node2string(Buffer<Parsing_node>* _input, Buffer<std::string>* _output): input_buffer(_input), output_buffer(_output)
{

}

Simple_Parsing_node2string::Simple_Parsing_node2string(Buffer<Parsing_node> *_input, Buffer<std::string>* _output): Parsing_node2string(_input, _output)
{

}

void Simple_Parsing_node2string::convert()
{
    Parsing_node input = input_buffer->pop();
    while (!input_buffer->is_eof())
    {
        std::string output = input.to_string();
        output_buffer->push(output);

        input = input_buffer->pop();
    }
    output_buffer->set_end_of_input();
}
