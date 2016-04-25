
#pragma once


#include "exception.hpp"

#include <cstdio>

typedef unsigned int uint;

namespace featherful
{

template <class T, class R>
class list_mapper
{
public:
    virtual R* map(const T& item) = 0;
};

template <class T>
class list_filterer
{
public:
    virtual bool filter(const T& item) = 0;
};

template <class T, class R>
class list_reducer
{
public:
    virtual void reduce(const T& item) = 0;
    virtual R produce() = 0;
};

template <class T>
class list
{

public:

    class list_link;
    class iterator;
//    typedef list_link iterator;

    list();
    list(const list<T>& other);
    list(list_link* start, list_link* end);
    ~list();

    list<T>& operator=(list<T> other);
    T& operator[](int index);
    list<T>& operator+(list<T>& other);
    list<T>& operator+(list<T>&& other);
    list<T>& operator+=(list<T>& other);
    list<T>& operator+=(list<T>&& other);

    void init_empty();
    void destroy();
    void pilfer_links(list_link* start, list_link* end, uint* length);

    iterator begin() const;
    iterator end() const;

    uint length() const;
    bool empty() const;

    void push(T* item);
    void unshift(T* item);
    T pop();
    T shift();
    T& at(int index) const;
    iterator iterator_at(int index) const;

    void copy(const list<T>& other);
    list<T> clone();
    list<T>& concat(list<T>& other);
    list<T>& concat(list<T>&& other);
    list<T>& concat(list<list<T>>& other);
    list<T>& concat(list<list<T>>&& other);

    list<T> slice(iterator start, iterator end);
    list<T> slice(int start, int end);
    list<T>& slice_inplace(iterator start, iterator end);
    list<T>& slice_inplace(int start, int end);
    list<T>& splice(list<T>& items, iterator start, iterator end);
    list<T>& splice(list<T>&& items, iterator start, iterator end);
    list<T>& splice(list<T>& items, int start, int end);
    list<T>& splice(list<T>&& items, int start, int end);


    template <class K>
    list<K> map(list_mapper<T, K>& mapper) const;
    template <class K>
    list<K> map(list_mapper<T, K>&& mapper) const;
    template <class K>
    list<K> map(K* (*mapper_function)(const T&)) const;
    list<T>& map_inplace(list_mapper<T, T>& mapper);
    list<T>& map_inplace(list_mapper<T, T>&& mapper);
    list<T>& map_inplace(T* (*mapper_function)(const T&));

    list<T> filter(list_filterer<T>& filterer) const;
    list<T> filter(list_filterer<T>&& filterer) const;
    list<T> filter(bool (*filter_function)(const T&)) const;
    list<T>& filter_inplace(list_filterer<T>& filterer);
    list<T>& filter_inplace(list_filterer<T>&& filterer);
    list<T>& filter_inplace(bool (*filter_function)(const T&));

    template <typename K>
    K reduce(list_reducer<T, K>& reducer) const;
    template <typename K>
    K reduce(list_reducer<T, K>&& reducer) const;
    T reduce(T (*reducer_function)(const T&, const T&)) const;
    T reduce(T (*reducer_function)(const T&, const T&), const T& init) const;

    bool all(list_filterer<T>& filterer) const;
    bool all(list_filterer<T>&& filterer) const;
    bool all(bool (*filter_function)(const T&)) const;
    bool none(list_filterer<T>& filterer) const;
    bool none(list_filterer<T>&& filterer) const;
    bool none(bool (*filter_function)(const T&)) const;
    bool any(list_filterer<T>& filterer) const;
    bool any(list_filterer<T>&& filterer) const;
    bool any(bool (*filter_function)(const T&)) const;
    bool notall(list_filterer<T>& filterer) const;
    bool notall(list_filterer<T>&& filterer) const;
    bool notall(bool (*filter_function)(const T&)) const;


    class list_link
    {
    public:
        list_link(list_link* prev, T* item, list_link* next);

        T* p_item;
        list_link* p_prev;
        list_link* p_next;
    };

