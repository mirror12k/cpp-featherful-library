
#pragma once

namespace featherful
{

template <class T>
class list
{

public:

    class list_link;
    typedef list_link iterator;

    list();
    ~list();

    iterator begin() const;
    iterator end() const;

    void push(T* item);
    void unshift(T* item);
    T& pop();
    T& shift();


    class list_link
    {
    public:
        list_link(list_link* prev, T* item, list_link* next);

        T& operator*() const;
        list_link& operator=(const list_link& other);
        bool operator!=(const list_link& other) const;
        bool operator==(const list_link& other) const;
        list_link& operator++();
        list_link& operator--();

        T* p_item;
        list_link* p_prev;
        list_link* p_next;
    };

private:
    list_link* p_head_link;
    list_link* p_tail_link;

};


template <class T>
list<T>::list()
{
    this->p_head_link = new list_link(nullptr, nullptr, nullptr);
    this->p_tail_link = new list_link(this->p_head_link, nullptr, nullptr);
    this->p_head_link->p_next = this->p_tail_link;
}

template <class T>
list<T>::~list()
{
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        delete iter.p_item;
    for (list_link* link = this->p_head_link; link != nullptr;)
    {
        list_link* next = link->p_next;
        delete link;
        link = next;
    }
}

template <class T>
typename list<T>::iterator list<T>::begin() const
{
    return *this->p_head_link->p_next;
}

template <class T>
typename list<T>::iterator list<T>::end() const
{
    return *this->p_tail_link;
}


template <class T>
void list<T>::push(T* item)
{
    list_link* link = new list_link(this->p_tail_link->p_prev, item, this->p_tail_link);
    link->p_prev->p_next = link;
    this->p_tail_link->p_prev = link;
}

template <class T>
void list<T>::unshift(T* item)
{
    list_link* link = new list_link(this->p_head_link, item, this->p_head_link->p_next);
    link->p_next->p_prev = link;
    this->p_head_link->p_next = link;
}


//template <class T>
//list<T>::


template <class T>
T& list<T>::pop()
{
    list_link* link = this->p_tail_link->p_prev;
    this->p_tail_link->p_prev = link->p_prev;
    link->p_prev->p_next = this->p_tail_link;
    T* item = link->p_item;
    delete link;
    return *item;
}

template <class T>
T& list<T>::shift()
{
    list_link* link = this->p_head_link->p_next;
    this->p_head_link->p_next = link->p_next;
    link->p_next->p_prev = this->p_head_link;
    T* item = link->p_item;
    delete link;
    return *item;
}









template <class T>
list<T>::list_link::list_link(list_link* prev, T* item, list_link* next)
{
    this->p_item = item;
    this->p_prev = prev;
    this->p_next = next;
}

template <class T>
T& list<T>::list_link::operator*() const
{
    return *this->p_item;
}
template <class T>
typename list<T>::list_link& list<T>::list_link::operator=(const list<T>::list_link& other)
{
    this->p_item = other.p_item;
    this->p_prev = other.p_prev;
    this->p_next = other.p_next;
    return *this;
}
template <class T>
bool list<T>::list_link::operator!=(const list_link& other) const
{
    return other.p_item != this->p_item;
}
template <class T>
bool list<T>::list_link::operator==(const list_link& other) const
{
    return other.p_item == this->p_item;
}
template <class T>
typename list<T>::list_link& list<T>::list_link::operator++()
{
    *this = *this->p_next;
    return *this;
}
template <class T>
typename list<T>::list_link& list<T>::list_link::operator--()
{
    *this = *this->p_prev;
    return *this;
}





}
