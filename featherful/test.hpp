
#pragma once

#include "assert.hpp"


namespace featherful
{

class test_results
{
public:
    test_results(const char* test_name);

    void result(bool passed, const char* filename, int line_number, const char* code);
    void finish() const;
    bool is_successful() const;

private:
    const char* test_name;
    int test_count = 0;
    int test_passed = 0;
};

#define TEST_RESULT(RESULTS, STATUS, CODE) RESULTS.result(STATUS, __FILE__, __LINE__, CODE)
#define TEST(RESULTS, CODE) do { if (CODE) { TEST_RESULT(RESULTS, true, #CODE); } else { TEST_RESULT(RESULTS, false, #CODE); } } while (0)
#define TEST_THROW(RESULTS, CODE, EXCEPT) do { try { CODE; TEST_RESULT(RESULTS, false, #CODE); } catch (const EXCEPT& e) { TEST_RESULT(RESULTS, true, #CODE); } } while (0)


}
