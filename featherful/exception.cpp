
#include "exception.hpp"

#include <cstdio>

namespace featherful
{

range_exception::range_exception(const char* reason, int index) : reason(reason), index(index), index2(0), is_double_index(false)
{}
range_exception::range_exception(const char* reason, int index, int index2) : reason(reason), index(index), index2(index2), is_double_index(true)
{}

const char* range_exception::what() const noexcept
{
    char* buffer = new char[512];
    if (this->is_double_index)
        snprintf(buffer, 512, "range exception: '%s' : %d, %d", this->reason, this->index, this->index2);
    else
        snprintf(buffer, 512, "range exception: '%s' : %d", this->reason, this->index);
    return buffer;
}


invalid_exception::invalid_exception(const char* reason) : reason(reason)
{}
const char* invalid_exception::what() const noexcept
{
    return this->reason;
}

}
