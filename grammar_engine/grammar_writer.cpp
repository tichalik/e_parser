#include "grammar_writer.h"

Grammar_writer::Grammar_writer(Logger _logger): logger(_logger)
{

}

bool Grammar_writer::write(const std::string & filepath,  Grammar & grammar)
{
    std::ofstream file(filepath);
    if (file)
    {
        file << "<nonterminals>\n";
        for (std::string vn: grammar.get_nonterminals())
            file << "\t<s> " << vn << " </s>\n";
        file << "</nonterminals>\n\n<terminals>\n";
        for (std::string vt: grammar.get_terminals())
            file << "\t<s> " << vt << " </s>\n";
        file << "</terminals>\n\n<head> <s> " <<grammar.get_head() << " </s> </head>\n";
        file << "\n<rules>\n";
        for (std::pair<std::string, std::vector<std::string>> rule: grammar.get_rules() )
        {
            file << "\n\t<rule>\n\t\t<r_head>\n\t\t\t<s> " << rule.first << " </s>\n\t\t</r_head>\n\t\t<r_body>\n";
            for (std::string str: rule.second)
                file << "\t\t\t<s> " << str << " </s>\n";
            file << "\t\t</r_body>\n\t</rule>\n";
        }
        file << "</rules>"<<std::endl;

        file.close();
        return true;
    }
    return false;
}
