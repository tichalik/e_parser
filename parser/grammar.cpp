#include "grammar.h"


bool Rule::operator==(const Rule r)
{
    return left == r.left && right == r.right;
}

Grammar::Grammar()
{

}



