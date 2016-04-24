

#include <iostream>

using std::cout;
using std::endl;

#define ENABLE_DEBUG
#include "featherful.hpp"

using featherful::bytestring;
using featherful::list;


#include "featherful_tests/test_list.hpp"


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

//    bytestring str("test");
//    bytestring other("asdf");
//
//    str = str.concat(other);
//    cout << "my bytestring: [" << str.length() << "]: " << str.c_str() << endl;
//
//    str = bytestring("hello world!").substring(6);
//    cout << "my bytestring: [" << str.length() << "]: " << str.c_str() << endl;
//
//    str = bytestring("hello world!").substring(6, -2);
//    cout << "my bytestring: [" << str.length() << "]: " << str.c_str() << endl;
//
//    str = bytestring("hello world!").substring(1,4);
//    cout << "my bytestring: [" << str.length() << "]: " << str.c_str() << endl;
//
//    str = bytestring("hello world!").substring(1,7);
//    cout << "my bytestring: [" << str.length() << "]: " << str.c_str() << endl;
//
//    str = bytestring("hello world!").substring(0, -2);
//    cout << "my bytestring [" << str.length() << "]: " << str.c_str() << endl;
//    str = bytestring("hello world!").substring(-6, -2);
//    cout << "my bytestring [" << str.length() << "]: " << str.c_str() << endl;
//
//    cout << "find char:" << endl;
//    cout << bytestring("hello world!").find('l') << endl;
//    cout << bytestring("hello world!").find('l', 3) << endl;
//    cout << bytestring("hello world!").find('l', 4) << endl;
//    cout << bytestring("hello world!").find('a') << endl;
//
//    cout << "find bytestring:" << endl;
//    cout << bytestring("hello world!").find(bytestring("hello")) << endl;
//    cout << bytestring("hello world!").find(bytestring("world")) << endl;
//    cout << bytestring("hello world!").find(bytestring("o w")) << endl;
//    cout << bytestring("hello world!").find(bytestring("o w"), 10) << endl;
//    cout << bytestring("hello world!").find(bytestring("!")) << endl;
//    cout << bytestring("hello world!").find(bytestring("! asdf")) << endl;
//
//    cout << bytestring("hello world!").strip('l').c_str() << endl;
//    cout << bytestring("hello world!").strip(bytestring("ello")).c_str() << endl;
//    cout << bytestring("hello world!").strip(bytestring("word!")).c_str() << endl;
//    cout << bytestring("hello world!").strip_whitespace().c_str() << endl;
//
//    cout << "[1]: " << bytestring("hello world!")[1] << endl;
//    cout << "[11]: " << bytestring("hello world!")[11] << endl;
//    cout << (bytestring("hello") + bytestring(" ") + bytestring("world!")).c_str() << endl;
//
//    cout << ".empty()" << endl;
//    cout << "is 'asdf' empty? " << bytestring("asdf").empty() << endl;
//    cout << "is '' empty? " << bytestring("").empty() << endl;
//    cout << "is '' empty? " << bytestring().empty() << endl;
//
//
//    cout << ".compare():" << endl;
//    cout << "'hello world!' vs 'asdf': " << bytestring("hello world!").compare(bytestring("asdf")) << endl;
//    cout << "'hello world!' vs 'hell': " << bytestring("hello world!").compare(bytestring("hell")) << endl;
//    cout << "'hello world!' vs 'hetl': " << bytestring("hello world!").compare(bytestring("hetl")) << endl;
//    cout << "'hello world!' vs 'world': " << bytestring("hello world!").compare(bytestring("world")) << endl;
//    cout << "'hello world!' vs '': " << bytestring("hello world!").compare(bytestring("")) << endl;
//    cout << "'hello world!' vs 'hello world!': " << bytestring("hello world!").compare(bytestring("hello world!")) << endl;
//    cout << "'hello world!' vs 'hello world!asdf': " << bytestring("hello world!").compare(bytestring("hello world!asdf")) << endl;
//
//    cout << "'hello world!' == 'hello world!': " << (bytestring("hello world!") == bytestring("hello world!")) << endl;
//    cout << "'hello world!' == 'asdf!': " << (bytestring("hello world!") == bytestring("asdf!")) << endl;
//
//    cout << ".insert():" << endl;
//    cout << "'hello world!' <+ 'asdf!' @ -1: " << bytestring("hello world!").insert(bytestring("asdf*")).c_str() << endl;
//    cout << "'hello world!' <+ 'welcome ' @ 0: " << bytestring("hello world!").insert(bytestring("welcome "), 0).c_str() << endl;
//    cout << "'hello world!' <+ 'my ' @ 6: " << bytestring("hello world!").insert(bytestring("my "), 6).c_str() << endl;
//    cout << "'hello world!' <+ 'my ' @ -7: " << bytestring("hello world!").insert(bytestring("my "), -7).c_str() << endl;
//    cout << "'hello world!' <+ ' cometh to my ' @ 4: " << bytestring("hello world!").insert(bytestring(" cometh to my "), 4).c_str() << endl;
//
//
//    cout << ".erase():" << endl;
//    cout << "'hello world!' - 5:-2 : " << bytestring("hello world!").erase(5, -2).c_str() << endl;
//    cout << "'hello world!' - 5:-1 : " << bytestring("hello world!").erase(5).c_str() << endl;
//    cout << "'hello world!' - 0:5 : " << bytestring("hello world!").erase(0, 5).c_str() << endl;
//    cout << "'hello world!' - -5:-2 : " << bytestring("hello world!").erase(-5, -2).c_str() << endl;
//
//
//    cout << ".splice():" << endl;
//    cout << "'hello world!' /- 'goodbye' : " << bytestring("hello world!").splice(bytestring("goodbye"), 0, 4).c_str() << endl;
//    cout << "'hello world!' /- 'steve' : " << bytestring("hello world!").splice(bytestring("steve"), 6, -2).c_str() << endl;
//    cout << "'hello world!' /- '?' : " << bytestring("hello world!").splice(bytestring("?"), -1, -1).c_str() << endl;
//    cout << "'hello world!' /- ' welcome' : " << bytestring("hello world!").splice(bytestring(" welcome"), 4).c_str() << endl;
//
//    cout << ".remove():" << endl;
//    cout << "'this is my apple' : " << (bytestring("this is my apple") - bytestring("my ")).c_str() << endl;
//    cout << "'abcbcdebbcc' : " << (bytestring("abcbcdebbcc") - bytestring("bc")).c_str() << endl;
//
//    cout << ".replace():" << endl;
//    cout << "'hi there $name' : " << bytestring("hi there $name").replace(bytestring("$name"), bytestring("steve")).c_str() << endl;
//    cout << "'$a and $a with $a': " << bytestring("$a and $a with $a").replace(bytestring("$a"), bytestring("!_!")).c_str() << endl;
//    cout << "'$a$$a$aa': " << bytestring("$a$$a$aa").replace(bytestring("$a"), bytestring("-_-")).c_str() << endl;
//    cout << "'/../asdf/../../': " << bytestring("/../asdf/../../").replace(bytestring("/.."), bytestring("")).c_str() << endl;
//
//    cout << ".multiply():" << endl;
//    cout << "'_abc_' * 0: " << (bytestring("_abc_") * 0).c_str() << endl;
//    cout << "'_abc_' * 2: " << (bytestring("_abc_") * 2).c_str() << endl;
//    cout << "'_abc_' * 3: " << (bytestring("_abc_") * 3).c_str() << endl;
//    cout << "'_+-' * 9: " << (bytestring("_+-") * 9).c_str() << endl;


    list<bytestring> l;
    l.push(new bytestring("qwerty"));
    l.push(new bytestring("asdf"));
    l.push(new bytestring("qwertyuiop"));
    l.push(new bytestring("hello"));
    l.unshift(new bytestring("world"));

    cout << "popped: " << l.pop().c_str() << endl;

    cout << "shifted: " << l.shift().c_str() << endl;

