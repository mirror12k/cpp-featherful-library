

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

    cout << "[1]: " << bytestring("hello world!")[1] << endl;
    cout << "[1]: " << bytestring("hello world!")[11] << endl;
    cout << (bytestring("hello") + bytestring(" ") + bytestring("world!")).c_str() << endl;

    cout << "is 'asdf' empty? " << bytestring("asdf").empty() << endl;
    cout << "is '' empty? " << bytestring("").empty() << endl;
    cout << "is '' empty? " << bytestring().empty() << endl;


    cout << "'hello world!' vs 'asdf': " << bytestring("hello world!").compare(bytestring("asdf")) << endl;
    cout << "'hello world!' vs 'hell': " << bytestring("hello world!").compare(bytestring("hell")) << endl;
    cout << "'hello world!' vs 'hetl': " << bytestring("hello world!").compare(bytestring("hetl")) << endl;
    cout << "'hello world!' vs 'world': " << bytestring("hello world!").compare(bytestring("world")) << endl;
    cout << "'hello world!' vs '': " << bytestring("hello world!").compare(bytestring("")) << endl;
    cout << "'hello world!' vs 'hello world!': " << bytestring("hello world!").compare(bytestring("hello world!")) << endl;
    cout << "'hello world!' vs 'hello world!asdf': " << bytestring("hello world!").compare(bytestring("hello world!asdf")) << endl;

    cout << "'hello world!' == 'hello world!': " << (bytestring("hello world!") == bytestring("hello world!")) << endl;
    cout << "'hello world!' == 'asdf!': " << (bytestring("hello world!") == bytestring("asdf!")) << endl;
//    str = str.concat(other);
//    cout << "my bytestring: " << str.c_str() << endl;

    return 0;
}



