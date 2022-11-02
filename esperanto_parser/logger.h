#ifndef LOGGER
#define LOGGER

#include <iostream>
#include <string>

#include "buffers.h"

/** \brief class for communication with the user
 *
 */

class Logger
{
    /** \brief structure for storing information about registered lines
     */

    struct Line
    {
        int file_id; /**< index of the source file in `file_record` */
        int linecount; /**< line number in the original file */
    };


    std::vector<std::string> file_record;/**< names of the source files */
    std::vector<Line> line_record; /**< record of the lines */

    Buffer<std::string> message_buffer; /**< buffer for miscellaneous messages */
    Buffer<std::string> error_buffer; /**< buffer for error messages */
    std::ostream * output_stream; /**< where the messages will go */

public:
    /** \brief constructor
     *
     * \param output_buffer pointer to the output buffer
     */

    Logger(std::ostream* output_buffer);

    /** \brief registers file in the logger
     *
     * \return received file_id
     *
     */

    int add_file(const std::string& filename);

    /** \brief registers line in the last registered file
     *
     * \param linecount position in the original file
     * \return unique line_id
     *
     */

    int add_line(const int& linecount);

    /** \brief adds message to the message pool.
     *
     */

    void log_message(const std::string & message);

    /** \brief adds error to the error pool.
     * the ouput message is a concatenation of position of the line
     * and the provided message
     *
     */

    void log_error(const int & line_id, const std::string & message);

    /** \brief adds error to the error pool
     *
     */
    void log_error(const std::string & message);

    /** \brief at once displays all logged errors. can only be called once in object's lifetime
     *
     */

    void write_errors_out();

    /** \brief at once displays all logged messages. can only be called once in object's lifetime
     *
     */

    void write_messages_out();
};

#endif // LOGGER
