#ifndef BUFFERS
#define BUFFERS

#include <vector>
#include <semaphore>
#include <mutex>
#include <string>

#include <list>

#include <iostream> //debug!!!
/**
 * A Buffer class for wrapping up parallel data flow.
 * Because it's a template, can't make a polymorphic class out of it -- and it's a shame, because sometimes the buffers could be used in serial computing and do not need all the things required for parallel
 * T must imlement a copy/carry constructor, but it can be just the default
 */


template<class T> //T must have default constructor for making the EOF object
class Buffer
{
    static const int max_size=1000; /**< The maximal number of elements in the buffer */

//    bool end_of_input;
//    std::mutex lock_end_of_input;
    std::mutex lock_buffer; /**< mutex for guarding the access to the buffer */
    std::counting_semaphore<Buffer::max_size> buffer_data; /**< semaphore signalizing presence of data in the buffer. should start with the value 0 */
    std::counting_semaphore<Buffer::max_size> buffer_empty;/**< semaphore signalizing empty space in the buffer. should start with Buffer::max_size */

    T * eof = nullptr; /**< the value which will mark the end of input; if found in buffer, no more data will be inserted */

    std::list<T*> buffer; /**< the proper buffer; it's a list so it can work as queue */
public:
    int no_push = 0;
    int no_pop = 0;

/** \brief checks whether the provided value is marks the end of input
 *
 * \param i the value which should be checked
 * \return true if end of input
 *
 */

    bool is_eof()
    {
        lock_buffer.lock();
        bool tmp = buffer.front() == nullptr;
        lock_buffer.unlock();
        return tmp;
    }

/** \brief Constructor
 * initializes semaphores with the right values
 *
 *
 */

    Buffer(): lock_buffer(), buffer_data(std::counting_semaphore<max_size>(0)),buffer_empty(std::counting_semaphore<max_size>(max_size))
    {
    };


/** \brief Inserts into queue
 *
 * \param input what to enter; it is then pushed_back() to the list
 *
 */

    void push(const T &input)
    {
        T* tmp = new T(input);
        buffer_empty.acquire();
        lock_buffer.lock();

        no_push++;
        buffer.push_back(tmp);

        lock_buffer.unlock();
        buffer_data.release();
    };
/** \brief Retrieves next element in queue (with decrementing the size)
 *
 * \return the next element
 *
 */

    T pop()
    {

        buffer_data.acquire();
        lock_buffer.lock();

        no_pop++;
        T* tmp_ptr = buffer.front();
        buffer.pop_front();

        lock_buffer.unlock();
        buffer_empty.release();

        T tmp = *tmp_ptr;
        delete tmp_ptr;
        tmp_ptr = nullptr;

        return tmp;
    }

/** \brief signalizes that there won't be any more input
 *
 *
 *
 */

    void set_end_of_input()
    {
        std::cout << "  setting end of input... ";
        buffer_empty.acquire();
        lock_buffer.lock();

        buffer.push_back(nullptr);

        std::cout << "set!\n";

        lock_buffer.unlock();
        buffer_data.release();
        std::cout << "  getting out\n";
    }

/** \brief for debugging
 *
 */

    void print_all()
    {
        std::cout << "printing all\n";

        lock_buffer.lock();

        for (auto i=buffer.begin(); i!=buffer.end(); i++)
            if (*i != nullptr)
                std::cout << "\t" << **i << "\n";

        lock_buffer.unlock();
    }

    ~Buffer()
    {
        std::cout << "destructing buffer\n";
        lock_buffer.lock();
        while (buffer.front()!=nullptr)
        {
            std::cout << "not all input in buffer has beeen emptied!\n";
            delete buffer.front();
            buffer.pop_front();
        }
    }

};

#endif // BUFFERS
