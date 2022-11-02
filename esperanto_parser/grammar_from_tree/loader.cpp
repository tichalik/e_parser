#include "grammar_from_tree/loader.h"


Grammar_from_tree_loader::Grammar_from_tree_loader(Logger *&l): Grammar_loader(l)
{

}

Grammar* Grammar_from_tree_loader::load(const std::string &path)
{

    /// reading the contents of directory pointed by `path`
    Reader * tree_reader = new Reader(logger);
    std::vector<std::pair<int, std::string>> file_contents = tree_reader->read(path);
    delete tree_reader;
    tree_reader = nullptr;

    /// reading the tree structures in the text input
    Rule_parser * rule_parser = new Rule_parser(logger);
    Grammar_from_tree* g = rule_parser->parse(file_contents); /// this stage the terminals of the grammar are the words in the file
    delete rule_parser;
    rule_parser = nullptr;

    /// turning current terminals (specific symbols of the language) into the cathegories they represent
    Rule_transformer * transformer = new Terminal_tagger(logger);
    g->set_head("S");
    Grammar_from_tree *  transformed_grammar =  transformer->transform(g);
    delete transformer;
    transformer = nullptr;

    if (transformed_grammar!= nullptr) /// if everything is ok
    {
        transformed_grammar->update(); /// final touches
        std::cout << transformed_grammar->get_string_description() << "\n"; /// presentation of the outcome
    }

    return transformed_grammar;
}
