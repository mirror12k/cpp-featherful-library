

#include "test_bytestring.hpp"

#include "../featherful/featherful.hpp"

using featherful::test_results;
using featherful::bytestring;
using featherful::list;
using featherful::to_string;

bool test_bytestring()
{
    test_results bytestring_tests("all bytestring tests");
    bytestring_tests.result(test_bytestring_basic());
    bytestring_tests.result(test_bytestring_insert());
    bytestring_tests.result(test_bytestring_search());
    bytestring_tests.result(test_bytestring_to_string());

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
    TEST(results, bytestring("asdf").substring(3, 1) == bytestring(""));
    TEST_THROW(results, bytestring("asdf").substring(5) == bytestring(""), featherful::range_exception);
    TEST_THROW(results, bytestring("asdf").substring(-5) == bytestring(""), featherful::range_exception);
    TEST_THROW(results, bytestring("asdf").substring(0, 15) == bytestring(""), featherful::range_exception);
    TEST_THROW(results, bytestring("asdf").substring(0, -15) == bytestring(""), featherful::range_exception);

    TEST(results, bytestring("asdf").concat("ghjk") == bytestring("asdfghjk"));
    TEST(results, bytestring("asdf").concat("ghjk").substring(2,5) == bytestring("dfgh"));

    TEST(results, bytestring("hello world").strip('l') == bytestring("heo word"));
    TEST(results, bytestring("hello world").strip("leo") == bytestring("h wrd"));
    TEST(results, bytestring("\thello world\r\n").strip_whitespace() == bytestring("helloworld"));

    TEST(results, bytestring("hello world\r\n").trim() == bytestring("hello world"));
    TEST(results, bytestring("\t\thello world\r\n").trim() == bytestring("hello world"));
    TEST(results, bytestring("\t\t  \r\n").trim() == bytestring(""));
    TEST(results, bytestring("b\t\t  \r\na").trim() == bytestring("b\t\t  \r\na"));


    TEST(results, bytestring("asdf").leftpad('-', 8) == bytestring("----asdf"));
    TEST(results, bytestring("asdf").rightpad('-', 8) == bytestring("asdf----"));
    TEST(results, bytestring("asdf").leftpad("123", 8) == bytestring("1231asdf"));
    TEST(results, bytestring("asdf").rightpad("123", 8) == bytestring("asdf1231"));
    TEST(results, bytestring("asdf").leftpad('-', 3) == bytestring("asdf"));
    TEST(results, bytestring("asdf").rightpad('-', 3) == bytestring("asdf"));

    results.finish();
    return results.is_successful();
}




bool test_bytestring_insert()
{
    test_results results("bytestring insertion tests");

    TEST(results, bytestring("asdf").insert("qwer") == bytestring("asdfqwer"));
    TEST(results, bytestring("asdf").insert("qwer", 2) == bytestring("asqwerdf"));
    TEST(results, bytestring("asdf").insert("qwer", 0) == bytestring("qwerasdf"));
    TEST(results, bytestring("asdf").insert("qwer", -2) == bytestring("asdqwerf"));
    TEST_THROW(results, bytestring("asdf").insert("qwer", 15) == bytestring(""), featherful::range_exception);
    TEST_THROW(results, bytestring("asdf").insert("qwer", -15) == bytestring(""), featherful::range_exception);

    TEST(results, bytestring("asdf").erase(0, 1) == bytestring("df"));
    TEST(results, bytestring("asdf").erase(1, 2) == bytestring("af"));
    TEST(results, bytestring("asdf").erase(3) == bytestring("asd"));
    TEST(results, bytestring("asdf").erase(-2) == bytestring("as"));
    TEST_THROW(results, bytestring("asdf").erase(-15) == bytestring(""), featherful::range_exception);
    TEST_THROW(results, bytestring("asdf").erase(15) == bytestring(""), featherful::range_exception);
    TEST_THROW(results, bytestring("asdf").erase(0, -5) == bytestring(""), featherful::range_exception);
    TEST_THROW(results, bytestring("asdf").erase(0, 5) == bytestring(""), featherful::range_exception);

    TEST(results, bytestring("hello hello therello").remove("el") == bytestring("hlo hlo therlo"));
    TEST(results, bytestring("hello hello therello").remove("hell") == bytestring("o o therello"));
    TEST(results, bytestring("hello hello therello").remove("llo ") == bytestring("hehetherello"));
    TEST_THROW(results, bytestring("asdf").remove("") == bytestring(""), featherful::invalid_exception);

    TEST(results, bytestring("hello hello therello").replace("hello", "goodbye") == bytestring("goodbye goodbye therello"));
    TEST(results, bytestring("hello hello therello").replace("ello", "") == bytestring("h h ther"));
    TEST_THROW(results, bytestring("asdf").replace("", "asdf") == bytestring(""), featherful::invalid_exception);

    TEST(results, bytestring("hello world!").splice("goodbye", 0, 4) == bytestring("goodbye world!"));
    TEST(results, bytestring("hello world!").splice("olleh", -6, -2) == bytestring("hello olleh!"));
    TEST(results, bytestring("hello world!").splice("everyone", 6) == bytestring("hello everyone"));
    TEST_THROW(results, bytestring("asdf").splice("asdf", 5) == bytestring(""), featherful::range_exception);
    TEST_THROW(results, bytestring("asdf").splice("asdf", 0, 5) == bytestring(""), featherful::range_exception);
    TEST_THROW(results, bytestring("asdf").splice("asdf", 0, -5) == bytestring(""), featherful::range_exception);
    TEST_THROW(results, bytestring("asdf").splice("asdf", -5, 1) == bytestring(""), featherful::range_exception);

    results.finish();
    return results.is_successful();
}



