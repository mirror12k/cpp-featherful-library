

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

    cout << "find char:" << endl;
    cout << bytestring("hello world!").find('l') << endl;
    cout << bytestring("hello world!").find('l', 3) << endl;
    cout << bytestring("hello world!").find('l', 4) << endl;
    cout << bytestring("hello world!").find('a') << endl;

    cout << "find bytestring:" << endl;
    cout << bytestring("hello world!").find(bytestring("hello")) << endl;
    cout << bytestring("hello world!").find(bytestring("world")) << endl;
    cout << bytestring("hello world!").find(bytestring("o w")) << endl;
    cout << bytestring("hello world!").find(bytestring("o w"), 10) << endl;
    cout << bytestring("hello world!").find(bytestring("!")) << endl;
    cout << bytestring("hello world!").find(bytestring("! asdf")) << endl;

    cout << bytestring("hello world!").strip('l').c_str() << endl;
    cout << bytestring("hello world!").strip(bytestring("ello")).c_str() << endl;
    cout << bytestring("hello world!").strip(bytestring("word!")).c_str() << endl;
    cout << bytestring("hello world!").strip_whitespace().c_str() << endl;

//    str = str.concat(other);
//    cout << "my bytestring: " << str.c_str() << endl;

    return 0;
}



