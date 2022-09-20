#include "grammar_from_XML/loader.h"



Grammar_from_XML_loader::Grammar_from_XML_loader()
{

}

Grammar* Grammar_from_XML_loader::read(const std::string &path)
{
    Grammar_reader_from_XML gr;
    Grammar_from_XML* grammar = gr.read(path);

    Half_chomskyficator n;
    n.normalize(grammar);

//    grammar -> normalize();

    Grammar_saver s;
    s.write("output.txt", *grammar);

    return grammar;
}
