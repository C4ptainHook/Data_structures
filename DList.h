#ifndef ASD_LAB6_HASH_DLIST_H
#define ASD_LAB6_HASH_DLIST_H

#include <iostream>
#include <stdexcept>

typedef unsigned int T_size;

template<class T>
class Dlist{
    struct Node{
        T data;
        Node* next;
        Node* prev;
        explicit Node(T _data): data(_data), next(nullptr), prev(nullptr){}
        ~Node() {delete next, prev;}
    };
    Node* head;
    Node* tail;
    unsigned int size;
    void create_list(T);
    bool close_to_tail(T_size);
    void add_before_ft(T, T_size);
    void add_before_fh(T, T_size);
    void add_after_ft(T, T_size);
    void add_after_fh(T, T_size);
    void destroy_list();
    void remove_ft(T);
    void remove_fh(T);

    public:
    Dlist(){
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    class iterator {
        Node *current_ptr = nullptr;
        const Dlist *o_list = nullptr;
    public:
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;
        iterator() = default;
        iterator(Node* ptr, const Dlist* gen);

        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);

        T& operator*() const;
        T* operator->() const;

        friend class Dlist;
    };
    public:
    bool empty();
    void append(T);
    void push_back(T);
    void add_before(T, T_size);
    void add_after(T, T_size);
    void pop_front();
    void pop_back();
    void remove(T_size);
    Dlist<T>::iterator begin();
    Dlist<T>::iterator end();
};

template<class T>
typename Dlist<T>::iterator Dlist<T>::begin() {
    return Dlist::iterator(head, this);
}

template<class T>
typename Dlist<T>::iterator  Dlist<T>::end() {
    return Dlist::iterator(tail->next, this);
}

template<class T>
bool Dlist<T>::empty() {
   if(!head)
       return true;
    return false;
}

template<class T>
bool Dlist<T>::close_to_tail(T_size pos) {
    if(pos>size/2)
        return true;
    return false;
}


template<class T>
void Dlist<T>::create_list(T _data) {
    Node* newNode = new Node(_data);
    head=tail=newNode;
    ++size;
}

template<class T>
void Dlist<T>::append(T _data) {
    if(empty()) {
        create_list(_data);
        return;}
    Node* newNode = new Node(_data);
    newNode->next=head;
    head->prev=newNode;
    head=newNode;
    ++size;
}

template<class T>
void Dlist<T>::push_back(T _data) {
    if(empty()) {
        create_list(_data);
        return;}
    else{
        Node* newNode = new Node(_data);
        tail->next=newNode;
        newNode->prev=tail;
        tail=newNode;
    }
    ++size;
}

template<class T>
void Dlist<T>::add_before(T _data, T_size pos) {
    if(empty()&&pos!=0)
    {
        throw std::range_error("Cannot insert before non-exist member!");
    }
    else if(!pos) {
        append(_data);
    } else if(close_to_tail(pos)) {
        add_before_ft(_data, pos);}
    else{
        add_before_fh(_data, pos);
    }
}

template<class T>
void Dlist<T>::add_before_ft(T _data, T_size pos) {
    Node* step = tail;
    for (T_size i = size-1; i > pos ; --i) {
        step=step->prev;
    }
    Node* newNode = new Node(_data);
    step->prev->next=newNode;
    newNode->prev=step->prev;
    step->prev=newNode;
    newNode->next=step;
}

template<class T>
void Dlist<T>::add_before_fh(T _data, T_size pos) {
    Node* step = head;
    for (T_size i = 0; i < pos; ++i) {
        step=step->next;
    }
    Node* newNode = new Node(_data);
    step->prev->next=newNode;
    newNode->prev=step->prev;
    step->prev=newNode;
    newNode->next=step;
}

template<class T>
void Dlist<T>::add_after(T _data, T_size pos) {
    if(empty()&&pos!=0)
    {
        throw std::range_error("Cannot insert after non-exist member!");
    } else if(close_to_tail(pos)) {
        add_after_ft(_data, pos);}
    else{
        add_after_fh(_data, pos);
    }
}

template<class T>
void Dlist<T>::add_after_ft(T _data, T_size pos) {
    Node* step = tail;
    for (T_size i = size-1; i > pos ; --i) {
        step=step->prev;
    }
    Node* newNode = new Node(_data);
    step->next->prev=newNode;
    newNode->next=step->next;
    newNode->prev=step;
    step->next=newNode;
}

template<class T>
void Dlist<T>::add_after_fh(T _data, T_size pos) {
    Node* step = head;
    for (T_size i = 0; i < pos ; ++i) {
        step=step->prev;
    }
    Node* newNode = new Node(_data);
    step->next->prev=newNode;
    newNode->next=step->next;
    newNode->prev=step;
    step->next=newNode;
}

template<class T>
void Dlist<T>::pop_front() {
    if(empty()) throw std::domain_error("Pop from from empty list");
    else if(size==1) {destroy_list();}
    else{
        Node* temp = head;
        head = temp->next;
        temp->next = nullptr;
        delete temp;
        head->prev = nullptr;
        --size;
    }
}

template<class T>
void Dlist<T>::pop_back() {
    if(empty()) throw std::domain_error("Pop from from empty list");
    else if(size==1) {destroy_list();}
    else{
        Node* temp = tail;
        tail=temp->prev;
        temp->prev = nullptr;
        delete temp;
        tail->next = nullptr;
        --size;
    }
}

template<class T>
void Dlist<T>::destroy_list() {
        delete head, tail;
        head=tail=nullptr;
        --size;
}

template<class T>
void Dlist<T>::remove(T_size pos) {
    if(pos>=size) throw std::domain_error("Can not remove non-existent member");
    else if(!pos) pop_front();
    else if(pos==size-1) pop_back();
    else if(close_to_tail(pos)) remove_ft(pos);
    else remove_fh(pos);
}

template<class T>
void Dlist<T>::remove_ft(T pos) {
    Node* step = tail;
    for (T_size i = size-1; i > pos ; --i) {
        step=step->prev;
    }

    step->prev->next=step->next;
    step->next->prev=step->prev;
    step->next = nullptr;
    step->prev = nullptr;
    delete step;
}

template<class T>
void Dlist<T>::remove_fh(T pos) {
    Node* step = head;
    for (T_size i = 0; i < pos; ++i) {
        step=step->next;
    }
    step->prev->next=step->next;
    step->next->prev=step->prev;
    step->next = nullptr;
    step->prev = nullptr;
    delete step;
}

#endif //ASD_LAB6_HASH_DLIST_H
