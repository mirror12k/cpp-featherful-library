
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
    ~range_exception();
    const char* what() const noexcept;
private:
    const char* msg;
};

class invalid_exception : public exception
{
public:
    invalid_exception(const char* reason);
    ~invalid_exception();
    const char* what() const noexcept;
private:
    const char* msg;
};

class iterator_exception : public exception
{
public:
    iterator_exception(const char* reason);
    ~iterator_exception();
    const char* what() const noexcept;
private:
    const char* msg;
};

}