bool test_bytestring_search()
{
    test_results results("bytestring searching tests");

    TEST(results, bytestring("as") * 3 == bytestring("asasas"));
    TEST(results, bytestring("as") * 8 == bytestring("asasasasasasasas"));
    TEST(results, bytestring("qwer") * 1 == bytestring("qwer"));
    TEST(results, bytestring("qwer") * 0 == bytestring(""));

    list<bytestring> strings = bytestring("123456") / 3;

    TEST(results, strings.length() == 3);
    TEST(results, strings[0] == bytestring("12"));
    TEST(results, strings[1] == bytestring("34"));
    TEST(results, strings[2] == bytestring("56"));

    TEST(results, bytestring("-").join(bytestring("123456") / 3) == bytestring("12-34-56"));

    TEST(results, bytestring("foo bar").find('o') == 1);
    TEST(results, bytestring("foo bar").find('o', 2) == 2);
    TEST(results, bytestring("foo bar").find('o', 3) == -1);
    TEST(results, bytestring("foo bar").find("foo") == 0);
    TEST(results, bytestring("foo bar").find("bar") == 4);
    TEST(results, bytestring("foo bar").find("baz") == -1);
    TEST(results, bytestring("foo bar baz").find("ba") == 4);
    TEST(results, bytestring("foo bar baz").find("ba", 5) == 8);
    TEST(results, bytestring("foo bar baz").find("ba", 9) == -1);
    TEST(results, bytestring("foo bar baz").find("az", -2) == 9);
    TEST(results, bytestring("foo bar baz").find("ar", -2) == -1);
    TEST(results, bytestring("asdf").find("asdf", 5) == -1);
    TEST_THROW(results, bytestring("asdf").find("asdf", -5) == -1, featherful::range_exception);

    strings = bytestring("foo bar baz").split(' ');
    TEST(results, strings.length() == 3);
    TEST(results, strings[0] == bytestring("foo"));
    TEST(results, strings[1] == bytestring("bar"));
    TEST(results, strings[2] == bytestring("baz"));

    strings = bytestring("foo bar baz").split("ba");
    TEST(results, strings.length() == 3);
    TEST(results, strings[0] == bytestring("foo "));
    TEST(results, strings[1] == bytestring("r "));
    TEST(results, strings[2] == bytestring("z"));

    TEST(results, bytestring("foo bar baz").contains("foo") == true);
    TEST(results, bytestring("foo bar baz").contains("foo bar") == true);
    TEST(results, bytestring("foo bar baz").contains("foo bravo") == false);
    TEST(results, bytestring("foo bar baz").contains("baz") == true);
    TEST(results, bytestring("foo bar baz").contains("bazz") == false);
    TEST(results, bytestring("foo bar baz").contains("foo bar bazz") == false);


    TEST(results, bytestring("asdf").compare("as") == -1);
    TEST(results, bytestring("asdf").compare("as") == -1);
    TEST(results, bytestring("asdf").compare("asz") == -1);
    TEST(results, bytestring("asdf").compare("asa") == 1);
    TEST(results, bytestring("asdf").compare("dddd") == -1);
    TEST(results, bytestring("asdf").compare("asdf") == 0);


    TEST(results, bytestring("asdf").empty() == false);
    TEST(results, bytestring("").empty() == true);
    TEST(results, (bytestring("") + "qwerty").empty() == false);


    TEST(results, bytestring("asdf$qwerty$zxcv").before('$') == bytestring("asdf"));
    TEST(results, bytestring("asdf$qwerty$zxcv").before('$', 6) == bytestring("asdf$qwerty"));
    TEST(results, bytestring("asdf$qwerty$zxcv").after('$') == bytestring("qwerty$zxcv"));
    TEST(results, bytestring("asdf$qwerty$zxcv").after('$', 6) == bytestring("zxcv"));

    TEST(results, bytestring("asdf$1$qwerty$2$zxcv").before("$1$") == bytestring("asdf"));
    TEST(results, bytestring("asdf$1$qwerty$2$zxcv").after("$2$") == bytestring("zxcv"));

    TEST(results, bytestring("asdf$1$qwerty$2$zxcv").before("$1$", 6) == bytestring("asdf$1$qwerty$2$zxcv"));
    TEST(results, bytestring("asdf$1$qwerty$2$zxcv").after("$2$", 17) == bytestring("asdf$1$qwerty$2$zxcv"));

    results.finish();
    return results.is_successful();
}




bool test_bytestring_to_string()
{
    test_results results("bytestring to_string tests");

    TEST(results, to_string(bytestring("as")) == bytestring("as"));
    TEST(results, to_string(15) == bytestring("15"));
    TEST(results, to_string(12348765) == bytestring("12348765"));
    TEST(results, to_string(-543) == bytestring("-543"));
    TEST(results, to_string((unsigned int)-15) == bytestring("4294967281"));
    TEST(results, to_string((unsigned short)-5) == bytestring("65531"));

    list<bytestring> vals;
    TEST(results, to_string(vals) == bytestring("[]"));
    vals.push("asdf");
    TEST(results, to_string(vals) == bytestring("[asdf]"));
    vals.push("qwerty");
    TEST(results, to_string(vals) == bytestring("[asdf, qwerty]"));
    vals.unshift("zxcv");
    TEST(results, to_string(vals) == bytestring("[zxcv, asdf, qwerty]"));

    list<int> vals2;
    TEST(results, to_string(vals2) == bytestring("[]"));
    vals2.push(15);
    TEST(results, to_string(vals2) == bytestring("[15]"));
    vals2.push(-1337);
    TEST(results, to_string(vals2) == bytestring("[15, -1337]"));
    vals2.unshift(65536);
    TEST(results, to_string(vals2) == bytestring("[65536, 15, -1337]"));

    results.finish();
    return results.is_successful();
}






