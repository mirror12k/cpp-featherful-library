
#pragma once


typedef unsigned int uint;

namespace featherful
{


class bytestring
{
public:
    bytestring();
    bytestring(const char* s);
    bytestring(uint length, const char* s);
    bytestring(uint string_count, uint* length, const char** s);

    bytestring(const bytestring& other);
    bytestring& operator=(const bytestring& other);

    ~bytestring();



    uint length() const;
    const char* buffer() const;
    char* c_str() const;

    char operator[](uint index) const;
    bytestring operator+(const bytestring& other) const;


    typedef const char* const_iterator;

    const_iterator begin() const;
    const_iterator end() const;

    bytestring concat(const bytestring& other) const;
    bytestring substring(int start, int end=-1) const;
    bytestring strip(char c) const;
    bytestring strip(const bytestring& chars) const;
    bytestring strip_whitespace() const;

    char char_at(uint index) const;
    bool contains(char c, uint offset=0) const;
    bool contains(const bytestring& needle, uint offset=0) const;
    int find(char c, uint offset=0) const;
    int find(const bytestring& needle, uint offset=0) const;

    bool empty() const;



private:
    int i_length;
    const char* a_buffer;
};


}
