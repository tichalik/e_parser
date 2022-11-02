#include "grammar_from_XML/loader.h"



Grammar_from_XML_loader::Grammar_from_XML_loader(Logger * l): Grammar_loader(l)
{

}

Grammar* Grammar_from_XML_loader::load(const std::string &path)
{
    Grammar_from_XML* grammar = nullptr; ///result grammar

    /// reading the contents of directory pointed by `path`
    Reader * reader = new Reader(logger);
    std::vector<std::pair<int, std::string>> file_contents = reader->read(path);
    delete reader;
    reader = nullptr;

    ///parsing the XML into a grammar
    Grammar_reader_from_XML gr(logger);
    grammar = gr.read(file_contents);

    ///reading went ok
    if (grammar!=nullptr)
    {
        ///removing binary rules
        Binarizer n(logger);
        n.normalize(grammar);
        ///normalization went ok
        if (grammar!=nullptr)
        {
            ///displaying the results
            std::cout << grammar->get_string_description();
            ///optionally the normalized grammar can be saved
//            Grammar_saver s;
//            s.write("output.txt", *grammar);
        }
    }
    else
    {
        logger->log_message("cannot open load grammar\n");
    }

    return grammar;
}
