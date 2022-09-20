#ifndef INTERFACE
#define INTERFACE

#include <string>
#include <iostream>
#include <vector>

class Interface
{
    std::ostream* output_stream;
    std::istream* input_stream;
public:
    Interface(std::ostream* _output_stream, std::istream * _input_stream);
    int choose_candidate(const std::string & context, const std::string &head, const std::vector<std::vector<std::string>> & candidates);
};

#endif // INTERFACE