//    l.map_inplace(string_mapper());
//    list<int> lengths = l.map(string_length_mapper());
//
//    for (list<bytestring>::iterator iter = l.begin(), iter_end = l.end(); iter != iter_end; ++iter)
//        cout << "iter: " << (*iter).c_str() << endl;
//    for (list<int>::iterator iter = lengths.begin(), iter_end = lengths.end(); iter != iter_end; ++iter)
//        cout << "lengths: " << *iter << endl;
//
//    list<bytestring> result;
//    result = list<bytestring>());
//    l.filter(string_length_filterer(5);
    list<bytestring> l2;
    l2.push(new bytestring("new!"));
    l2.push(new bytestring("test!"));
    list<bytestring> l3;
    l3.push(new bytestring("newnewnew!"));
    l3.push(new bytestring("testtesttest!"));
//    list<list<bytestring>> ltop;
//    ltop.push(new list<bytestring>(l2));
//    ltop.push(new list<bytestring>(l3));
//    ltop.push(new list<bytestring>(l2));

    l += l.filter(is_longer_than_5).map(hijacker_function) + l2 + l3;
//    l.concat();

//    list<int> lengths = l.map(bytestring_length);

//    l.concat(l.clone());

//    cout << "at 3: " << l[3].c_str() << endl;

    cout << "length: " << l.length() << endl;
    for (list<bytestring>::iterator iter = l.begin(), iter_end = l.end(); iter != iter_end; iter++)
        cout << "iter: " << (*iter).c_str() << endl;
//    for (list<int>::iterator iter = lengths.begin(), iter_end = lengths.end(); iter != iter_end; iter++)
//        cout << "iter: " << *iter << endl;


    cout << "sum: " << list<bytestring>().map(bytestring_length).reduce(sum, 10) << endl;

    cout << bytestring('-').join(bytestring("||").join(bytestring("asdf qwerty hello").split(' ')).split("||")).c_str() << endl;
    cout << bytestring('-').join(bytestring("123456").divide(3)).c_str() << endl;
    cout << bytestring("words: ").concat(bytestring("welcome to hell") / bytestring('e')).c_str() << endl;

//    cout << "debug: " << bytestring("asdf")[-5] << endl;

//    DEBUG_ASSERT(bytestring("asdf").length() == 5, "test string");
//    DEBUG("hello world! %d\n", 15);


//    featherful::test_results test1("test1");
//    TEST(test1, false);
//    TEST(test1, true);
//    TEST(test1, false);
//    TEST_THROW(test1, bytestring("asdf").find(""), featherful::invalid_exception);
//    test1.finish();

    test_list();


    return 0;
}



