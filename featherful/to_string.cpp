
#include "to_string.hpp"

#include "list.hpp"

namespace featherful
{

template<>
bytestring to_string<int>(const int& item)
{
    int val = item;
    if (item == 0)
        return "0";

    bool negative = false;
    if (val < 0)
    {
        negative = true;
        val = -val;
    }

    int char_count = negative;
    for (int i = val; i > 0; i /= 10)
        char_count++;

    char* buf = new char[char_count];
    *buf = '-'; // testing for negative is absolutely unnecessary, it will be overwritten anyways

    char* writer = buf + char_count;
    for (int i = val; i > 0; i /= 10)
        *--writer = (char)((i % 10) + 0x30);

    bytestring result(char_count, buf);
    delete buf;

    return result;
}

template<>
bytestring to_string<unsigned int>(const unsigned int& item)
{
    unsigned int val = item;
    if (item == 0)
        return "0";

    int char_count = 0;
    for (unsigned int i = val; i > 0; i /= 10)
        char_count++;

    char* buf = new char[char_count];
    char* writer = buf + char_count;
    for (unsigned int i = val; i > 0; i /= 10)
        *--writer = (char)((i % 10) + 0x30);

    bytestring result(char_count, buf);
    delete buf;

    return result;
}

template<>
bytestring to_string<short>(const short& item)
{
    short val = item;
    if (item == 0)
        return "0";

    bool negative = false;
    if (val < 0)
    {
        negative = true;
        val = -val;
    }

    int char_count = negative;
    for (short i = val; i > 0; i /= 10)
        char_count++;

    char* buf = new char[char_count];
    *buf = '-';

    char* writer = buf + char_count;
    for (short i = val; i > 0; i /= 10)
        *--writer = (char)((i % 10) + 0x30);

    bytestring result(char_count, buf);
    delete buf;

    return result;
}

template<>
bytestring to_string<unsigned short>(const unsigned short& item)
{
    unsigned short val = item;
    if (item == 0)
        return "0";

    int char_count = 0;
    for (unsigned short i = val; i > 0; i /= 10)
        char_count++;

    char* buf = new char[char_count];
    char* writer = buf + char_count;
    for (unsigned short i = val; i > 0; i /= 10)
        *--writer = (char)((i % 10) + 0x30);

    bytestring result(char_count, buf);
    delete buf;

    return result;
}

template<>
bytestring to_string<char>(const char& item)
{
    return bytestring(item);
}

template<>
bytestring to_string<char*>(char* const& item)
{
    return bytestring(item);
}



template<>
bytestring to_string<bytestring>(const bytestring& item)
{
    return item;
}



}

