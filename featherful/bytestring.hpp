
#pragma once

#include <iostream>
#include "list.hpp"
#include "tuple.hpp"
//#include "to_string.hpp"

#define ENABLE_DEBUG
#include "debug.hpp"

namespace featherful
{





class bytestring
{
public:
    bytestring();
    bytestring(char c);
    bytestring(const char* s);
    bytestring(uint length, const char* s);
    bytestring(uint string_count, uint* length, const char** s);

    bytestring(const bytestring& other);
    bytestring& operator=(const bytestring& other);

    ~bytestring();



    uint length() const;
    const char* buffer() const;
    char* c_str() const;

    char operator[](int index) const;
    bytestring operator+(const bytestring& appended) const;
    bytestring operator-(const bytestring& removed) const;
    bytestring operator*(uint times) const;
    list<bytestring> operator/(uint times) const;
    list<bytestring> operator/(const bytestring& delimiter) const;
    bool operator==(const bytestring& other) const;
    bool operator!=(const bytestring& other) const;
    bool operator<(const bytestring& other) const;
    bool operator<=(const bytestring& other) const;


    typedef const char* const_iterator;

    const_iterator begin() const;
    const_iterator end() const;

    bytestring concat(const bytestring& other) const;
    bytestring concat(const list<bytestring>& strings) const;
    bytestring substring(int start, int end=-1) const;
    bytestring strip(char c) const;
    bytestring strip(const bytestring& chars) const;
    bytestring strip_whitespace() const;
    bytestring trim() const;

    bytestring leftpad(char c, uint length) const;
    bytestring leftpad(const bytestring& pad, uint length) const;
    bytestring rightpad(char c, uint length) const;
    bytestring rightpad(const bytestring& pad, uint length) const;

    bytestring insert(const bytestring& other, int offset=-1) const;
    bytestring erase(int start, int end=-1) const;
    bytestring remove(const bytestring& needle) const;
    bytestring replace(const bytestring& needle, const bytestring& replacement) const;
    bytestring replace_once(const bytestring& needle, const bytestring& replacement) const;
    bytestring splice(const bytestring& segment, int start, int end=-1) const;

    bytestring before(char c, int offset=0) const;
    bytestring before(const bytestring& c, int offset=0) const;
    bytestring after(char c, int offset=0) const;
    bytestring after(const bytestring& c, int offset=0) const;


    bytestring multiply(uint times) const;
    list<bytestring> divide(uint times) const;

    list<bytestring> split(char c) const;
    list<bytestring> split(const bytestring& delimiter) const;
    bytestring join(const list<bytestring>& strings) const;

    char char_at(int index) const;
    bool contains(char c, int offset=0) const;
    bool contains(const bytestring& needle, int offset=0) const;
    int find(char c, int offset=0) const;
    int find(const bytestring& needle, int offset=0) const;

    bool equal(const bytestring& other) const;
    int compare(const bytestring& other) const;

    bool empty() const;


    template <typename T1, typename T2, typename T3, typename T4>
    bytestring format(const tuple<T1, T2, T3, T4>& items) const;
    template <typename T1, typename T2, typename T3>
    bytestring format(const tuple<T1, T2, T3>& items) const;
    template <typename T1, typename T2>
    bytestring format(const tuple<T1, T2>& items) const;
    template <typename T1>
    bytestring format(const tuple<T1>& items) const;


    template <typename T1, typename T2, typename T3, typename T4>
    bytestring format(const T1& v1, const T2& v2, const T3& v3, const T4& v4) const;
    template <typename T1, typename T2, typename T3>
    bytestring format(const T1& v1, const T2& v2, const T3& v3) const;
    template <typename T1, typename T2>
    bytestring format(const T1& v1, const T2& v2) const;
    template <typename T1>
    bytestring format(const T1& v1) const;


    bytestring to_lowercase() const;
    bytestring to_uppercase() const;

    int parse_int() const;
    uint parse_uint() const;
    bytestring to_hex() const;
    bytestring from_hex() const;


