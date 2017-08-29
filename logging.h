#ifndef LOGGING_H
#define LOGGING_H

#include <exception>
#include <sstream>


#define THROW_EXCEPTION(message) \
    { \
        std::stringstream ss; \
        ss << "file:" << __FILE__ << ":" << __LINE__ << " msg:" << message; \
        throw std::runtime_error(ss.str().c_str()); \
    }


#endif // LOGGING_H
