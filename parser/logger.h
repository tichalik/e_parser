#ifndef LOGGER
#define LOGGER

#include <iostream>
#include <string>

#include "buffers.h"

class Logger
{
    struct Line
    {
        int file_id, linecount;
    };

    std::vector<std::string> file_record;
    std::vector<Line> line_record;

    Buffer<std::string> message_buffer;
    Buffer<std::string> error_buffer;
    std::ostream * output_stream;

public:
    Logger(std::ostream* output_buffer);

    int add_file(const std::string& filename);
    int add_line(const int& linecount);

    void log_message(const std::string & message);
    void log_error(const int & line_id, const std::string & message);
    void log_error(const std::string & message);

    void write_errors_out();
    void write_messages_out();
};

#endif // LOGGER