    friend std::ostream& operator<<(std::ostream& output, const bytestring& str);

private:
    uint i_length;
    const char* a_buffer;
};






// pre-declare these functions instead of including to_string because to_string requires bytestring
template<typename T>
bytestring to_string(const T& item);
template<typename T>
bytestring to_string(const list<T>& item);





template <typename T1, typename T2, typename T3, typename T4>
bytestring bytestring::format(const tuple<T1, T2, T3, T4>& items) const
{
    bytestring result = this->replace_once("%", to_string(items.arg0()));
    result = result.replace_once("%", to_string(items.arg1()));
    result = result.replace_once("%", to_string(items.arg2()));
    result = result.replace_once("%", to_string(items.arg3()));
    return result;
}

template <typename T1, typename T2, typename T3>
bytestring bytestring::format(const tuple<T1, T2, T3>& items) const
{
    bytestring result = this->replace_once("%", to_string(items.arg0()));
    result = result.replace_once("%", to_string(items.arg1()));
    result = result.replace_once("%", to_string(items.arg2()));
    return result;
}

template <typename T1, typename T2>
bytestring bytestring::format(const tuple<T1, T2>& items) const
{
    bytestring result = this->replace_once("%", to_string(items.arg0()));
    result = result.replace_once("%", to_string(items.arg1()));
    return result;
}

template <typename T1>
bytestring bytestring::format(const tuple<T1>& items) const
{
    bytestring result = this->replace_once("%", to_string(items.arg0()));
    return result;
}




template <typename T1, typename T2, typename T3, typename T4>
bytestring bytestring::format(const T1& v1, const T2& v2, const T3& v3, const T4& v4) const
{
    bytestring result = this->before('%');
    bytestring temp = this->after('%');

    bytestring val = to_string(v1);
    bytestring arg = temp.before('%');
    temp = temp.after('%');
    if (arg.length() > 1)
        if (arg[-1] == '>')
            val = val.rightpad(arg[0], arg.substring(1).parse_uint());
        else
            val = val.leftpad(arg[0], arg.substring(1).parse_uint());
    else if (arg.length() > 0)
        throw invalid_exception("invalid format argument");

    result = result + val + temp.before('%');
    temp = temp.after('%');

    val = to_string(v2);
    arg = temp.before('%');
    temp = temp.after('%');
    if (arg.length() > 1)
        if (arg[-1] == '>')
            val = val.rightpad(arg[0], arg.substring(1).parse_uint());
        else
            val = val.leftpad(arg[0], arg.substring(1).parse_uint());
    else if (arg.length() > 0)
        throw invalid_exception("invalid format argument");

    result = result + val + temp.before('%');
    temp = temp.after('%');

    val = to_string(v3);
    arg = temp.before('%');
    temp = temp.after('%');
    if (arg.length() > 1)
        if (arg[-1] == '>')
            val = val.rightpad(arg[0], arg.substring(1).parse_uint());
        else
            val = val.leftpad(arg[0], arg.substring(1).parse_uint());
    else if (arg.length() > 0)
        throw invalid_exception("invalid format argument");

    result = result + val + temp.before('%');
    temp = temp.after('%');

    val = to_string(v4);
    arg = temp.before('%');
    temp = temp.after('%');
    if (arg.length() > 1)
        if (arg[-1] == '>')
            val = val.rightpad(arg[0], arg.substring(1).parse_uint());
        else
            val = val.leftpad(arg[0], arg.substring(1).parse_uint());
    else if (arg.length() > 0)
        throw invalid_exception("invalid format argument");

    result = result + val + temp;

    return result;
}

template <typename T1, typename T2, typename T3>
bytestring bytestring::format(const T1& v1, const T2& v2, const T3& v3) const
{
    bytestring result = this->before('%');
    bytestring temp = this->after('%');

    bytestring val = to_string(v1);
    bytestring arg = temp.before('%');
    temp = temp.after('%');
    if (arg.length() > 1)
        if (arg[-1] == '>')
            val = val.rightpad(arg[0], arg.substring(1).parse_uint());
        else
            val = val.leftpad(arg[0], arg.substring(1).parse_uint());
    else if (arg.length() > 0)
        throw invalid_exception("invalid format argument");

    result = result + val + temp.before('%');
    temp = temp.after('%');

    val = to_string(v2);
    arg = temp.before('%');
    temp = temp.after('%');
    if (arg.length() > 1)
        if (arg[-1] == '>')
            val = val.rightpad(arg[0], arg.substring(1).parse_uint());
        else
            val = val.leftpad(arg[0], arg.substring(1).parse_uint());
    else if (arg.length() > 0)
        throw invalid_exception("invalid format argument");

    result = result + val + temp.before('%');
    temp = temp.after('%');

    val = to_string(v3);
    arg = temp.before('%');
    temp = temp.after('%');
    if (arg.length() > 1)
        if (arg[-1] == '>')
            val = val.rightpad(arg[0], arg.substring(1).parse_uint());
        else
            val = val.leftpad(arg[0], arg.substring(1).parse_uint());
    else if (arg.length() > 0)
        throw invalid_exception("invalid format argument");

    result = result + val + temp;

    return result;
}

template <typename T1, typename T2>
bytestring bytestring::format(const T1& v1, const T2& v2) const
{
    bytestring result = this->before('%');
    bytestring temp = this->after('%');

    bytestring val = to_string(v1);
    bytestring arg = temp.before('%');
    temp = temp.after('%');
    if (arg.length() > 1)
        if (arg[-1] == '>')
            val = val.rightpad(arg[0], arg.substring(1).parse_uint());
        else
            val = val.leftpad(arg[0], arg.substring(1).parse_uint());
    else if (arg.length() > 0)
        throw invalid_exception("invalid format argument");

    result = result + val + temp.before('%');
    temp = temp.after('%');

    val = to_string(v2);
    arg = temp.before('%');
    temp = temp.after('%');
    if (arg.length() > 1)
        if (arg[-1] == '>')
            val = val.rightpad(arg[0], arg.substring(1).parse_uint());
        else
            val = val.leftpad(arg[0], arg.substring(1).parse_uint());
    else if (arg.length() > 0)
        throw invalid_exception("invalid format argument");

    result = result + val + temp;

    return result;
}

template <typename T1>
bytestring bytestring::format(const T1& v1) const
{
    bytestring result = this->before('%');
    bytestring temp = this->after('%');

    bytestring val = to_string(v1);
    bytestring arg = temp.before('%');
    temp = temp.after('%');
    if (arg.length() > 1)
        if (arg[-1] == '>')
            val = val.rightpad(arg[0], arg.substring(1).parse_uint());
        else
            val = val.leftpad(arg[0], arg.substring(1).parse_uint());
    else if (arg.length() > 0)
        throw invalid_exception("invalid format argument");

    result = result + val + temp;

    return result;
}





}
