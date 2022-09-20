#include "reader.h"

#include <iostream>

//Reader::Reader(Buffer<std::string>* _output): output(_output)
//{
//
//}

std::vector<std::string> Reader::read(const std::string &directory)
{

    std::vector<std::string> output;
    for (std::filesystem::directory_entry entry: std::filesystem::directory_iterator(std::filesystem::path(directory)))
    {

        if (entry.path().extension()==".txt")
        {
            std::ifstream file(entry.path());
            if (file)
            {
                std::string line;
                while (std::getline(file, line))
                {
                    //removing comments starting with #
                    std::regex r("#"); //NIE MA ODWOŁYWANIA KOMENTARZY!!
                    std::smatch match;
                    if (std::regex_search(line, match, r))
                    {
                        line = match.prefix();
                        if (match.length()!=1)
                            line +=match.str(0)[0];
                    }

                    //normalizing the line
                    std::stringstream s;
                    s << line;
                    std::string tmp;
                    s>>tmp;
                    line = tmp;
                    while(s>>tmp)
                        line +=" "+tmp;

                    if (line!="")
                    {
        //                std::cout << line <<std::endl; // TO POTEM ZNIKNIE, BĘDZIEMY WSADZAĆ DO BUFORA
                       output.push_back(line);
                    }

                }
                file.close();
 //               std::cout << "all read\n";
            }
        }
    }
    return output;
}
