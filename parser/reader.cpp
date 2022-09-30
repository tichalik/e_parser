#include "reader.h"

Reader::Reader(Logger * _logger): logger(_logger)
{

}

std::vector<std::pair<int, std::string>> Reader::read(const std::string &directory)
{

    std::vector<std::pair<int, std::string>> output;
    for (std::filesystem::directory_entry entry: std::filesystem::directory_iterator(std::filesystem::path(directory)))
    {
        if (entry.path().extension() == ".txt")
        {
            logger->add_file(entry.path());

            std::ifstream file(entry.path());
            if (file)
            {
                std::stringstream file_content;
                file_content << file.rdbuf();
                file.close();

                std::string line;
                int linecount = 1;
                while (std::getline(file_content, line))
                {
                    //removing comments starting with #
                    int pos = line.find("#");
                    if (pos!=std::string::npos)
                        line = line.substr(0, pos);

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
                        int line_id = logger->add_line(linecount);
//                        std::cout << line_id << ". " << line <<std::endl; // TO POTEM ZNIKNIE, BĘDZIEMY WSADZAĆ DO BUFORA
                       output.push_back({ line_id, line });
                    }
                    linecount++;

                }

                logger->log_message("finished reading " + entry.path().string() +"\n");
            }
        }
    }
    return output;
}
