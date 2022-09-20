#ifndef LOGGER
#define LOGGER

#include <iostream>
#include <string>


class Logger
{
    std::ostream * output_stream;
    bool show_messages;
public:
    Logger(std::ostream* _output_stream, bool _show_messages);
    Logger(const Logger& logger,  bool _show_messages);
    void log_error(const int & line, const std::string &message );
    void log_message(const std::string &message);
//    void set_filename(const std::string& _filename);
};

#endif // LOGGER
