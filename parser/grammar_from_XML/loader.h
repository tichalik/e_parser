#ifndef GRAMMAR_FROM_XML_LOADER
#define GRAMMAR_FROM_XML_LOADER

#include "../grammar_loader.h"
#include "../normalizer.h"

#include "saver.h"
#include "reader.h"

class Grammar_from_XML_loader: public Grammar_loader
{
public:
    Grammar_from_XML_loader();
    virtual Grammar* read(const std::string &path);
};

#endif //GRAMMAR_FROM_XML_LOADER
