#include "writer.h"

Writer::Writer(std::string p): path(std::filesystem::path(p))
{

}

Simple_writer::Simple_writer(std::string p): Writer(p)
{

}

void Simple_writer::write(const std::vector<std::string> & input)
{
    std::ofstream output(path);
    if (output)
    {
        for (std::string s : input)
            output << s;
        output.close();
    }
}
