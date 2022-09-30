#include "grammar_from_XML/loader.h"



Grammar_from_XML_loader::Grammar_from_XML_loader(Logger * l): Grammar_loader(l)
{

}

Grammar* Grammar_from_XML_loader::load(const std::string &path)
{
    Grammar_reader_from_XML gr(logger);
    Grammar_from_XML* grammar = gr.read(path);

    Half_chomskyficator n(logger);
    n.normalize(grammar);

//    grammar -> normalize();

    Grammar_saver s;
    s.write("output.txt", *grammar);

    return grammar;
}
