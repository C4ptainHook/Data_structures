#ifndef SHUNTING_YARD_LINKED_LIST_H
#define SHUNTING_YARD_LINKED_LIST_H

template<class T>
class List{
    struct Node{
        T data;
        Node* next;
        Node(Node* _next, T _data): next(_next), data(_data) {}
        ~Node() {delete next;}
    };
    Node* head;
    Node* tail;
    unsigned int size;
    void remove_last();
    void remove_middle(Node& _temp);
public:
    List();
    void add_at(int, T);
    void append(T);
    void push(T);
    void remove(T);
    bool empty();
    Node* find(T _data) {
        Node* step=head;
        while (step&&step->data!=_data) {
            step=step->next;
        }
        if(!step)
            return nullptr;
        return step;
    }

};

template<class T>
 List<T>::List() {
     head = nullptr;
     tail = nullptr;
     size = 0;
 }

template<class T>
void List<T>::add_at(const int pos, const T _data) {
    Node* newNode = new Node(nullptr, _data);
    int idx=0;
    if(!head) {
        head=tail=newNode;
    }
    else{
        if(pos==0)
        {
            newNode->next=head;
            head=newNode;
        }
        else{
            Node* step = head;
            while (step&&idx<pos-1)
            {
                step=step->next;
                idx++;
            }
            if(!step)
            {
                tail->next=newNode;
                tail = newNode;
            }
            else {
                newNode->next = step->next;
                step->next = newNode;
            }
        }
    }
}

template<class T>
void List<T>::append(T _data) {
    Node* newNode = new Node(nullptr,_data);
    if(this->empty())
    {
        head=tail=newNode;
    }
    else{
        tail->next=newNode;
        tail=newNode;
    }
}

template<class T>
void List<T>::push(T _data) {
    Node* newNode = new Node(nullptr,_data);
    if(this->empty())
    {
        head=tail=newNode;
    }
    else{
        newNode->next=head;
        head=newNode;
    }
}

template<class T>
bool List<T>::empty() {
    if(!head)
        return true;
    return false;
}

template<class T>
void List<T>::remove(T _data) {
    Node* temp = find(_data);
    if(!temp)
        throw std::range_error("No element to delete!");
    switch(temp) {
        case head:
            head=temp->next;
            temp->next = nullptr;
            delete temp;
            break;
        case tail:
            remove_last();
            break;
        default:
            remove_middle();

    }
}

template<class T>
void List<T>::remove_last() {
    Node* step=head;
    while (!step->next->next) {
        step=step->next;
    }
    delete tail;
    step->next=nullptr;
    tail=step;
}

template<class T>
void List<T>::remove_middle(Node& _temp) {
    Node* step=head;
    while (step->next!=_temp)
    {
        step=step->next;
    }
    step->next=_temp.next;
    delete _temp;
    _temp = nullptr;
}

#endif //SHUNTING_YARD_LINKED_LIST_H
