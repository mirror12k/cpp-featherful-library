

#include <iostream>

using std::cout;
using std::endl;

#define ENABLE_DEBUG
#include "featherful.hpp"

using featherful::bytestring;
using featherful::list;

#include "featherful_tests/test_all.hpp"
//#include "featherful_tests/test_list.hpp"
//#include "featherful_tests/test_bytestring.hpp"
//#include "featherful_tests/test_assert.hpp"


class string_mapper : public featherful::list_mapper<bytestring, bytestring>
{
public:
    bytestring* map(const bytestring& s) const
    { return new bytestring(s + bytestring(" lol hijack")); }
};

class string_length_mapper : public featherful::list_mapper<bytestring, int>
{
public:
    int* map(const bytestring& s) const
    { return new int(s.length()); }
};

class string_length_filterer : public featherful::list_filterer<bytestring>
{
public:
    string_length_filterer(uint length) : i_length(length) {}
    bool filter(const bytestring& s) const
    { return s.length() > this->i_length; }
    const uint i_length;
};

bytestring* hijacker_function(const bytestring& s)
{
    return new bytestring(bytestring("hijacked ") + s);
}

int* bytestring_length(const bytestring& s)
{
    return new int(s.length());
}

bool is_longer_than_5(const bytestring& s)
{
    return s.length() >= 5;
}

int sum(const int& a, const int& b)
{
    return a + b;
}

int main (int argc, char** argv)
{
    cout << "hello world" << endl;

    all_featherful_tests();
//    test_list();
//    test_bytestring();
//    test_assert();


    return 0;
}



