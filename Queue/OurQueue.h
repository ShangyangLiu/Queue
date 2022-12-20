#ifndef OURQUEUE_H
#define OURQUEUE_H

#include <string>
#include "error.h"
#include <iostream>
#include <sstream>
using namespace std;

template <typename ValueType>
class OurQueue
{
public:
    OurQueue();
    ~OurQueue();

    OurQueue(const OurQueue<ValueType>& queue2);
    OurQueue<ValueType>& operator=(const OurQueue<ValueType>& queue2);

    void enqueue(const ValueType& value);
    const ValueType& peek() const;
    ValueType dequeue();
    int size() const;
    bool isEmpty() const;
    void clear();
    bool equals(const OurQueue<ValueType> &queue2) const;
    bool operator==(const OurQueue& queue2) const;
    bool operator!=(const OurQueue& queue2) const;

    string toString() const;

    template <typename T>
    friend ostream& operator<<(ostream &out,const OurQueue<T>& queue);
    template <typename T>
    friend istream& operator<<(istream &in,const OurQueue<T>& queue);

private:
    ValueType *elements;
    int capacity;
    int head;
    int tail;
    static const int INITIAL_CAPACITY=10;
    void expand();
};

template <typename ValueType>
const int OurQueue<ValueType>::INITIAL_CAPACITY;

template <typename ValueType>
OurQueue<ValueType>::OurQueue()
{
    elements =new ValueType[INITIAL_CAPACITY];
    capacity=INITIAL_CAPACITY;
    head=0;
    tail=0;
}

template <typename ValueType>
OurQueue<ValueType>::~OurQueue()
{
    delete[] elements;
}

template <typename ValueType>
OurQueue<ValueType>::OurQueue(const OurQueue<ValueType> &queue2)
{
    capacity =max(INITIAL_CAPACITY,(queue2.tail-queue2.head)*2);
    elements=new ValueType[capacity];
    for (int i=queue2.head;i<queue2.tail;i++)
    {
        elements[i-queue2.head]=queue2.elements[i];
    }
    head=0;
    tail=queue2.tail-queue2.head;
}

template <typename ValueType>
OurQueue<ValueType>& OurQueue<ValueType>::operator=(const OurQueue<ValueType>& queue2)
{
    if (capacity>queue2.tail-queue2.head)
    {
        for (int i=queue2.head;i<queue2.tail;i++)
        {
            elements[i-queue2.head]=queue2.elements[i];
        }
    }
    else
    {
        delete[] elements;
        capacity=(queue2.tail-queue2.head)*2;
        elements=new ValueType[capacity];
        for (int i=queue2.head;i<queue2.tail;i++)
        {
            elements[i-queue2.head]=queue2.elements[i];
        }
    }
    head=0;
    tail=queue2.tail-queue2.head;
    return *this;
}

template <typename ValueType>
void OurQueue<ValueType>::enqueue(const ValueType& value)
{
    if (tail==capacity)
    {
        expand();
    }
    elements[tail++]=value;
}

template <typename ValueType>
const ValueType& OurQueue<ValueType>::peek() const
{
    if (isEmpty()){
        error ("Queue::peek: Attempting to peek an empty queue");
    }
    return elements[head];
}

template <typename ValueType>
ValueType OurQueue<ValueType>::dequeue(){
    if (isEmpty())
    {
        error("Queue::peek: Attempting to peek at an empty queue");
    }
    return elements[head++];
}

template <typename ValueType>
int OurQueue<ValueType>::size() const
{
    return tail-head;
}

template <typename ValueType>
bool OurQueue<ValueType>::isEmpty() const
{
    return tail==head;
}

template <typename ValueType>
void OurQueue<ValueType>::clear()
{
    tail=head=0;
}

template <typename ValueType>
bool OurQueue<ValueType>::equals(const OurQueue<ValueType>& queue2) const
{
    return *this==queue2;
}

template <typename ValueType>
bool OurQueue<ValueType>::operator==(const OurQueue& queue2) const
{
    if (queue2.size()!=size()){
        return false;
    }
    for (int i=head;i<tail;i++)
    {
        if (elements[i]!=queue2.elements[queue2.head+i-head])
            return false;
    }
    return true;
}

template <typename ValueType>
bool OurQueue<ValueType>::operator!=(const OurQueue& queue2) const
{
    return !(*this==queue2);
}

template <typename ValueType>
void OurQueue<ValueType>::expand()
{
    capacity=max(INITIAL_CAPACITY,(tail-head)*2);
    ValueType* newElements=new ValueType[capacity];
    for (int i=head;i<tail;i++)
    {
       newElements[i-head]=elements[i];
    }
    delete[] elements;
    elements=newElements;
    tail=tail-head;
    head=0;
}

template <typename ValueType>
string OurQueue<ValueType>::toString() const{
    ostringstream os;
    os<<*this;
    return os.str();
}

template <typename ValueType>
ostream& operator<<(ostream &cout,const OurQueue<ValueType>& queue)
{
    cout<<"{";
    for (int i=queue.head;i<queue.tail-1;i++)
    {
        cout<<queue.elements[i]<<", ";
    }
    cout<<queue.elements[queue.tail-1]<<"}";
    return cout;
}

template <typename ValueType>
istream& operator>>(istream &cin,OurQueue<ValueType>& queue)
{
    char ch='\0';
    cin>>ch;
    if (ch!='{')
    {
        cin.setstate(ios::failbit);
        return cin;
    }
    queue.clear();
    cin>>ch;
    if (ch!='}')
    {
        cin.unget();
        while (true)
        {
            ValueType elem;
            if (!(cin>>elem))
            {
                cin.setstate(ios_base::failbit);
                return cin;
            }
            queue.enqueue(elem);
            cin>>ch;
            if (ch=='}')
                break;
            if (ch!=',')
            {
                cin.setstate(ios_base::failbit);
                return cin;
            }
        }
    }
    return cin;
}






























#endif // OURQUEUE_H
