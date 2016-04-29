

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

    all_featherful_tests();


    return 0;
}



