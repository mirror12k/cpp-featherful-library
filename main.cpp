

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
////    all_featherful_tests();
//
//    unsigned short val = 15;
//    val -= 21;
//    cout << "to_string: " << featherful::to_string(val) << endl;
//    cout << "to_string: " << featherful::to_string(vals) << endl;

    cout << bytestring("-15").parse_int() << endl;
    cout << bytestring("1337").parse_int() << endl;
    cout << bytestring("007").parse_int() << endl;
    cout << bytestring("0").parse_int() << endl;
    cout << bytestring("-13asdf").parse_int() << endl;
    cout << bytestring("3000000000").parse_int() << endl;
    cout << bytestring("3000000000").parse_uint() << endl;
    cout << bytestring("-73").parse_uint() << endl;

    unsigned int val = -16666;
    cout << bytestring("hello %!").format(val) << endl;
    cout << bytestring("hello %, you have % %!").format(val, 15, bytestring("dollars")) << endl;
    cout << bytestring("hello %, you have % %: %").format(val, 15, bytestring("dollars"), bytestring("asdf+qwerty+123456") / "+") << endl;
//    cout << bytestring("hello %!").format(tuple<bytestring>(bytestring("test"))) << endl;
    cout << bytestring("% %! % + %")
        .format(tuple<bytestring, bytestring, int, list<bytestring>>(bytestring("hello"), bytestring("world"), -1337, bytestring("123456") / 3)) << endl;

    return 0;
}



