#include "grammar_from_XML/reader.h"


Grammar_reader_from_XML::Grammar_reader_from_XML(Logger * l): logger(l)
{

}



Grammar_from_XML * Grammar_reader_from_XML::read(const std::vector<std::pair<int, std::string>> & input)
{

    /// normalizing the input
    std::vector<std::pair<int, std::string>>  preprocessed_input = normalize(input);
    ///tokenizing the input
    std::vector<std::pair<int, std::vector<std::string>>>  tokenized = tokenize(preprocessed_input, "<\\/?\\w+>|\\w+'?");

    ///reading the grammar from the input
    std::unordered_set<std::string> nonterminals;
    std::unordered_set<std::string> terminals;
    std::string head;
    std::vector<Rule> rules;
    std::string r_head; ///rule head (LHS)
    std::vector<std::string> r_body; ///rule body (RHS)

    bool all_ok = true; ///whether critical error occurred

    std::stack<std::string> stack; ///XML tags are put here
    for (int i=0; i<tokenized.size() && all_ok; i++) ///for each line of the input while no critical error occurs
    {
        std::string prev_token; ///we need to look one token back
        for (int j=0; j<tokenized[i].second.size() && all_ok;j++) ///for each token in the line
        {
            std::string token = tokenized[i].second[j];

            if (token[0]=='<') /// it is a tag
            {
                std::string tag = (token[1]=='/'?(token.substr(2,token.size()-3)):(token.substr(1,token.size()-2))); ///removing the braces

                ///checking whether the tag is valid
                if (tag != "terminals" && tag != "nonterminals" && tag != "s" && tag != "head" && tag != "rules" && tag != "rule" && tag != "r_head" && tag != "r_body" )
                {
                    all_ok = false;
                    logger->log_error(tokenized[i].first, "Grammar parsing error: invalid tag "+ tag);
                }
                else if (token[1]=='/') /// it is a closing tag
                {
                    if (stack.empty()) ///rogue opening tag
                    {
                        all_ok = false;
                        logger->log_error(tokenized[i].first,"Grammar parsing error: closing tag "  + tag +", but no tag has been opened\n");
                    }
                    else if (stack.top()!=tag) ///mismatch in tags
                    {
                        all_ok = false;
                        logger->log_error(tokenized[i].first,"Grammar parsing error: incompatible closing tag, last opened was " + stack.top() + ", now closing with "  +tag +"\n");
                    }
                    else
                    {
                        stack.pop(); ///the tag on top is unnecessary -- it is identical with `tag`
                        if(tag=="s") ///marking a symbol
                        {
                            if (stack.top()=="terminals") ///the symbol should be added to terminals
                            {
                                if (nonterminals.contains(prev_token))
                                {
                                    all_ok = false;
                                    logger->log_error(tokenized[i].first,"Grammar parsing error: " + prev_token +  " cannot be both in terminals and nonterminals\n");
                                }
                                else
                                    terminals.insert(prev_token);
                            }
                            else if (stack.top()=="nonterminals") ///the symbol should be added to nonterminals
                            {
                                if (terminals.contains(prev_token))
                                {
                                    all_ok = false;
                                    logger->log_error(tokenized[i].first,"Grammar parsing error: " + prev_token + " cannot be both in terminals and nonterminals\n");
                                }
                                else
                                    nonterminals.insert(prev_token);
                            }
                            else if (stack.top()=="head") ///it is a head
                            {
                                    head = prev_token;
                            }
                            else if (stack.top()=="r_head") ///it is the head of a rule (LHS)
                            {
                                if (!nonterminals.contains(prev_token)) ///this symbol was not declared as nonterminal
                                {
                                    all_ok = false;
                                    logger->log_error(tokenized[i].first,"Grammar parsing error: " + prev_token  +" not in nonterminals\n");
                                }
                                else
                                    r_head = prev_token;
                            }
                            else if (stack.top()=="r_body") ///it is a part of the body of a rule
                            {
                                if (!nonterminals.contains(prev_token) && !terminals.contains(prev_token)) ///this symbol was not declared
                                {
                                    all_ok = false;
                                    logger->log_error(tokenized[i].first,"Grammar parsing error: " + prev_token  + " neither in nonterminals nor in terminals\n");
                                }
                                else
                                    r_body.push_back(prev_token); ///adding it to the rest of the body
                            }
                        }
                        else if (tag == "rule") ///definition of a rule has been finished...
                        {
                            if (r_head =="") ///...but no LHS was declared
                            {
                                all_ok = false;
                                logger->log_error(tokenized[i].first,"Grammar parsing error: no rule head\n");
                            }
                            else if (r_body.size()==0) ///...but no RHS was declared
                            {
                                all_ok = false;
                                logger->log_error(tokenized[i].first,"Grammar parsing error: no rule body\n");
                            }
                            else /// ...and it has both head and body
                            {
                                rules.push_back({r_head, r_body}); ///adding to rules
                                ///resetting the holders
                                r_head = "";
                                r_body.clear();
                            }

                        }
                        prev_token = ""; ///what was declared inside a rule won't be useful outside
                    }

                }
                else /// it is an opening tag
                {
                    prev_token = ""; ///what happened before an opening tag has been saved to the holder variables
                    ///checking whether tag hierarchy is followed
                    if (!stack.empty()) ///checking for tags other than the highest-order
                    {
                        ///the symbol tag can only be after these
                        if ((stack.top()=="nonterminals" || stack.top()=="terminals" || stack.top()=="head" || stack.top()=="r_head" || stack.top()=="r_body") && tag!="s")
                        {
                            all_ok=false;
                            logger->log_error(tokenized[i].first,"Grammar parsing error: expected s tag, got " + tag+"\n");
                        }
                        else if ((stack.top()=="rules") && tag!="rule") ///rule can only be defined in the rule section
                        {
                            all_ok=false;
                            logger->log_error(tokenized[i].first,"Grammar parsing error: expected rule tag, got " + tag+"\n");
                        }
                        else if ((stack.top()=="rule") && tag!="r_body" && tag!="r_head") ///LHS and RHS can only be in a rule
                        {
                            all_ok=false;
                            logger->log_error(tokenized[i].first,"Grammar parsing error: expected r_body/r_head tag, got " + tag+"\n");
                        }
                    }
                    else if (tag!="nonterminals" && tag!="terminals" && tag!="head" && tag!="rules" ) ///if it's not one of the highest-order tags
                    {
                        all_ok = false;
                        logger->log_error(tokenized[i].first,"Grammar parsing error: on the highest level expected tag nonterminals/terminals/head/rules, got " + tag +"\n");
                    }
                    if (all_ok) ///if no critical errors occurred
                    {
                        if (tag == "head" && head!="") ///redefinition of head
                        {
                            all_ok = false;
                            logger->log_error(tokenized[i].first,"Grammar parsing error: redefinition of head\n");
                        }
                        else if (tag == "r_head" && r_head!="") ///redefinition of rule head (LHS)
                        {
                            all_ok = false;
                            logger->log_error(tokenized[i].first,"Grammar parsing error: redefinition of r_head\n");
                        }
                        else if (tag == "terminals" && !terminals.empty()) ///redefinition of terminals
                        {
                            all_ok = false;
                           logger->log_error(tokenized[i].first,"Grammar parsing error: redefinition of terminals\n");
                        }
                        else if (tag == "nonterminals" && !nonterminals.empty()) ///redefinition of nonterminals
                        {
                            all_ok = false;
                            logger->log_error(tokenized[i].first,"Grammar parsing error: redefinition of nonterminals\n");
                        }
                        else if (tag == "r_body" && !r_body.empty()) ///redefinition of rule body (RHS)
                        {
                            all_ok = false;
                            logger->log_error(tokenized[i].first,"Grammar parsing error: redefinition of r_body\n");
                        }
                        else ///everything is ok and we can open the XML tag
                        {
                            stack.push(tag);
                        }
                    }
                }
            }
            else /// it is a normal string
            {
                prev_token = token;
            }
        }


    }

    if (!stack.empty()) ///something was left on the stack; proper XML file should leave it empty
    {
        all_ok = false;
        logger->log_error("Grammar parsing error: no closing tag for " + stack.top() + "\n");
    }

    Grammar_from_XML* result = nullptr;
    if (all_ok) ///no critical error occurred
        result = new Grammar_from_XML(nonterminals, terminals, head, rules);


    return result;

}


