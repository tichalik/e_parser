
#include "word.h"
//bool Word::is_subsequence(const Word& b) // us a sybsequence of b
//{
//    std::string aS="|"; //separator sign, before must check whether it's not present in the input vectors!
//    for (int i=0; i<this->symbols.size(); i++)
//        aS += this->symbols[i]+"|";
//
//    std::string bS="|"; //separator sign, before must check whether it's not present in the input vectors!
//    for (int i=0; i<b.symbols.size(); i++)
//        bS += b.symbols[i]+"|";
//
//    if (bS.find(aS)!=std::string::npos)
//        return true;
//    else
//        return false;
//}

Word::Word()
{

}
bool Word::operator == ( const Word& b)
{
    if (this->symbols.size()==b.symbols.size())
    {
        for (int i=0; i<this->symbols.size(); i++)
            if (this->symbols[i].symbol!=b.symbols[i].symbol)
                return false;
        return true;
    }
    else
        return false;
}

int Word::get_size()
{
    return symbols.size();
}

std::ostream&  operator << (std::ostream& s, const Word &w)
{
//    if (w.symbols.size()==0)
//        s << "EMPTY!";
//    else
        for(Symbol tmp: w.symbols)
            s << "<"<<tmp.symbol <<">["<<tmp.tag<<"]";
    return s;
}
void Word::insert_symbol(const std::string&i)
{
    this->symbols.push_back({i,""});
}
void Word::tag_at(const int i, const std::string tag)
{
    symbols[i].tag = tag;
}

std::string Word::get_symbol_at(const int i )
{
    return this->symbols[i].symbol;
}
std::string Word::get_tag_at(int i)
{
    return this->symbols[i].tag;
}


Word::Word(const Word && w)
{
    for (Symbol s: w.symbols)
        symbols.push_back(s);
}