    class iterator
    {
    public:
        iterator(list_link* link);

        T& operator*() const;
        bool operator!=(const iterator& other) const;
        bool operator==(const iterator& other) const;
        iterator& operator++();
        iterator& operator--();
        iterator operator++(int);
        iterator operator--(int);
        iterator operator+(int amount);
        iterator operator-(int amount);

        list_link* link;
    };

private:
    list_link* p_head_link;
    list_link* p_tail_link;

    uint i_length = 0;
};







template <class T>
list<T>::list()
{
//    printf("ctor list\n");
    this->init_empty();
}


template <class T>
list<T>::list(const list<T>& other)
{
//    printf("ctor list copy\n");
    this->init_empty();
    this->copy(other);
}


template <class T>
list<T>::list(list_link* start, list_link* end)
{
//    printf("ctor list copy\n");
    this->init_empty();
    this->p_head_link->p_next = start;
    start->p_prev = this->p_head_link;
    this->p_tail_link->p_prev = end;
    end->p_next = this->p_tail_link;

    int length = 1;
    for (list_link* iter = start; iter != end; iter = iter->p_next)
        length++;
    this->i_length = length;
}

template <class T>
list<T>::~list()
{
//    printf("dtor list: %d\n", this->i_length);
    this->destroy();
}


template <class T>
list<T>& list<T>::operator=(list<T> other)
{
    this->copy(other);
//    other.pilfer_links(this->p_head_link, this->p_tail_link, &this->i_length);
    return *this;
}

template <class T>
T& list<T>::operator[](int index)
{
    return this->at(index);
}
template <class T>
list<T>& list<T>::operator+(list<T>& other)
{
    this->concat(other);
    return *this;
}
template <class T>
list<T>& list<T>::operator+(list<T>&& other)
{
    this->concat(other);
    return *this;
}

template <class T>
list<T>& list<T>::operator+=(list<T>& other)
{
    this->concat(other);
    return *this;
}
template <class T>
list<T>& list<T>::operator+=(list<T>&& other)
{
    this->concat(other);
    return *this;
}


template <class T>
void list<T>::init_empty()
{
    this->p_head_link = new list_link(nullptr, nullptr, nullptr);
    this->p_tail_link = new list_link(this->p_head_link, nullptr, nullptr);
    this->p_head_link->p_next = this->p_tail_link;
}

template <class T>
void list<T>::destroy()
{
    for (list_link* link = this->p_head_link, *next = link->p_next; link != nullptr; link = next)
    {
        if (link->p_item)
            delete link->p_item;
        next = link->p_next;
        delete link;
    }

    this->p_head_link = nullptr;
    this->p_tail_link = nullptr;
    this->i_length = 0;
}

template <class T>
void list<T>::pilfer_links(list_link* start, list_link* end, uint* length)
{
    if (this->i_length > 0)
    {
        start->p_next = this->p_head_link->p_next;
        this->p_head_link->p_next->p_prev = start;
        end->p_prev = this->p_tail_link->p_prev;
        this->p_tail_link->p_prev->p_next = end;
    }
    this->p_head_link->p_next = this->p_tail_link;
    this->p_tail_link->p_prev = this->p_head_link;
    *length += this->i_length;
    this->i_length = 0;
}

template <class T>
typename list<T>::iterator list<T>::begin() const
{
    return iterator(this->p_head_link->p_next);
}

template <class T>
typename list<T>::iterator list<T>::end() const
{
    return iterator(this->p_tail_link);
}


template <class T>
uint list<T>::length() const
{
    return this->i_length;
}

template <class T>
bool list<T>::empty() const
{
    return this->i_length == 0;
}

template <class T>
void list<T>::push(T* item)
{
    list_link* link = new list_link(this->p_tail_link->p_prev, item, this->p_tail_link);
    link->p_prev->p_next = link;
    this->p_tail_link->p_prev = link;
    this->i_length++;
}

template <class T>
void list<T>::unshift(T* item)
{
    list_link* link = new list_link(this->p_head_link, item, this->p_head_link->p_next);
    link->p_next->p_prev = link;
    this->p_head_link->p_next = link;
    this->i_length++;
}



template <class T>
T list<T>::pop()
{
    list_link* link = this->p_tail_link->p_prev;
    this->p_tail_link->p_prev = link->p_prev;
    link->p_prev->p_next = this->p_tail_link;
    T* item = link->p_item;
    delete link;
    this->i_length--;
    return *item;
}

template <class T>
T list<T>::shift()
{
    list_link* link = this->p_head_link->p_next;
    this->p_head_link->p_next = link->p_next;
    link->p_next->p_prev = this->p_head_link;
    T* item = link->p_item;
    delete link;
    this->i_length--;
    return *item;
}

template <class T>
T& list<T>::at(int index) const
{
    if (index < 0)
    {
        if (index + (int)this->i_length < 0)
            throw range_exception("negative list index out of bounds in list::at", index);
        else
            return *(this->end() + index);
    }
    else if (index >= this->i_length)
        throw range_exception("list index out of bounds in list::at", index);
//    else
    return *(this->begin() + index);
}
template <class T>
typename list<T>::iterator list<T>::iterator_at(int index) const
{
    if (index < 0)
    {
        if (index + (int)this->i_length < 0)
            throw range_exception("negative list index out of bounds in list::iterator_at", index);
        else
            return this->end() + index;
    }
    else if (index >= this->i_length)
        throw range_exception("list index out of bounds in list::iterator_at", index);

    return this->begin() + index;
}





template <class T>
void list<T>::copy(const list<T>& other)
{
    this->destroy();
    this->init_empty();

    list_link* prev_link = this->p_head_link, *last_link = this->p_tail_link;
    for (iterator iter = other.begin(), iter_end = other.end(); iter != iter_end; ++iter)
    {
        list_link* link = new list_link(prev_link, new T(*iter), last_link);
        prev_link->p_next = link;
        prev_link = link;
        this->i_length++;
    }
    last_link->p_prev = prev_link;
}

template <class T>
list<T> list<T>::clone()
{
    return list<T>(*this);
}

template <class T>
list<T>& list<T>::concat(list<T>& other)
{
    other.pilfer_links(this->p_tail_link->p_prev, this->p_tail_link, &this->i_length);
    return *this;
}

template <class T>
list<T>& list<T>::concat(list<T>&& other)
{
    other.pilfer_links(this->p_tail_link->p_prev, this->p_tail_link, &this->i_length);
    return *this;
}

template <class T>
list<T>& list<T>::concat(list<list<T>>& other)
{
    for (typename list<list<T>>::iterator iter = other.begin(), iter_end = other.end(); iter != iter_end; ++iter)
        (*iter).pilfer_links(this->p_tail_link->p_prev, this->p_tail_link, &this->i_length);
    return *this;
}

template <class T>
list<T>& list<T>::concat(list<list<T>>&& other)
{
    for (typename list<list<T>>::iterator iter = other.begin(), iter_end = other.end(); iter != iter_end; ++iter)
        (*iter).pilfer_links(this->p_tail_link->p_prev, this->p_tail_link, &this->i_length);
    return *this;
}


template <class T>
list<T> list<T>::slice(iterator start, iterator end)
{
    list_link* link = start.link, *last_link = end.link;
    if (link == this->p_head_link)
        throw invalid_exception("invalid slice start iterator at list::slice");
    else if (last_link == this->p_tail_link)
        throw invalid_exception("invalid slice end iterator at list::slice");

    link->p_prev->p_next = last_link->p_next;
    link->p_prev->p_next->p_prev = link->p_prev;
    list<T> result(link, last_link);
    int length = 0;
    for (list_link* iter = this->p_head_link->p_next, * iter_end = this->p_tail_link; iter != iter_end; iter = iter->p_next)
        length++;
    this->i_length = length;
    return result;
}

template <class T>
list<T> list<T>::slice(int start, int end)
{
    return this->slice(this->iterator_at(start), this->iterator_at(end));
}

template <class T>
list<T>& list<T>::slice_inplace(iterator start, iterator end)
{
    list_link* link = start.link, *last_link = end.link;
    if (link == this->p_head_link)
        throw invalid_exception("invalid slice start iterator at list::slice_inplace");
    else if (last_link == this->p_tail_link)
        throw invalid_exception("invalid slice end iterator at list::slice_inplace");

    for (list_link* iter = this->p_head_link->p_next; iter != link;)
    {
        list_link* next = iter->p_next;
        delete iter->p_item;
        delete iter;
        iter = next;
        this->i_length--;
    }
    for (list_link* iter = last_link->p_next, * iter_end = this->p_tail_link; iter != iter_end;)
    {
        list_link* next = iter->p_next;
        delete iter->p_item;
        delete iter;
        iter = next;
        this->i_length--;
    }

    this->p_head_link->p_next = link;
    this->p_head_link->p_next->p_prev = this->p_head_link;
    this->p_tail_link->p_prev = last_link;
    this->p_tail_link->p_prev->p_next = this->p_tail_link;

    return *this;
}

template <class T>
list<T>& list<T>::slice_inplace(int start, int end)
{
    return this->slice_inplace(this->iterator_at(start), this->iterator_at(end));
}

template <class T>
list<T>& list<T>::splice(list<T>& items, iterator start, iterator end)
{
    list_link* link = start.link, *last_link = end.link;
    if (link == this->p_head_link)
        throw invalid_exception("invalid splice start iterator at list::splice");
    else if (last_link == this->p_tail_link)
        throw invalid_exception("invalid splice end iterator at list::splice");

    list_link* before = link->p_prev, * after = last_link->p_next;

    for (list_link* iter = link; iter != after;)
    {
        list_link* next = iter->p_next;
        delete iter->p_item;
        delete iter;
        iter = next;
        this->i_length--;
    }

    items.pilfer_links(before, after, &this->i_length);
    return *this;
}

template <class T>
list<T>& list<T>::splice(list<T>&& items, iterator start, iterator end)
{
    list_link* link = start.link, *last_link = end.link;
    if (link == this->p_head_link)
        throw invalid_exception("invalid splice start iterator at list::splice");
    else if (last_link == this->p_tail_link)
        throw invalid_exception("invalid splice end iterator at list::splice");

    list_link* before = link->p_prev, * after = last_link->p_next;

    for (list_link* iter = link; iter != after;)
    {
        list_link* next = iter->p_next;
        delete iter->p_item;
        delete iter;
        iter = next;
        this->i_length--;
    }

    items.pilfer_links(before, after, &this->i_length);
    return *this;
}

template <class T>
list<T>& list<T>::splice(list<T>& items, int start, int end)
{
    return this->splice(items, this->iterator_at(start), this->iterator_at(end));
}

template <class T>
list<T>& list<T>::splice(list<T>&& items, int start, int end)
{
    return this->splice(items, this->iterator_at(start), this->iterator_at(end));
}



template <class T>
template <class K>
list<K> list<T>::map(list_mapper<T, K>& mapper) const
{
    list<K> result;
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        result.push(mapper.map(*iter));
    return result;
}

template <class T>
template <class K>
list<K> list<T>::map(list_mapper<T, K>&& mapper) const
{
    list<K> result;
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        result.push(mapper.map(*iter));
    return result;
}

template <class T>
template <class K>
list<K> list<T>::map(K* (*mapper_function)(const T&)) const
{
    list<K> result;
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        result.push(mapper_function(*iter));
    return result;
}


template <class T>
list<T>& list<T>::map_inplace(list_mapper<T, T>& mapper)
{
    for (list_link* link = this->p_head_link->p_next, *link_end = this->p_tail_link; link != link_end; link = link->p_next)
    {
        T* val = mapper.map(*link->p_item);
        delete link->p_item;
        link->p_item = val;
    }
    return *this;
}
template <class T>
list<T>& list<T>::map_inplace(list_mapper<T, T>&& mapper)
{
    for (list_link* link = this->p_head_link->p_next, *link_end = this->p_tail_link; link != link_end; link = link->p_next)
    {
        T* val = mapper.map(*link->p_item);
        delete link->p_item;
        link->p_item = val;
    }
    return *this;
}

template <class T>
list<T>& list<T>::map_inplace(T* (*mapper_function)(const T&))
{
    for (list_link* link = this->p_head_link->p_next, *link_end = this->p_tail_link; link != link_end; link = link->p_next)
    {
        T* val = mapper_function(*link->p_item);
        delete link->p_item;
        link->p_item = val;
    }
    return *this;
}


template <class T>
list<T> list<T>::filter(list_filterer<T>& filterer) const
{
    list<T> result;
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        if (filterer.filter(*iter))
            result.push(new T(*iter));
    return result;
}

template <class T>
list<T> list<T>::filter(list_filterer<T>&& filterer) const
{
    list<T> result;
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        if (filterer.filter(*iter))
            result.push(new T(*iter));
    return result;
}

template <class T>
list<T> list<T>::filter(bool (*filter_function)(const T&)) const
{
    list<T> result;
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        if (filter_function(*iter))
            result.push(new T(*iter));
    return result;
}


template <class T>
list<T>& list<T>::filter_inplace(list_filterer<T>& filterer)
{
    for (list_link* link = this->p_head_link->p_next, *link_end = this->p_tail_link; link != link_end; link = link->p_next)
        if (! filterer.filter(*link->p_item))
        {
            link->p_next->p_prev = link->p_prev;
            link->p_prev->p_next = link->p_next;
            delete link->p_item;
            this->i_length--;
        }
    return *this;
}

template <class T>
list<T>& list<T>::filter_inplace(list_filterer<T>&& filterer)
{
    for (list_link* link = this->p_head_link->p_next, *link_end = this->p_tail_link; link != link_end; link = link->p_next)
        if (! filterer.filter(*link->p_item))
        {
            link->p_next->p_prev = link->p_prev;
            link->p_prev->p_next = link->p_next;
            delete link->p_item;
            this->i_length--;
        }
    return *this;
}

template <class T>
list<T>& list<T>::filter_inplace(bool (*filter_function)(const T&))
{
    for (list_link* link = this->p_head_link->p_next, *link_end = this->p_tail_link; link != link_end; link = link->p_next)
        if (! filter_function(*link->p_item))
        {
            link->p_next->p_prev = link->p_prev;
            link->p_prev->p_next = link->p_next;
            delete link->p_item;
            this->i_length--;
        }
    return *this;
}



template <class T>
template <typename K>
K list<T>::reduce(list_reducer<T, K>& reducer) const
{
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        reducer.reduce(*iter);
    return reducer.produce();
}

template <class T>
template <typename K>
K list<T>::reduce(list_reducer<T, K>&& reducer) const
{
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        reducer.reduce(*iter);
    return reducer.produce();
}

template <class T>
T list<T>::reduce(T (*reducer_function)(const T&, const T&)) const
{
    if (this->i_length == 0)
        throw invalid_exception("can't reduce empty list at list::reduce");

    iterator iter = this->begin(), iter_end = this->end();
    T result = *iter;
    for (++iter; iter != iter_end; ++iter)
        result = reducer_function(result, *iter);
    return result;
}

template <class T>
T list<T>::reduce(T (*reducer_function)(const T&, const T&), const T& init) const
{
    T result = init;
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        result = reducer_function(result, *iter);
    return result;
}


template <class T>
bool list<T>::all(list_filterer<T>& filterer) const
{
    list<T> result;
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        if (! filterer.filter(*iter))
            return false;
    return true;
}

template <class T>
bool list<T>::all(list_filterer<T>&& filterer) const
{
    list<T> result;
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        if (! filterer.filter(*iter))
            return false;
    return true;
}

template <class T>
bool list<T>::all(bool (*filter_function)(const T&)) const
{
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        if (! filter_function(*iter))
            return false;
    return true;
}

template <class T>
bool list<T>::none(list_filterer<T>& filterer) const
{
    list<T> result;
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        if (filterer.filter(*iter))
            return false;
    return true;
}

template <class T>
bool list<T>::none(list_filterer<T>&& filterer) const
{
    list<T> result;
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        if (filterer.filter(*iter))
            return false;
    return true;
}

template <class T>
bool list<T>::none(bool (*filter_function)(const T&)) const
{
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        if (filter_function(*iter))
            return false;
    return true;
}

template <class T>
bool list<T>::any(list_filterer<T>& filterer) const
{
    return ! this->none(filterer);
}

template <class T>
bool list<T>::any(list_filterer<T>&& filterer) const
{
    return ! this->none(filterer);
}

template <class T>
bool list<T>::any(bool (*filter_function)(const T&)) const
{
    return ! this->none(filter_function);
}

template <class T>
bool list<T>::notall(list_filterer<T>& filterer) const
{
    return ! this->all(filterer);
}

template <class T>
bool list<T>::notall(list_filterer<T>&& filterer) const
{
    return ! this->all(filterer);
}

template <class T>
bool list<T>::notall(bool (*filter_function)(const T&)) const
{
    return ! this->all(filter_function);
}






















template <class T>
list<T>::list_link::list_link(list_link* prev, T* item, list_link* next)
{
    this->p_item = item;
    this->p_prev = prev;
    this->p_next = next;
}

















template <class T>
list<T>::iterator::iterator(list_link* link) : link(link)
{}

template <class T>
T& list<T>::iterator::operator*() const
{
    if (this->link->p_item)
        return *this->link->p_item;
    else
        throw iterator_exception("attempt to dereference head or tail iterator at list::iterator dereference");
}
template <class T>
bool list<T>::iterator::operator!=(const iterator& other) const
{
    return this->link != other.link;
}

template <class T>
bool list<T>::iterator::operator==(const iterator& other) const
{
    return this->link == other.link;
}

template <class T>
typename list<T>::iterator& list<T>::iterator::operator++()
{
    if (this->link->p_next == nullptr)
        throw iterator_exception("list iterator out of bounds in list::iterator increment");
    this->link = this->link->p_next;
    return *this;
}

template <class T>
typename list<T>::iterator& list<T>::iterator::operator--()
{
    if (this->link->p_prev == nullptr)
        throw iterator_exception("list iterator out of bounds in list::iterator decrement");
    this->link = this->link->p_prev;
    return *this;
}

template <class T>
typename list<T>::iterator list<T>::iterator::operator++(int)
{
    if (this->link->p_next == nullptr)
        throw iterator_exception("list iterator out of bounds in list::iterator increment");
    iterator result(*this);
    this->link = this->link->p_next;
    return result;
}

template <class T>
typename list<T>::iterator list<T>::iterator::operator--(int)
{
    if (this->link->p_prev == nullptr)
        throw iterator_exception("list iterator out of bounds in list::iterator increment");
    iterator result(*this);
    this->link = this->link->p_prev;
    return result;
}


template <class T>
typename list<T>::iterator list<T>::iterator::operator+(int amount)
{
    list_link* link = this->link;
    if (amount < 0)
        for (int i = 0; i > amount; i--)
        {
            if (link->p_prev)
                link = link->p_prev;
            else
                throw iterator_exception("list iterator out of bounds in list::iterator addition");
        }
    else
        for (int i = 0; i < amount; i++)
            if (link->p_next)
                link = link->p_next;
            else
                throw iterator_exception("list iterator out of bounds in list::iterator addition");

    return list<T>::iterator(link);
}

template <class T>
typename list<T>::iterator list<T>::iterator::operator-(int amount)
{
    list_link* link = this->link;
    if (amount < 0)
        for (int i = 0; i > amount; i--)
            if (link->p_next)
                link = link->p_next;
            else
                throw iterator_exception("list iterator out of bounds in list::iterator subtraction");
    else
        for (int i = 0; i < amount; i++)
            if (link->p_prev)
                link = link->p_prev;
            else
                throw iterator_exception("list iterator out of bounds in list::iterator subtraction");

    return list<T>::iterator(link);
}




}
