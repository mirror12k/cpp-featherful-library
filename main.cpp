

#include <iostream>

using std::cout;
using std::endl;

#include "featherful.hpp"

using featherful::bytestring;

int main (int argc, char** argv)
{
    cout << "hello world" << endl;

    bytestring str("test");
    bytestring other("asdf");

    str = str.concat(other);
    cout << "my bytestring: [" << str.length() << "]: " << str.c_str() << endl;

    str = bytestring("hello world!").substring(6);
    cout << "my bytestring: [" << str.length() << "]: " << str.c_str() << endl;

    str = bytestring("hello world!").substring(6, -2);
    cout << "my bytestring: [" << str.length() << "]: " << str.c_str() << endl;

    str = bytestring("hello world!").substring(1,4);
    cout << "my bytestring: [" << str.length() << "]: " << str.c_str() << endl;

    str = bytestring("hello world!").substring(1,7);
    cout << "my bytestring: [" << str.length() << "]: " << str.c_str() << endl;

    str = bytestring("hello world!").substring(0, -2);
    cout << "my bytestring [" << str.length() << "]: " << str.c_str() << endl;
    str = bytestring("hello world!").substring(-6, -2);
    cout << "my bytestring [" << str.length() << "]: " << str.c_str() << endl;

//    str = str.concat(other);
//    cout << "my bytestring: " << str.c_str() << endl;

    return 0;
}



