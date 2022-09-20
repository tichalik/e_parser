#include "interface.h"

Interface::Interface(std::ostream* _output_stream, std::istream* _input_stream): output_stream(_output_stream), input_stream(_input_stream)
{

}

int Interface::choose_candidate(const std::string & context, const std::string &head, const std::vector<std::vector<std::string>> & candidates)
{
    (*output_stream) << "\t"<<context << "\n";
    (*output_stream) << "choose rule to apply:\n";
    for (int i=0; i<candidates.size(); i++)
    {
        (*output_stream) << "\t[" << i+1 << "] " << head << " ::= ";
        for (std::string s: candidates[i])
            (*output_stream) << s <<" ";
        (*output_stream) << "\n";
    }

    int result = -1;
    while (result <= 0 || result > candidates.size())
    {
        (*output_stream) << ">";
        (*input_stream) >> result;
//        std::cout << input_stream->good() << "\n" << input_stream->bad() << "\n" << input_stream->fail() << "\n" << input_stream->eof() <<"\n";
        if (!*input_stream)
        {
            result = -1;
            input_stream->clear();
            input_stream->ignore();
//            input_stream->clear();
        }
    }
    return result-1;
}
