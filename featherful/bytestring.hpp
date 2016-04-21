
#pragma once

typedef unsigned int uint;

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
    bytestring operator+(const bytestring& other) const;
    bytestring operator-(const bytestring& other) const;
    bytestring operator*(uint times) const;
    bool operator==(const bytestring& other) const;


    typedef const char* const_iterator;

    const_iterator begin() const;
    const_iterator end() const;

    bytestring concat(const bytestring& other) const;
    bytestring substring(int start, int end=-1) const;
    bytestring strip(char c) const;
    bytestring strip(const bytestring& chars) const;
    bytestring strip_whitespace() const;

    bytestring insert(const bytestring& other, int offset=-1) const;
    bytestring erase(int start, int end=-1) const;
    bytestring remove(const bytestring& needle) const;
    bytestring replace(const bytestring& needle, const bytestring& replacement) const;
    bytestring splice(const bytestring& segment, int start, int end=-1) const;

    bytestring multiply(uint times) const;
//    list<bytestring> divide(uint times) const;

//    list<bytestring> split(const bytestring& const delimiter) const;
//    bytestring join(const list<bytestring>& strings) const;

    char char_at(int index) const;
    bool contains(char c, uint offset=0) const;
    bool contains(const bytestring& needle, uint offset=0) const;
    int find(char c, uint offset=0) const;
    int find(const bytestring& needle, uint offset=0) const;

    bool equal(const bytestring& other) const;
    int compare(const bytestring& other) const;

    bool empty() const;



private:
    int i_length;
    const char* a_buffer;
};

}