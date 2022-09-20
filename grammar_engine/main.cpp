#include <fstream>
#include <iostream>
#include <string>

#include "grammar.h"
#include "grammar_reader.h"
#include "grammar_writer.h"
#include "word.h"
#include "generator.h"


int main(int argn, const char* args[])
{
//    for (int i=0; i<argn; i++)
//        std::cout << args[i] <<std::endl;

    if (argn == 1)
    {
        std::cout << "hello to grammar engine! this software generates N words from a given grammar.\n";
        std::cout << "usage:\n";
        std::cout << "\t -i filename\t\tname of the input file\n";
        std::cout << "\t -ot filename\t\tname of the output file of the trees \n\t\t\t(if skipped, the console is the output)\n";
        std::cout << "\t -os filename\t\tname of the output file of the strings \n\t\t\t(if skipped, the console is the output)\n";
        std::cout << "\t -n number\t\tnumber of words to generate\n";
        std::cout << "\t -u \t\t\tuser picks which rule to apply, otherwise it's randomly chosen\n";
        std::cout << "\t -t \t\t\toutput to console in the tree form, otherwise in normal strings\n";
        std::cout << "\t -l filename\t\tlogs the formation process to filename, if skipped no logging is done \n\n";
    }
    else
    {
        bool all_ok = true;

        std::string input_file_n;
        std::string t_output_file_n;
        std::string s_output_file_n;
        std::string logging_file_n;
        int no_words = 0;
        bool is_auto = true;
        bool is_tree = false;

        for (int i=1; i<argn; i++)
        {
            std::string arg(args[i]);
            if (i+1!=argn)
            {
                if (arg == "-i")
                {
                    input_file_n = args[++i];
                }

                else if (arg == "-ot")
                    t_output_file_n = args[++i];
                else if (arg == "-os")
                    s_output_file_n = args[++i];
                else if (arg == "-l")
                    logging_file_n = args[++i];
                else if (arg == "-n")
                {
                    std::string number = args[++i];
                    try
                    {
                        no_words = std::stoi(number); //EXEPTION HANDLING!!!
                    }
                    catch(std::exception& e)
                    {
                        std::cout << "Error! cannot convert " <<  number  << " to a number \n";

                        all_ok = false;
                        no_words = 0;
                    }

                }

            }
            if (arg == "-t")
                is_tree = true;
            else if (arg == "-u")
                is_auto = false;
        }

        std::ofstream logging_file;
        if (logging_file_n!="")
        {
            std::cout << "opening the logging file\n";
            logging_file.open(logging_file_n);
            if (!logging_file.is_open())
            {
                all_ok = false;
                std::cout << "cannot open that file\n";
            }

        }
        std::cout << "\ninput: " << input_file_n <<"\n";
        std::cout << "tree output: " << t_output_file_n <<"\n";
        std::cout << "string output: " << s_output_file_n <<"\n";
        std::cout << "logging: " << logging_file_n <<"\n";
        std::cout << "is auto: " << is_auto <<"\n";
        std::cout << "is tree: " << is_tree <<"\n";
        std::cout << "number of words: " << no_words <<"\n";
        std::cout << "is all ok: " << all_ok<<"\n";


        if (all_ok)
        {
            Logger l((logging_file.is_open())?(&logging_file):(&std::cout), logging_file.is_open()); //czy is_open() dzia³¹????

            Interface interface(&std::cout, &std::cin);
            Grammar_reader* g_reader = new BNF_without_ors_reader( l, input_file_n);
            Grammar grammar = g_reader->read();
        //

            if (g_reader->is_ok())
            {
                std::cout << grammar << "\n--------------\n";

                std::vector<Word> words;

                Generator g(l, interface);
                for (int i =0; i<no_words && g.is_ok(); i++)
                {

                    std::cout << "generating " <<i+1 <<"/"<<no_words<<"\n";
                    words.push_back(g.generate__word(grammar, is_auto));
                }

                if (t_output_file_n!="")
                {

                    std::cout << "saving trees to file " << t_output_file_n <<"\n";

                    std::ofstream output_file(t_output_file_n);
                    if (output_file)
                    {
                        for (Word w: words)
                            output_file << w.to_tree_string() << "\n";
                        output_file.close();
                    }
                    else
                    {
                        std::cout << "Error, cannot open " << t_output_file_n << " file. printing out to the console \n";
                        t_output_file_n = "";
                    }
                }
                if (s_output_file_n!="")
                {

                    std::cout << "saving strings to file " << s_output_file_n <<"\n";

                    std::ofstream output_file(s_output_file_n);
                    if (output_file)
                    {
                        for (Word w: words)
                            output_file << w.to_string() << "\n";
                        output_file.close();
                    }
                    else
                    {
                        std::cout << "Error, cannot open " << s_output_file_n << " file. printing out to the console \n";
                        s_output_file_n = "";
                    }
                }
                if (s_output_file_n==""||t_output_file_n=="")
                {
                    std::cout << "constructed words:\n";
                    for (Word w: words)
                    {
                        if (is_tree)
                            std::cout << w.to_tree_string() << "\n";
                        else
                            std::cout << w.to_string() << "\n";
                    }
                }
            }

            if(logging_file.is_open())
                logging_file.close();

            delete g_reader;
            g_reader = nullptr;
        }

    }


}

