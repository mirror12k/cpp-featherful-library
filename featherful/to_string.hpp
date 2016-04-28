
#pragma once

#include "bytestring.hpp"
#include "list.hpp"

namespace featherful
{



template<typename T>
bytestring to_string(const T& item);


template<typename T>
bytestring* to_string_temp(const T& item)
{
    return new bytestring(to_string(item));
}

template<typename T>
bytestring to_string(const list<T>& item)
{
    return bytestring("[") + bytestring(", ").join(item.map(to_string_temp<T>)) + "]";
}



}
