
#include "assert.hpp"

#include <cstdio>

assertion_exception::assertion_exception(const char* filename, int line_number, const char* code)
: filename(filename), line_number(line_number), code(code), test_name("assertion")
{}
assertion_exception::assertion_exception(const char* filename, int line_number, const char* code, const char* test_name)
: filename(filename), line_number(line_number), code(code), test_name(test_name)
{}

const char* assertion_exception::what() const noexcept
{
    char* buffer = new char[2048];
    snprintf(buffer, 2048, "assertion exception [%s failed at %s:%d]: %s", this->test_name, this->filename, this->line_number, this->code);
    return buffer;
}
