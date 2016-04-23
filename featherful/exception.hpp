
#pragma once

#include <exception>

using std::exception;

namespace featherful
{

class range_exception : public exception
{
public:
    range_exception(const char* reason, int index);
    range_exception(const char* reason, int index, int index2);
    const char* what() const noexcept;

    const char* reason;
    const int index;
    const int index2;
    const bool is_double_index;
};

class invalid_exception : public exception
{
public:
    invalid_exception(const char* reason);
    const char* what() const noexcept;

    const char* reason;
};

}


