#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>


#include "word.h"
#include "tokenizer.h"
#include "reader.h"
#include "tagger.h"
#include "grammar_from_tree/loader.h"
#include "parser.h"
#include "writer.h"
#include "buffers.h"
#include "parse_tree.h"

#include "grammar_from_XML/loader.h"
#include "lojban/tagger.h"
#include "lojban/tokenizer.h"

const int NO_THREADS = 1;



int main(int args, char* argv[])
{


    Logger *logger = new Logger(&std::cout);

//  the following section deals with loading the grammar

//    Grammar_loader  * gr = new Grammar_from_XML_loader(logger);
    Grammar_loader * gr = new Grammar_from_tree_loader(logger);
    Grammar * transformed_grammar = gr->load("../trees");
//    Grammar * transformed_grammar = gr->load("C:/Users/huawei/Desktop/lojban/form_of_original3.xml");

    if (transformed_grammar!=nullptr)
    {
            ////  the following section bothers with processing the input text to be parsed
    //

    //    //reading the files
        Buffer<std::pair<int, std::string>> * string_buffer = new Buffer<std::pair<int, std::string>>;
        Reader* reader = new Reader(logger);
        for (const std::pair<int, std::string> &s: reader->read("../fgs") )
            string_buffer->push(s);

        delete reader;
        reader = nullptr;
        string_buffer->set_end_of_input();

        Buffer<std::pair<int, Parse_tree*>> * parsed_buffer = new Buffer<std::pair<int, Parse_tree*>>;
        std::vector<std::thread> thread_poll;


        Tokenizer * tokenizer = new Between_whitespaces_tokenizer(logger);
        Tagger * tagger = new Part_of_speech_tagger(logger);
        Parser * parser = new CYK_parser(transformed_grammar, logger);


        for (int i=0; i<NO_THREADS; i++)
            thread_poll.push_back(std::thread(
                              [tokenizer, tagger, parser, string_buffer, parsed_buffer] ()
                              {
                                  while(!string_buffer->is_eof())
                                    {
                                        std::pair<int, Word*> tokenized = tokenizer->tokenize(string_buffer->pop());
                                        if (tokenized.second != nullptr)
                                        {
//                                            std::cout << "all tokenized\n";
                                            std::pair<int, Word*> tagged = tagger->tag(tokenized);
                                            if (tagged.second!= nullptr)
                                            {
//                                                std::cout << "all tagged\n";
                                                for (std::pair<int, Parse_tree*> parsed: parser->parse(tagged))
                                                    parsed_buffer->push(parsed);

//                                                std::cout << "all parsed\n";
                                                delete tagged.second;
//                                                std::cout << "all_parsed/deleted\n";
                                            }
                                        }

                                    }
                              }));

        for (int i =0; i<NO_THREADS; i++)
            thread_poll[i].join();

        parsed_buffer->set_end_of_input();

        delete tokenizer;
        delete tagger;
        delete parser;

        std::vector<std::pair<int, Parse_tree*>> to_delete;

        while (!parsed_buffer->is_eof())
        {
             std::pair<int, Parse_tree*> p = parsed_buffer->pop();
             std::cout << "->\t" << p.second->to_string() << "\n";
//             delete p.second;
            to_delete.push_back(p);
        }

        for (std::pair<int, Parse_tree*> p: to_delete)
            delete p.second;

    //
    //    Writer * writer = new Simple_writer("c:/Users/huawei/parser/formal grammar tests/results.txt", b_result_strings);
    //    writer->write();
    //
    //    delete writer;
    //    writer = nullptr;
    //


        delete transformed_grammar;
        transformed_grammar = nullptr;


        delete string_buffer;
        delete parsed_buffer;
    }
    else
    {
        logger->log_error("cannot load grammar\n");
    }
    logger->write_errors_out();
    logger->write_messages_out();


    delete gr;
    delete logger;




    return 0;
}
