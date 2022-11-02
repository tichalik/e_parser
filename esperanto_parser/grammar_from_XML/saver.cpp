#include "grammar_from_XML/saver.h"

Grammar_saver::Grammar_saver()
{

}

bool Grammar_saver::write(const std::string & filepath,  Grammar_from_XML & grammar)
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
        for (Rule rule: grammar.get_rules())
        {
            file << "\n\t<rule>\n\t\t<r_head>\n\t\t\t<s> " << rule.left << " </s>\n\t\t</r_head>\n\t\t<r_body>\n";
            for (std::string str: rule.right)
                file << "\t\t\t<s> " << str << " </s>\n";
            file << "\t\t</r_body>\n\t</rule>\n";
        }
        file << "</rules>"<<std::endl;

        file.close();
        return true;
    }
    return false;
}
