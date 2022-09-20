#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>


#include "word.h"
#include "tokenizer.h"
#include "reader.h"
#include "tagger.h"
#include "grammar_from_tree/reader.h"
#include "parser.h"
#include "writer.h"

//#include "loader.h"
#include "grammar_from_XML/loader.h"
#include "lojban/tagger.h"
#include "lojban/tokenizer.h"


#include<list>


int main(int args, char* argv[])
{

//  the following section deals with loading the grammar

//    Grammar_loader  * gr = new Grammar_from_XML_loader();
    Grammar_loader * gr = new Grammar_from_tree_loader();
    Grammar * transformed_grammar = gr->read("c:/Users/huawei/Parser/formal grammar tests/trees");
//    Grammar * transformed_grammar = gr->read("C:/Users/huawei/Desktop/lojban/form_of_original3.xml");

////  the following section bothers with processing the input text to be parsed
//


//    //reading the files
    Reader* reader = new Reader();
    std::vector<std::string> file_contents =  reader->read("C:/Users/huawei/parser/formal grammar tests/fgs");

    //tokenization
//    Tokenizer * tokenizer = new Lojban_tokenizer();
    Tokenizer * tokenizer = new Between_whitespaces_tokenizer();
    std::vector<Word> tokenized_words;
    for (std::string s: file_contents)
        tokenized_words.push_back(tokenizer->tokenize(s));


//    tagging
    std::vector<Word> tagged_words;
//    Tagger * tagger = new Lojban_tagger();
    Tagger * tagger = new Part_of_speech_tagger();
    for (Word w: tokenized_words)
        tagged_words.push_back(tagger->tag(w));


//
//    for (auto w: tagged_words)
//        std::cout << w << "\n";
//
    std::vector<Parsing_node> parsed_words;
    Parser * parser = new CYK_parser(transformed_grammar);
    for (Word w: tagged_words)
    {
        Parsing_node parsed = parser->parse(w);
        if (parsed.to_string()!="")
            parsed_words.push_back(parsed);
    }



    for (auto w: parsed_words)
        std::cout <<">\t"<< w.to_string() << "\n";


//
//    Writer * writer = new Simple_writer("c:/Users/huawei/parser/formal grammar tests/results.txt", b_result_strings);
//    writer->write();
//
//    delete writer;
//    writer = nullptr;
//
    delete reader;
    reader = nullptr;

    delete tokenizer;
    tokenizer = nullptr;

    delete tagger;
    tagger = nullptr;

    delete parser;
    parser = nullptr;

    delete transformed_grammar;
    transformed_grammar = nullptr;

    delete gr;
    gr = nullptr;



    return 0;
}
