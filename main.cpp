

#include <iostream>

using std::cout;
using std::endl;

#define ENABLE_DEBUG
#include "featherful.hpp"

using featherful::bytestring;
using featherful::list;

#include "featherful_tests/test_all.hpp"

#include "featherful/tuple.hpp"

using featherful::tuple;

int main (int argc, char** argv)
{
    cout << "hello world" << endl;

    tuple<bytestring, bytestring> asdf("asdf", "qwerty");

    list<bytestring> vals = asdf;

    cout << "length: " << vals.length() << endl;
    cout << "first: " << vals[0].c_str() << endl;
    cout << "second: " << vals[1].c_str() << endl;
//    cout << "first: " << asdf.first().c_str() << endl;
//    cout << "second: " << asdf.second().c_str() << endl;

//    all_featherful_tests();

    return 0;
}



