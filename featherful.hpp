
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

    bytestring concat(const bytestring& other) const;

    uint length() const;
    const char* buffer() const;
    char* c_str() const;

private:
    int i_length;
    const char* a_buffer;
};


}
