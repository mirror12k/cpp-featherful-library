

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

    tuple<int, int> asdf(15, 35);

    cout << "first: " << asdf.first() << endl;
    cout << "second: " << asdf.second() << endl;

//    all_featherful_tests();

    return 0;
}



