


#include "grammar_from_tree/loader.h"


Grammar_from_tree_loader::Grammar_from_tree_loader(Logger *&l): Grammar_loader(l)
{

}

Grammar* Grammar_from_tree_loader::load(const std::string &path)
{



    Reader * tree_reader = new Reader(logger);
    std::vector<std::pair<int, std::string>> file_contents = tree_reader->read(path);

//    for(std::string s :file_contents)
//        std::cout << s << "\n";


    Rule_parser * rule_parser = new Rule_parser(logger);
    Grammar_from_tree* g = rule_parser->parse(file_contents);

    Rule_transformer * transformer = new Terminal_tagger(logger);
    g->set_head("S");
    Grammar_from_tree *  transformed_grammar =  transformer->transform(g);

    if (transformed_grammar!= nullptr)
    {
        transformed_grammar->update();
        std::cout << (*transformed_grammar) << "\n";
    }





    delete rule_parser;
    rule_parser = nullptr;

    delete tree_reader;
    tree_reader = nullptr;


    return transformed_grammar;
}
