#include "word.h"


int Word::get_size() const
{
    return symbols.size();
}

std::string  Word::to_string() const
{
    std::string s;
    for(Symbol tmp: symbols)
        s += "<" + tmp.symbol + ">[" + tmp.tag + "]";
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

std::string Word::get_symbol_at(const int i ) const
{
    return this->symbols[i].symbol;
}
std::string Word::get_tag_at(int i) const
{
    return this->symbols[i].tag;
}
