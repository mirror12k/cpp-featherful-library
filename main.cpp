

#include <iostream>

using std::cout;
using std::endl;

#define ENABLE_DEBUG
#include "featherful/featherful.hpp"

using featherful::bytestring;
using featherful::list;
using featherful::tuple;

#include "featherful_tests/test_all.hpp"

//#include "featherful/to_string.hpp"


int main (int argc, char** argv)
{
    cout << "hello world" << endl;
//
//    tuple<bytestring, bytestring> asdf("asdf", "qwerty");
//
//    list<bytestring> vals = asdf;
//
//    cout << "length: " << vals.length() << endl;
//    cout << "first: " << vals[0] << endl;
//    cout << "second: " << vals[1] << endl;
////    cout << "first: " << asdf.first().c_str() << endl;
////    cout << "second: " << asdf.second().c_str() << endl;
//
//    all_featherful_tests();
//
//    unsigned short val = 15;
//    val -= 21;
//    cout << "to_string: " << featherful::to_string(val) << endl;
//    cout << "to_string: " << featherful::to_string(vals) << endl;

//    cout << bytestring("-15").parse_int() << endl;
//    cout << bytestring("1337").parse_int() << endl;
//    cout << bytestring("007").parse_int() << endl;
//    cout << bytestring("0").parse_int() << endl;
//    cout << bytestring("-13asdf").parse_int() << endl;
//    cout << bytestring("3000000000").parse_int() << endl;
//    cout << bytestring("3000000000").parse_uint() << endl;
//    cout << bytestring("-73").parse_uint() << endl;
//
//
//    cout << bytestring("asdf ASDF").to_hex() << endl;
//    cout << bytestring("1337").to_hex() << endl;
//
//
//    cout << bytestring("41424344").from_hex() << endl;
//    cout << bytestring("31203220334sdf").from_hex() << endl;
//
//    unsigned int val = -16666;
//    cout << bytestring("hello %%!").format(val) << endl;
//    cout << bytestring("hello %%, you have %% %%!").format(val, 15, bytestring("dollars")) << endl;
//    cout << bytestring("hello %%, you have %% %%: %%").format(val, 15, bytestring("dollars"), bytestring("asdf+qwerty+123456") / "+") << endl;
//    cout << bytestring("%% %%! %% + %%")
//        .format(tuple<bytestring, bytestring, int, list<bytestring>>(bytestring("hello"), bytestring("world"), -1337, bytestring("123456") / 3)) << endl;
//
//
//    cout << bytestring("paSSwoRD1234 !@#$%^&*()").to_lowercase() << endl;
//    cout << bytestring("paSSwoRD1234 !@#$%^&*()").to_uppercase() << endl;
//
//    cout << bytestring("asdf%%qwerty").before("%%") << endl;
//    cout << bytestring("asdf%%qwerty").before("%%", 6) << endl;
//    cout << bytestring("asdf%%qwerty").after("%%") << endl;
//    cout << bytestring("asdf%%qwerty").after("%%", 6) << endl;
//
//    cout << "before empty: " << bytestring("%%qwerty").before("%%") << endl;
//    cout << "after empty: " << bytestring("asdf%%").after("%%") << endl;
//
//
//    cout << bytestring("asdf").leftpad('-', 8) << endl;
//    cout << bytestring("asdf").leftpad('-', 3) << endl;
//    cout << bytestring("asdf").leftpad("123", 8) << endl;
//    cout << bytestring("asdf").leftpad("123", 3) << endl;
//
//    cout << bytestring("asdf").rightpad('-', 8) << endl;
//    cout << bytestring("asdf").rightpad('-', 3) << endl;
//    cout << bytestring("asdf").rightpad("123", 8) << endl;
//    cout << bytestring("asdf").rightpad("123", 3) << endl;
//
//
//
//    cout << bytestring("hello %%!").format(bytestring("world")) << endl;
//    cout << bytestring("lol %04% there").format(15) << endl;
//    cout << bytestring("%_8% |").format(bytestring("world")) << endl;
//    cout << bytestring("%_8>% |").format(bytestring("world")) << endl;
//
//    cout << bytestring("FOXTROT%%ECHO%%ALPHA").format(bytestring("hello"), bytestring("world")) << endl;
//    cout << bytestring("%03%:%_6%").format(15, -500) << endl;


//    list<bytestring> mylist;
//
//    mylist.push(bytestring("asdf"));
//
//    cout << featherful::to_string(mylist) << endl;


//    cout << bytestring("asdf%qwerty%zxcv").before('%') << endl;
//    cout << bytestring("asdf%qwerty%zxcv").before('%', 5) << endl;
    cout << bytestring("asdf qwerty zxcv").match("asdf%6%zxcv") << endl;
    cout << bytestring("asdf qwerty zxcv").match("asdf%15%zxcv") << endl;
    cout << bytestring("asdf qwerty zxcv").match("asdf%%zxcx") << endl;
    cout << bytestring("arg: 15").match("arg: %2%") << endl;


    cout << to_string(bytestring("asdf qwerty zxcv").extract("a%%f %% %%cv")) << endl;
    cout << to_string(bytestring("alpha").extract("lp%%")) << endl;
    cout << to_string(bytestring("arg:0015").extract("%3%:%4%")) << endl;
    cout << to_string(bytestring("arg:0015").extract("%%:%%")) << endl;
    cout << to_string(bytestring("arg:0015:username/password").extract("%%:%%:%%/%%")) << endl;
    cout << bytestring("arg:0015:username/password").match("%%:%%:%%/%%") << endl;
    cout << bytestring("arg:0015:username/password").match("%%:%%:%%:%%") << endl;
    cout << bytestring("arg:0015:username/password").match("%%:%%:%%") << endl;
    cout << bytestring("arg:0015:username/password").match("%%/%%:%%") << endl;
    cout << bytestring("arg:0015:username/password").match("%%:%%/%%") << endl;
    cout << bytestring("arg:0015:username/password").match("arg:%%:") << endl;
//    cout << to_string(bytestring("arg: 15").extract("a%2%: %2%")) << endl;
//    all_featherful_tests();

    list<bytestring> strings;
    strings.push("asdf");
    strings.push("qwerty");
    strings.push("zxcv");
    cout << to_string(bytestring("asdf qwerty zxcv").split(' ')) << endl;
    cout << (strings == bytestring("asdf qwerty zxcv").split(' ')) << endl;
    cout << (strings == bytestring("asdf qwerty zcv").split(' ')) << endl;
    cout << (strings == bytestring("asdf qwerty zxcv qwerty").split(' ')) << endl;
    strings.push("qwerty");
    cout << (strings == bytestring("asdf qwerty zxcv qwerty").split(' ')) << endl;

    cout << bytestring("asdf qwerty zxcv qwerty").split(' ').find("asdf") << endl;
    cout << bytestring("asdf qwerty zxcv qwerty").split(' ').find("qwerty") << endl;
    cout << bytestring("asdf qwerty zxcv qwerty").split(' ').find("qwerty", 2) << endl;
    cout << bytestring("asdf qwerty zxcv qwerty").split(' ').find("qwerty", -4) << endl;
    cout << bytestring("asdf qwerty zxcv qwerty").split(' ').find("qwerty", -2) << endl;
    cout << bytestring("asdf qwerty zxcv qwerty").split(' ').find("qwerty", 4) << endl;
    cout << bytestring("asdf qwerty zxcv qwerty").split(' ').find("zxcv") << endl;
    cout << bytestring("asdf qwerty zxcv qwerty").split(' ').find("magic") << endl;
    cout << bytestring("asdf qwerty zxcv qwerty").split(' ').find("asdf+") << endl;


    return 0;
}



