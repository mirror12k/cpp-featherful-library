

#include "test_bytestring.hpp"

#include "../featherful.hpp"

using featherful::test_results;
using featherful::bytestring;
using featherful::list;

bool test_bytestring()
{
    test_results bytestring_tests("all bytestring tests");
    bytestring_tests.result(test_bytestring_basic());
    bytestring_tests.result(test_bytestring_insert());

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
    TEST(results, bytestring("b\t\t  \r\na").trim() == bytestring("b\t\t  \r\na"));

    results.finish();
    return results.is_successful();
}




bool test_bytestring_insert()
{
    test_results results("bytestring insertion tests");

    TEST(results, bytestring("asdf").insert("qwer") == bytestring("asdfqwer"));
    TEST(results, bytestring("asdf").insert("qwer", 2) == bytestring("asqwerdf"));
    TEST(results, bytestring("asdf").insert("qwer", 0) == bytestring("qwerasdf"));
    TEST(results, bytestring("asdf").erase(0, 1) == bytestring("df"));
    TEST(results, bytestring("asdf").erase(1, 2) == bytestring("af"));
    TEST(results, bytestring("asdf").erase(3) == bytestring("asd"));
    TEST(results, bytestring("asdf").erase(-2) == bytestring("as"));
    TEST(results, bytestring("hello hello therello").remove("el") == bytestring("hlo hlo therlo"));
    TEST(results, bytestring("hello hello therello").remove("hell") == bytestring("o o therello"));
    TEST(results, bytestring("hello hello therello").remove("llo ") == bytestring("hehetherello"));
    TEST(results, bytestring("hello hello therello").replace("hello", "goodbye") == bytestring("goodbye goodbye therello"));
    TEST(results, bytestring("hello hello therello").replace("ello", "") == bytestring("h h ther"));
    TEST(results, bytestring("hello world!").splice("goodbye", 0, 4) == bytestring("goodbye world!"));
    TEST(results, bytestring("hello world!").splice("olleh", -6, -2) == bytestring("hello olleh!"));
    TEST(results, bytestring("hello world!").splice("everyone", 6) == bytestring("hello everyone"));

    results.finish();
    return results.is_successful();
}












