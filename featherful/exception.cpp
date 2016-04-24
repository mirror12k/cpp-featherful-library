
#include "exception.hpp"

#include <cstdio>

namespace featherful
{

range_exception::range_exception(const char* reason, int index)
{
    char* buffer = new char[2048];
    snprintf(buffer, 2048, "range exception: '%s' : %d", reason, index);
    this->msg = buffer;
}
range_exception::range_exception(const char* reason, int index, int index2)
{
    char* buffer = new char[2048];
    snprintf(buffer, 2048, "range exception: '%s' : %d, %d", reason, index, index2);
    this->msg = buffer;
}

range_exception::~range_exception()
{
    delete this->msg;
}

const char* range_exception::what() const noexcept
{
    return this->msg;
}


invalid_exception::invalid_exception(const char* reason)
{
    char* buffer = new char[2048];
    snprintf(buffer, 2048, "invalid exception: '%s'", reason);
    this->msg = buffer;
}

invalid_exception::~invalid_exception()
{
    delete this->msg;
}

const char* invalid_exception::what() const noexcept
{
    return this->msg;
}

iterator_exception::iterator_exception(const char* reason)
{
    char* buffer = new char[2048];
    snprintf(buffer, 2048, "iterator exception: '%s'", reason);
    this->msg = buffer;
}

iterator_exception::~iterator_exception()
{
    delete this->msg;
}

const char* iterator_exception::what() const noexcept
{
    return this->msg;
}

}
