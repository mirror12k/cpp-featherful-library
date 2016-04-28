
#include "test_assert.hpp"

#include "../featherful/featherful.hpp"

using featherful::test_results;

bool test_assert()
{
    test_results results("assertion tests");

    TEST_NO_THROW(results, ASSERT(true), featherful::assertion_exception);
    TEST_THROW(results, ASSERT(false), featherful::assertion_exception);
    TEST_NO_THROW(results, ASSERT("asdf"), featherful::assertion_exception);
    TEST_THROW(results, ASSERT(nullptr), featherful::assertion_exception);

    results.finish();
    return results.is_successful();
}
