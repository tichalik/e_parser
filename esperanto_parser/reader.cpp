#include "reader.h"

Reader::Reader(Logger * _logger): logger(_logger)
{

}

std::vector<std::pair<int, std::string>> Reader::read(const std::string &directory)
{

    std::vector<std::pair<int, std::string>> output;
    ///for each file in the given directory
    for (std::filesystem::directory_entry entry: std::filesystem::directory_iterator(std::filesystem::path(directory)))
    {
        ///registering the file to the logger
        logger->add_file(entry.path());

        ///opening the file
        std::ifstream file(entry.path());
        if (file)
        {
            ///loading entire file into a streambuff to save on system callings
            std::stringstream file_content;
            file_content << file.rdbuf();
            ///the file is no longer needed
            file.close();

            ///going through each line
            std::string line;
            ///position of line in the file
            int linecount = 1;
            while (std::getline(file_content, line))
            {
                ///removing comments starting with #
                int pos = line.find("#");
                if (pos!=std::string::npos)
                    line = line.substr(0, pos);

                ///normalizing the line -- uniform white spaces
                std::stringstream s;
                s << line;
                std::string tmp;
                s>>tmp;
                line = tmp;
                while(s>>tmp)
                    line +=" "+tmp;

                ///a line could be white characters only, so after normalization it is an empty string
                if (line!="")
                {
                    ///registering the line in the logger
                    int line_id = logger->add_line(linecount);
                    ///adding to output
                    output.push_back({ line_id, line });
                }
                ///going to next line in the file
                linecount++;

            }

            logger->log_message("finished reading " + entry.path().string() +"\n");
        }
    }
    return output;
}
