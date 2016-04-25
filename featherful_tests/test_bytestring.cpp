

#include "test_bytestring.hpp"

#include "../featherful.hpp"

using featherful::test_results;
using featherful::bytestring;
using featherful::list;

bool test_bytestring()
{
    test_results bytestring_tests("all bytestring tests");
    bytestring_tests.result(test_bytestring_basic());

    bytestring_tests.finish();
    return bytestring_tests.is_successful();
}


bool test_bytestring_basic()
{
    test_results results("bytestring basic tests");

    TEST(results, bytestring("asdf").length() == 4);
    TEST(results, bytestring("asdf")[0] == 'a');
    TEST(results, bytestring("asdf")[2] == 'd');
    TEST(results, bytestring("asdf")[-1] == 'f');
    TEST(results, bytestring("asdf")[-3] == 's');

    TEST(results, bytestring("asdf").substring(2) == bytestring("df"));
    TEST(results, bytestring("asdf").substring(-3, -2) == bytestring("sd"));
    TEST(results, bytestring("asdf").substring(0, -3) == bytestring("as"));
    TEST(results, bytestring("asdf").concat("ghjk") == bytestring("asdfghjk"));
    TEST(results, bytestring("asdf").concat("ghjk").substring(2,5) == bytestring("dfgh"));
    TEST(results, bytestring("hello world").strip('l') == bytestring("heo word"));
    TEST(results, bytestring("hello world").strip("leo") == bytestring("h wrd"));
    TEST(results, bytestring("hello world\r\n").strip_whitespace() == bytestring("helloworld"));
    TEST(results, bytestring("hello world\r\n").trim() == bytestring("hello world"));
    TEST(results, bytestring("\t\thello world\r\n").trim() == bytestring("hello world"));
    TEST(results, bytestring("\t\t  \r\n").trim() == bytestring(""));

    results.finish();
    return results.is_successful();
}

