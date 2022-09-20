#include "grammar_from_XML/reader.h"


Grammar_reader_from_XML::Grammar_reader_from_XML()
{

}



Grammar_from_XML * Grammar_reader_from_XML::read(const std::string & path)
{
    std::ifstream file(path);

    if (file)
    {
//
        std::cout << ("file "+ path + " opened.\n");
        std::string line;
        std::string file_contents;

        while (std::getline(file, line))
        {
//            std::cout << line << "\n";
            file_contents += line + "\n";
        }

        file.close();


        preprocessed_input = normalize(file_contents);

        std::vector<std::pair<int, std::vector<std::string>>>  tokenized = tokenize(preprocessed_input, "<\\/?\\w+>|\\w+");
//    for (int i=0; i<tokenized.size(); i++) //for inconceivable reasons the ranged for does not work and spits gibberish for the int :v
//    {
//        std::cout << tokenized[i].first << "\t";
//        for (int j=0; j<tokenized[i].second.size(); j++)
//            std::cout << tokenized[i].second[j] << "-";
//        std::cout << "\n";
//    }




        std::unordered_set<std::string> nonterminals;
        std::unordered_set<std::string> terminals;
        std::string head;
        std::vector<Rule> rules;
        std::string r_head;
        std::vector<std::string> r_body;

        all_ok = true;

        std::stack<std::string> stack;
        for (int i=0; i<tokenized.size() && all_ok; i++)
        {
            std::string prev_token;
            for (int j=0; j<tokenized[i].second.size() && all_ok;j++)
            {
                std::string token = tokenized[i].second[j];
                int current_line = tokenized[i].first;
                if (token[0]=='<') //tag
                {
    //                std::cout << token <<std::endl;
                    std::string tag = (token[1]=='/'?(token.substr(2,token.size()-3)):(token.substr(1,token.size()-2)));
    //                std::cout << "it is a tag!" << tag <<std::endl;

                    if (tag != "terminals" && tag != "nonterminals" && tag != "s" && tag != "head" && tag != "rules" && tag != "rule" && tag != "r_head" && tag != "r_body" )
                    {
                        all_ok = false;
                        std::cout << "Error! at line" << current_line << ": invalid tag "+ tag;
                    }
                    else if (token[1]=='/') //closing tag
                    {
    //                    std::cout << "it is a closing tag" <<std::endl;
                        if (stack.empty())
                        {
                            all_ok = false;
                            std::cout << "Error! at line" << current_line << ": closing tag "  << tag << ", but no tag has been opened\n";
                        }
                        else if (stack.top()!=tag)
                        {
                            all_ok = false;
                            std::cout << "Error! at line" << current_line << ": incompatible closing tag, last opened was " << stack.top() << ", now closing with "  << tag << "\n";
                        }
                        else
                        {
                            stack.pop();
        //                    std::cout << stack.empty() <<std::endl;
                            if(tag=="s")
                            {
                                if (stack.top()=="terminals")
                                {
                                    if (nonterminals.contains(prev_token))
                                    {
                                        all_ok = false;
                                        std::cout << "Error! at line" << current_line << ": " << prev_token <<  " cannot be both in terminals and nonterminals\n";
                                    }
                                    else
                                        terminals.insert(prev_token);
                                }
                                else if (stack.top()=="nonterminals")
                                {
                                    if (terminals.contains(prev_token))
                                    {
                                        all_ok = false;
                                        std::cout << "Error! at line" << current_line << ": " << prev_token << " cannot be both in terminals and nonterminals\n";
                                    }
                                    else
                                        nonterminals.insert(prev_token);
                                }
                                else if (stack.top()=="head")
                                {
                                        head = prev_token;
                                }
                                else if (stack.top()=="r_head")
                                {
                                    if (!nonterminals.contains(prev_token))
                                    {
                                        all_ok = false;
                                        std::cout << "Error! at line" << current_line << ": " << prev_token  <<" not in nonterminals\n";
                                    }
                                    else
                                        r_head = prev_token;
                                }
                                else if (stack.top()=="r_body")
                                {
                                    if (!nonterminals.contains(prev_token) && !terminals.contains(prev_token))
                                    {
                                        all_ok = false;
                                        std::cout << "Error! at line" << current_line << ": " << prev_token  <<" neither in nonterminals nor in terminals\n";
                                    }
                                    else
                                        r_body.push_back(prev_token);
                                }
                            }
                            else if (tag == "rule")
                            {
                                if (r_head =="")
                                {
                                    all_ok = false;
                                    std::cout << "Error! at line" << current_line << ": no rule head\n";
                                }
                                else if (r_body.size()==0)
                                {
                                    all_ok = false;
                                    std::cout << "Error! at line" << current_line << ": no rule body\n";
                                }
                                else
                                {
                                    rules.push_back({r_head, r_body});
                                    r_head = "";
                                    r_body.clear();
                                }

                            }
                            prev_token = "";
                        }

                    }
                    else //opening tag
                    {
    //                    std::cout << "it is an opening tag" <<std::endl;
                        prev_token = "";
                        if (!stack.empty())
                        {
                            if ((stack.top()=="nonterminals" || stack.top()=="terminals" || stack.top()=="head" || stack.top()=="r_head" || stack.top()=="r_body") && tag!="s")
                            {
                                all_ok=false;
                                std::cout << "Error! at line" << current_line << ": expected s tag, got " + tag+"\n";
                            }
                            else if ((stack.top()=="rules") && tag!="rule")
                            {
                                all_ok=false;
                                std::cout << "Error! at line" << current_line << ": expected rule tag, got " + tag+"\n";
                            }
                            else if ((stack.top()=="rule") && tag!="r_body" && tag!="r_head")
                            {
                                all_ok=false;
                                std::cout << "Error! at line" << current_line << ": expected r_body/r_head tag, got " + tag+"\n";
                            }
                        }
                        else if (tag!="nonterminals" && tag!="terminals" && tag!="head" && tag!="rules" )
                        {
                            all_ok = false;
                            std::cout << "Error! at line" << current_line << ": on the highest level expected tag nonterminals/terminals/head/rules, got " + tag +"\n";                        }

                        if (all_ok)
                        {
                            if (tag == "head" && head!="")
                            {
                                all_ok = false;
                                std::cout << "Error! at line" << current_line << ": redefinition of head\n";
                            }
                            else if (tag == "r_head" && r_head!="")
                            {
                                all_ok = false;
                                std::cout << "Error! at line" << current_line << ": redefinition of r_head\n";
                            }
                            else if (tag == "terminals" && !terminals.empty())
                            {
                                all_ok = false;
                                std::cout << "Error! at line" << current_line << ": redefinition of terminals\n";
                            }
                            else if (tag == "nonterminals" && !nonterminals.empty())
                            {
                                all_ok = false;
                                std::cout << "Error! at line" << current_line << ": redefinition of nonterminals\n";
                            }
                            else if (tag == "r_body" && !r_body.empty())
                            {
                                all_ok = false;
                                std::cout << "Error! at line" << current_line << ": redefinition of r_body\n";
                            }
                            else
                            {
    //                             std::cout << "pushing tag "<< tag <<"\n";
                                stack.push(tag);
                            }
                        }
                    }
                }
                else
                {
                    prev_token = token;
                }
            }


        }

        if (!stack.empty())
        {
            all_ok = false;
            std::cout << "Error! at line " << tokenized.size()<< ": no closing tag for " + stack.top()<<"\n";
        }

        Grammar_from_XML* result;
        result = new Grammar_from_XML(nonterminals, terminals, head, rules);


        return result;

    }
    else
    {
        std::cout << "Error! cannot open "+ path + " file.\n";
        return nullptr;
    }
}


