
#pragma once


#include <cstdio>

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


template <class T>
class list
{
public:

    class list_link
    {
    public:
        list_link(list_link* prev, T* item, list_link* next)
        {
            this->p_item = item;
            this->p_prev = prev;
            this->p_next = next;
        }

        T& operator*() const
        {
            return *this->p_item;
        }
        list_link& operator=(const list_link& other)
        {
            this->p_item = other.p_item;
            this->p_prev = other.p_prev;
            this->p_next = other.p_next;
            return *this;
        }
        bool operator!=(const list_link& other) const
        {
            return other.p_item != this->p_item;
        }
        bool operator==(const list_link& other) const
        {
            return other.p_item == this->p_item;
        }
        list_link& operator++()
        {
            *this = *this->p_next;
            return *this;
        }
        list_link& operator--()
        {
            return *this->p_prev;
        }

        T* p_item;
        list_link* p_prev;
        list_link* p_next;
    };


    typedef list_link const_iterator;


    list()
    {
        this->p_head_link = new list_link(nullptr, nullptr, nullptr);
        this->p_tail_link = new list_link(this->p_head_link, nullptr, nullptr);
        this->p_head_link->p_next = this->p_tail_link;
    }

    const_iterator begin() const
    {
        return *this->p_head_link->p_next;
    }
    const_iterator end() const
    {
        return *this->p_tail_link;
    }

    void push(T* item)
    {
        list_link* link = new list_link(this->p_tail_link->p_prev, item, this->p_tail_link);
        link->p_prev->p_next = link;
        this->p_tail_link->p_prev = link;
    }

    void unshift(T* item)
    {
        list_link* link = new list_link(this->p_head_link, item, this->p_head_link->p_next);
        link->p_next->p_prev = link;
        this->p_head_link->p_next = link;
    }

    T& pop()
    {
        list_link* link = this->p_tail_link->p_prev;
        this->p_tail_link->p_prev = link->p_prev;
        link->p_prev->p_next = this->p_tail_link;
        T* item = link->p_item;
        delete link;
        return *item;
    }

    T& shift()
    {
        list_link* link = this->p_head_link->p_next;
        this->p_head_link->p_next = link->p_next;
        link->p_next->p_prev = this->p_head_link;
        T* item = link->p_item;
        delete link;
        return *item;
    }



private:
    list_link* p_head_link;
    list_link* p_tail_link;

};



}
