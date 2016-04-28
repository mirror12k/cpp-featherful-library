
#pragma once

#include <iostream>
#include "list.hpp"
#include "tuple.hpp"
//#include "to_string.hpp"

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

    bytestring insert(const bytestring& other, int offset=-1) const;
    bytestring erase(int start, int end=-1) const;
    bytestring remove(const bytestring& needle) const;
    bytestring replace(const bytestring& needle, const bytestring& replacement) const;
    bytestring replace_once(const bytestring& needle, const bytestring& replacement) const;
    bytestring splice(const bytestring& segment, int start, int end=-1) const;

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


    int parse_int() const;
    uint parse_uint() const;
    bytestring to_hex() const;


    friend std::ostream& operator<<(std::ostream& output, const bytestring& str);

private:
    int i_length;
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
    bytestring result = *this;
    result = result.replace_once("%", to_string(v1));
    result = result.replace_once("%", to_string(v2));
    result = result.replace_once("%", to_string(v3));
    result = result.replace_once("%", to_string(v4));
    return result;
}

template <typename T1, typename T2, typename T3>
bytestring bytestring::format(const T1& v1, const T2& v2, const T3& v3) const
{
    bytestring result = *this;
    result = result.replace_once("%", to_string(v1));
    result = result.replace_once("%", to_string(v2));
    result = result.replace_once("%", to_string(v3));
    return result;
}

template <typename T1, typename T2>
bytestring bytestring::format(const T1& v1, const T2& v2) const
{
    bytestring result = *this;
    result = result.replace_once("%", to_string(v1));
    result = result.replace_once("%", to_string(v2));
    return result;
}

template <typename T1>
bytestring bytestring::format(const T1& v1) const
{
    bytestring result = *this;
    result = result.replace_once("%", to_string(v1));
    return result;
}





}
