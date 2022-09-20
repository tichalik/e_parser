#include "logger.h"


Logger::Logger( std::ostream* _output_stream, bool _show_messages): output_stream(_output_stream), show_messages(_show_messages)
{
//    std::cout << "show messages? " <<show_messages <<"\n";
    (*output_stream) << "starting the log\n";
}

Logger::Logger(const Logger& logger,  bool _show_messages): show_messages(_show_messages)
{
//    std::cout << "copy constructor!\n";
    this->output_stream = logger.output_stream;
}

void Logger::log_error(const int & line, const std::string &message )
{
    (*output_stream) <<"\tError! At line " << line << ": "<< message <<"\n";

}
void Logger::log_message(const std::string &message )
{
    if (show_messages)
    {
        (*output_stream)<< message <<"\n";

    }

}

//void Logger::set_filename(const std::string& _filename)
//{
//    filename = _filename;
//}
