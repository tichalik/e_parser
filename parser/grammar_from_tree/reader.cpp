


#include "grammar_from_tree/reader.h"


Grammar_from_tree_loader::Grammar_from_tree_loader()
{

}

Grammar* Grammar_from_tree_loader::read(const std::string &path)
{



    Buffer<std::string> * b_file_contents = new Buffer<std::string>();
    Reader * tree_reader = new Reader(b_file_contents);
//    std::thread tr(&Reader::read, tree_reader, "c:/Users/huawei/banan/Projekt/formal grammar tests/trees");
    tree_reader->read(path);

    b_file_contents->print_all();
//    std::cout << "all prunt!\n";




    Buffer<Grammar_from_tree> *b_grammar = new Buffer<Grammar_from_tree>();
    Rule_parser * rule_parser = new Rule_parser(b_file_contents, b_grammar);
//    std::thread rp(&Rule_parser::parse, rule_parser);
    rule_parser->parse();

    Rule_transformer * transformer = new Terminal_tagger();
    Grammar_from_tree g = b_grammar->pop();
    g.set_head("S");
    Grammar_from_tree *  transformed_grammar =  new Grammar_from_tree (transformer->transform(g));

//    std::cout << transformed_grammar << "\n";


//    rp.join();
//    tr.join();

    delete rule_parser;
    rule_parser = nullptr;

    delete tree_reader;
    tree_reader = nullptr;

    delete b_file_contents;
    b_file_contents = nullptr;

    delete b_grammar;
    b_grammar = nullptr;

    return transformed_grammar;
}
