#ifndef LOJBAN_TAGGER
#define LOJBAN_TAGGER

#include "../tagger.h"

class Lojban_tagger: public Tagger
{
public:
    Word tag(const Word & input);
};

#endif // LOJBAN_TAGGER
