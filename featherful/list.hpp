
#pragma once

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
    typedef list_link iterator;

    list();
    list(const list<T>& other);
    ~list();

    list<T>& operator=(list<T> other);
    T& operator[](uint index);
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

    void push(T* item);
    void unshift(T* item);
    T pop();
    T shift();
    T& at(uint index) const;

    void copy(const list<T>& other);
    list<T> clone();
    list<T>& concat(list<T>& other);
    list<T>& concat(list<T>&& other);
    list<T>& concat(list<list<T>>& other);
    list<T>& concat(list<list<T>>&& other);

    template <class K>
    list<K> map(list_mapper<T, K>& mapper) const;
    template <class K>
    list<K> map(K* (*mapper_function)(const T&)) const;
    list<T>& map_inplace(list_mapper<T, T>& mapper);
    list<T>& map_inplace(T* (*mapper_function)(const T&));

    list<T> filter(list_filterer<T>& filterer) const;
    list<T> filter(bool (*filter_function)(const T&)) const;
    list<T>& filter_inplace(list_filterer<T>& filterer);
    list<T>& filter_inplace(bool (*filter_function)(const T&));

    template <typename K>
    K reduce(list_reducer<T, K>& reducer) const;
    T reduce(T (*reducer_function)(const T&, const T&)) const;
    T reduce(T (*reducer_function)(const T&, const T&), const T& init) const;

    bool all(list_filterer<T>& filterer);
    bool all(bool (*filter_function)(const T&));
    bool none(list_filterer<T>& filterer);
    bool none(bool (*filter_function)(const T&));
    bool any(list_filterer<T>& filterer);
    bool any(bool (*filter_function)(const T&));
    bool notall(list_filterer<T>& filterer);
    bool notall(bool (*filter_function)(const T&));


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
        list_link& operator++(int);
        list_link& operator--(int);
        list_link& operator+(int amount);
        list_link& operator-(int amount);

        T* p_item;
        list_link* p_prev;
        list_link* p_next;
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
T& list<T>::operator[](uint index)
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
    for (iterator iter = this->begin(), iter_end = this->end(); iter != iter_end; ++iter)
        delete iter.p_item;
    for (list_link* link = this->p_head_link, *next = link->p_next; link != nullptr; link = next)
    {
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
    return *this->p_head_link->p_next;
}

template <class T>
typename list<T>::iterator list<T>::end() const
{
    return *this->p_tail_link;
}


template <class T>
uint list<T>::length() const
{
    return this->i_length;
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
T& list<T>::at(uint index) const
{
    if (index >= this->i_length)
        throw "death";
    else
        return *(this->begin() + index);
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
T list<T>::reduce(T (*reducer_function)(const T&, const T&)) const
{
    if (this->i_length == 0)
        throw "can't reduce empty list!";

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
template <class T>
typename list<T>::list_link& list<T>::list_link::operator++(int)
{
    list<T>::list_link link = *this;
    *this = *this->p_next;
    return link;
}
template <class T>
typename list<T>::list_link& list<T>::list_link::operator--(int)
{
    list<T>::list_link link = *this;
    *this = *this->p_prev;
    return link;
}
template <class T>
typename list<T>::list_link& list<T>::list_link::operator+(int amount)
{
    list<T>::list_link link = *this;
    if (amount > 0)
        for (int i = 0; i < amount; i++)
            link = *link.p_next;
    else
        for (int i = 0; i > amount; i--)
            link = *link.p_prev;
    return link;
}
template <class T>
typename list<T>::list_link& list<T>::list_link::operator-(int amount)
{
    list<T>::list_link link = *this;
    if (amount > 0)
        for (int i = 0; i < amount; i++)
            link = *link.p_prev;
    else
        for (int i = 0; i > amount; i--)
            link = *link.p_next;
    return link;
}





}