std::vector<std::pair<int, std::string>> Grammar_reader_from_XML::normalize(const std::vector<std::pair<int, std::string>> & input)
{
    std::vector<std::pair<int, std::string>>  output;
    for (const std::pair<int, std::string>& _line: input)
    {
        std::string line = _line.second;
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
                output.push_back({_line.first, line});
        }
    }

    return output;
}

std::vector<std::pair<int,std::vector<std::string>>> Grammar_reader_from_XML::tokenize(std::vector<std::pair<int, std::string>> & input, const std::string & _tokens)
{
    std::vector<std::pair<int,std::vector<std::string>>> output;
    std::regex tokens(_tokens); ///regex according to which tokenization will occur

    for (std::pair<int, std::string> line: input)
    {
        std::pair<int, std::vector<std::string>>tokenized; ///temporary result
        bool ok = true; ///whether an error occurred
        tokenized.first = line.first; ///the line_id stays the same

        std::smatch m;

        for (std::sregex_iterator i(line.second.begin(), line.second.end(), tokens); i!=std::sregex_iterator(); i++) ///cutting the line using a regex
        {
             m = *i;

             if (m.prefix()!="" && m.prefix()!=' ') /// there's a leftover text before the match (spaces can be ignored)
            {
                std::string tmp = m.prefix(); //cant glue together char[] and strings in the next line
               logger->log_error(tokenized.first, "Grammar parsing error: symbol " + tmp  + " cant be tokenized\n");
                ok = false;
                break;
            }
            tokenized.second.push_back(m.str()); ///the tokenized bit is put back
        }
        if (m.suffix()!=""&&m.suffix()!=' ') /// there's a leftover text before the match (spaces can be ignored)
        {
            std::string tmp = m.suffix(); //cant glue together char[] and strings in the next line
            logger->log_error(tokenized.first, "Grammar parsing error: symbol " + tmp  + " cant be tokenized\n");
            ok = false;
            break;
        }
        if (ok) ///if no error occurred
            output.push_back(tokenized); ///add into the result
    }




    return output;
}
