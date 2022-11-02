#include "logger.h"


Logger::Logger(std::ostream* _output_buffer): output_stream(_output_buffer)
{

}

int Logger::add_file(const std::string& filename)
{
    file_record.push_back(filename);
    return file_record.size()-1;
}

int Logger::add_line(const int& linecount)
{
//    if (!file_record.empty()) ///we assume that for the running app such situation wont happen
//    {
        Line l;
        l.file_id = file_record.size()-1;
        l.linecount = linecount;
        line_record.push_back(l);
        return line_record.size()-1;
//    }
//    else
//    {
//        (*output_stream) << "no filename specified for logging\n";
//    }
}

void Logger::log_error(const int & line_id, const std::string & message)
{
//    if (line_id >= 0 &&line_id < line_record.size()) ///we assume that for the running app such situation wont happen
//    {
        Line l = line_record[line_id];
        error_buffer.push("in file " + file_record[l.file_id] + " at line " + std::to_string(l.linecount) + ": " + message);
//    }
//    else
//    {
//        (*output_stream) << ("we've got an error but can't even find the line :( The error reads:  " + message);
//    }

}


void Logger::log_message(const std::string & message)
{
        message_buffer.push(message);
}

void Logger::log_error(const std::string & message)
{
    error_buffer.push(message);
}

void Logger::write_messages_out()
{
    message_buffer.set_end_of_input(); ///assuming no further messages will be added
    while (!message_buffer.is_eof())
        (*output_stream) << message_buffer.pop();
}

void Logger::write_errors_out() ///assuming no further messages will be added
{
    error_buffer.set_end_of_input();
    while (!error_buffer.is_eof())
        (*output_stream) << error_buffer.pop();
}
