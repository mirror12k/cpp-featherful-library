
#include "../featherful/featherful.hpp"

#include "test_list.hpp"
#include "test_bytestring.hpp"
#include "test_assert.hpp"

using featherful::test_results;

bool all_featherful_tests()
{
    test_results all_tests("all featherful tests");

    all_tests.result(test_list());
    all_tests.result(test_bytestring());
    all_tests.result(test_assert());

    all_tests.finish();
    return all_tests.is_successful();
}


