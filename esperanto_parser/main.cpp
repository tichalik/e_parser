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


///number of threads the parsing runs on
const int NO_THREADS = 4;



int main(int args, char* argv[])
{


    ///one logger to working as the user interface
    ///initialized with cout as the ouput buffer
    Logger *logger = new Logger(&std::cout);


//    ///loading grammar from XML file
//    Grammar_loader  * gr = new Grammar_from_XML_loader(logger);
//    Grammar * transformed_grammar = gr->load("../xml");

    ///loading grammar from a treebank
    Grammar_loader * gr = new Grammar_from_tree_loader(logger);
    Grammar * transformed_grammar = gr->load("../trees");

    ///disposing of grammar reader
    delete gr;
    gr = nullptr;

    ///if loading the grammar succeeeded
    if (transformed_grammar!=nullptr)
    {
        ///reading input files

        ///buffer for concurrent retrieval of data
        Buffer<std::pair<int, std::string>> * string_buffer = new Buffer<std::pair<int, std::string>>;

        ///filling the buffer with content of input files
        Reader* reader = new Reader(logger);
        for (const std::pair<int, std::string> &s: reader->read("../fgs") )
            string_buffer->push(s);

        ///disposing of reader
        delete reader;
        reader = nullptr;

        ///no more contents will be added to the buffer
        string_buffer->set_end_of_input();

        ///buffer for concurrent input and retrieval of results of parsing
        Buffer<std::pair<int, Parse_tree*>> * parsed_buffer = new Buffer<std::pair<int, Parse_tree*>>;

        ///thread pool
        std::vector<std::thread> thread_poll;

        ///template parser that will be cloned later
        Parser * original_parser = new CYK_parser(transformed_grammar, logger);

        ///if grammar passed to the parser does not create critical errors
        if (original_parser->is_everything_ok())
        {
             ///the process running concurrently
             for (int i=0; i<NO_THREADS; i++)
                 thread_poll.push_back(std::thread(

                                  [original_parser, logger, string_buffer, parsed_buffer] ()
                                  {
                                      ///initializing the pipeline elements
                                        Tokenizer * tokenizer = new Between_whitespaces_tokenizer(logger);
                                        Tagger * tagger = new Part_of_speech_tagger(logger);
                                        Parser * parser = original_parser->clone();
                                      while(!string_buffer->is_eof())
                                        {
                                            ///tokenization
                                            std::pair<int, Word*> tokenized = tokenizer->tokenize(string_buffer->pop());
                                            ///checking if tokenization was successful
                                                ///with `Between_whitespaces_tokenizer` it is impossible to get a nullptr
                                                ///but for the sake of completeness
                                            if (tokenized.second != nullptr)
                                            {
                                                ///tagging -- a new `Word` is allocated
                                                std::pair<int, Word*> tagged = tagger->tag(tokenized);
                                                ///checking if tagging was successfull
                                                if (tagged.second!= nullptr)
                                                {
                                                    ///parsing
                                                    for (std::pair<int, Parse_tree*> parsed: parser->parse(tagged))
                                                        ///all possible parses are included
                                                        parsed_buffer->push(parsed);
                                                    ///delallocating `Word` produced by tagger
                                                    delete tagged.second;
                                                }
                                            }
                                        }
                                        ///dealocation
                                        delete tokenizer;
                                        delete tagger;
                                        delete parser;
                                  }));

            ///synchronization
            for (int i =0; i<NO_THREADS; i++)
                thread_poll[i].join();

            ///no more input will be added to this buffer
            parsed_buffer->set_end_of_input();

            delete original_parser;

            ///printing out the results
            while (!parsed_buffer->is_eof())
            {
                 ///acquiring parse results
                 std::pair<int, Parse_tree*> p = parsed_buffer->pop();
                 ///printing out
                 std::cout << "->\t" << p.second->to_string() << "\n";
                 ///the result will not be used anymore -- deallocating
                 delete p.second;
            }

            ///deallocating grammar
            delete transformed_grammar;
            transformed_grammar = nullptr;

            ///deallocating buffers
            delete string_buffer;
            delete parsed_buffer;
        }
    }
    ///critical error occurred during loading the grammar
    else
    {
        logger->log_error("cannot load grammar\n");
    }

    ///no more text will be send to logger;
    ///starting printing out
    logger->write_errors_out();
    logger->write_messages_out();


    ///disposal of the logger
    delete logger;
    logger = nullptr;



    return 0;
}
