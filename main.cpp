

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

    tuple<bytestring, bytestring> asdf("asdf", "qwerty");

    list<bytestring> vals = asdf;

    cout << "length: " << vals.length() << endl;
    cout << "first: " << vals[0] << endl;
    cout << "second: " << vals[1] << endl;
//    cout << "first: " << asdf.first().c_str() << endl;
//    cout << "second: " << asdf.second().c_str() << endl;

//    all_featherful_tests();

    unsigned short val = 15;
    val -= 21;
    cout << "to_string: " << featherful::to_string(val) << endl;
    cout << "to_string: " << featherful::to_string(vals) << endl;

    return 0;
}



