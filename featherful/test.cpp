
#include "test.hpp"

#include <cstdio>

namespace featherful
{

test_results::test_results(const char* test_name) : test_name(test_name)
{}

void test_results::result(bool passed)
{
    this->test_count++;
    if (passed)
        this->test_passed++;
    else
        fprintf(stderr, "test #%d of '%s' failed\n", this->test_count, this->test_name);
}

void test_results::result(bool passed, const char* filename, int line_number, const char* code)
{
    this->test_count++;
    if (passed)
        this->test_passed++;
    else
        fprintf(stderr, "test #%d of '%s' failed (at %s:%d): %s\n",
            this->test_count, this->test_name, filename, line_number, code);
}

void test_results::finish() const
{
    const char* msg;
    if (this->is_successful())
        msg = "successful";
    else
        msg = "failed";
    printf("test '%s' [%d/%d]: %s\n", this->test_name, this->test_passed, this->test_count, msg);
}

bool test_results::is_successful() const
{
    return this->test_count == this->test_passed;
}

}