std::vector<std::pair<int, std::string>> Grammar_reader_from_XML::normalize(const std::string & input)
{
    std::vector<std::pair<int, std::string>> output;

    std::stringstream s;
    s << input;
    std::string line;
    int linecount = 1;
    while (std::getline(s, line))
    {
        if (line!="")
        {
            if (line.at(0) == '\t')
            {
                line[0]= ' ';
            }
            if (line.at(0) == '#')
            {
                continue;
            }

            for (int i=1; i<line.size(); i++)
            {
                if (line.at(i) == '\t')
                {
                    line[i]= ' ';
                }

                if (line[i]==' ' && (line[i-1]==' ' || line[i-1]=='<' ||line[i-1]=='/'))
                {
                    line.erase(i,1);
                    i--;
                }
                if (line[i]=='>'&& line[i-1]==' ')
                {
                    line.erase(i-1,1);
                    i--;
                }
                if (line[i]=='#')//comments
                {
                    line = line.substr(0,i);
                    break;
                }
            }

            if (line!=""&&line[0]==' ')
                line.erase(0,1);
            if (line!=""&&line[line.size()-1]==' ')
                line.erase(line.size()-1, 1);
            if (line!="")
                output.push_back({linecount, line});



        }
//        std::cout << linecount << " " << line << "\n";



        linecount++;
    }

    return output;
}

std::vector<std::pair<int,std::vector<std::string>>> Grammar_reader_from_XML::tokenize(std::vector<std::pair<int, std::string>> & input, const std::string & _tokens)
{
    //distinguished tokens:"::=" and string of chars
    std::vector<std::pair<int,std::vector<std::string>>> output;
    std::regex tokens(_tokens) ;

    for (std::pair<int, std::string> line: input)
    {
        std::pair<int, std::vector<std::string>>tokenized;
        bool ok = true;
        tokenized.first = line.first;
        for (std::sregex_iterator i(line.second.begin(), line.second.end(), tokens); i!=std::sregex_iterator(); i++)
        {
            std::smatch m = *i;

             if (m.prefix()!=' '&&m.prefix()!="") //we don't mind spaces
            {
                std::string tmp = m.prefix(); //cant glue together char[] and strings in the next line
                std::cout << "Error! at line " << tokenized.first << ": symbol " << tmp  << " cant be tokenized\n";
                ok = false;
                break;
            }
            tokenized.second.push_back(m.str());
        }

//        std::cout << tokenized.first << "\t";
//        for (std::string s: tokenized.second)
//            std::cout << s << "-";
//        std::cout << "\n";

        if (ok)
            output.push_back(tokenized);
    }




    return output;
}
