
#pragma once

namespace featherful
{

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
            *this = *this->p_prev;
            return *this;
        }

        T* p_item;
        list_link* p_prev;
        list_link* p_next;
    };


    typedef list_link iterator;


    list()
    {
        this->p_head_link = new list_link(nullptr, nullptr, nullptr);
        this->p_tail_link = new list_link(this->p_head_link, nullptr, nullptr);
        this->p_head_link->p_next = this->p_tail_link;
    }

    iterator begin() const
    {
        return *this->p_head_link->p_next;
    }
    iterator end() const
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
