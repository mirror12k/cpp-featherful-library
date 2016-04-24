
#pragma once

#include "exception.hpp"

class assertion_exception : public exception
{
public:
    assertion_exception(const char* filename, int line_number, const char* code);
    assertion_exception(const char* filename, int line_number, const char* code, const char* test_name);
    const char* what() const noexcept;

private:
    const char* filename;
    const int line_number;
    const char* code;
    const char* test_name;
};

#define ASSERT(X, ...) do { if (! (X)) throw assertion_exception(__FILE__, __LINE__, #X, ##__VA_ARGS__); } while (0)

#ifdef ENABLE_DEBUG
#define DEBUG_ASSERT(X, ...) ASSERT(X, ##__VA_ARGS__)
#else
#define DEBUG_ASSERT(X, ...)
#endif


