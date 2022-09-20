


#include "grammar_from_tree/loader.h"


Grammar_from_tree_loader::Grammar_from_tree_loader()
{

}

Grammar* Grammar_from_tree_loader::read(const std::string &path)
{


    Reader * tree_reader = new Reader();
//    std::vector<std::string> file_contents = tree_reader->read(path);
    std::vector<std::string> file_contents = tree_reader->read("C:/Users/huawei/Parser/formal grammar tests/trees");

//    for(std::string s :file_contents)
//        std::cout << s << "\n";


    Rule_parser * rule_parser = new Rule_parser();
    Grammar_from_tree g = rule_parser->parse(file_contents);

    Rule_transformer * transformer = new Terminal_tagger();
    g.set_head("S");
    Grammar_from_tree *  transformed_grammar =  new Grammar_from_tree (transformer->transform(g));




    std::cout << (*transformed_grammar) << "\n";




    delete rule_parser;
    rule_parser = nullptr;

    delete tree_reader;
    tree_reader = nullptr;

    return transformed_grammar;
}
