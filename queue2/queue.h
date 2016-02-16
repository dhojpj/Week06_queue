#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <typeinfo>

using std::cin;
using std::cout;
using std::ostream;
using std::istream;
using std::endl;
using std::string;
using namespace std;

enum QUEUE_ERRORS {QUEUE_EMPTY, QUEUE_FULL, BAD_QUEUE_SIZE};

template<typename T>
class queue
{
public:
    queue(size_t s = 5);
    ~queue();
    queue(const queue<T>& other);
    queue<T>& operator=(const queue<T>& other);

    bool full();
    bool empty();
    size_t max_size();
    size_t size();
    void clear();
    void resize(size_t s);
    queue<T>& operator<<(const T& data);
    queue<T>& operator>>(T &data);
    void enqueue(const T&data);
    void dequeue(T& data);
    T& front() const;

    template<typename Y>
    friend ostream& operator<<(ostream &out, const queue<Y>& q);

    template<typename Y>
    friend istream& operator>>(istream &in, queue<Y>& q);

private:
    T* que;
    size_t head, tail, max_qty;

    void copy(const queue<T>& other);
    void nukem();
};

template<typename T>
queue<T>::queue(size_t s)
{
//    max_qty = s+1;
    que = new T[max_qty = s+1]; // creating dynamic array (of objects) where the tail is empty
    head = tail = 0; // head and tail are null
}

template<typename T>
queue<T>::~queue()
{
    nukem();
}

template<typename T>
queue<T>::queue(const queue<T>& other)
{
    copy(other);
}

template<typename T>
queue<T>& queue<T>::operator=(const queue<T>& other)
{
    if(this != &other)
    {
        nukem();
        copy(other);
    }

    // this means pointer to the object, so *this is an object
    return *this;
}

template<typename T>
bool queue<T>::full()
{

    // when tail is at the end, and one away from the head
    return head == (tail + 1) % max_qty; // +1 because we added 1 in the constructor
}

template<typename T>
bool queue<T>::empty()
{
    return head == tail;
}

template<typename T>
size_t queue<T>::max_size()
{
    return max_qty;
}

template<typename T>
size_t queue<T>::size()
{
            // if head is greater, max_qty + tail - head
            // if tail is greater or equal to head, tail - head
    return (tail < head ? max_qty : 0) + tail - head; // wrap around
}

template<typename T>
void queue<T>::clear()
{
            // why no nukem?
    head = tail = 0;
}

template<typename T>
void queue<T>::resize(size_t s)
{
    delete [] que;
    que = new T[max_qty = s + 1];
    head = tail = 0;
}

template<typename T>
queue<T>& queue<T>::operator<<(const T& data)
{
    enqueue(data);
    return *this;
}

template<typename T>
queue<T>& queue<T>::operator>>(T &data)
{
    dequeue(data);
    return *this;
}


// goes at the tail -- end of the line
template<typename T>
void queue<T>::enqueue(const T&data)
{
    if(full())
        throw QUEUE_FULL;

//                              cout << "tail = " << tail << endl;
//                              cout << "que[tail] = " << que[tail] << endl;

    // tail incremented by 1, but head stays behind
    que[tail++] = data;

//            cout << "que[tail] = " << que[0] << endl;


//                                          cout << "tail++ = " << tail << endl;
    tail %= max_qty;
}

// delete from the front -- because they're first in line
template<typename T>
void queue<T>::dequeue(T& data)
{
    if(empty())
        throw QUEUE_EMPTY;

    // first we grab que[head], THEN increment head++

            // code is just the same as the other one
//    data = que[head];
//    head++;


    data = que[head++];


            //            cout << "head =  " << head << endl;
            //cout << "que[head] = " << que[head] << endl;
            //    data = que[head++];

            //            cout << "head++ =  " << head << endl;



    head %= max_qty; // going circular
}


template<typename T>
T& queue<T>::front() const
{
    if(empty())
        throw QUEUE_EMPTY;
    return que[head];
}


template<typename T>
void queue<T>::copy(const queue<T>& other)
{
    que = new T[max_qty = other.max_qty];
            head = other.head;
            tail = other.tail;
            for(size_t i = head; i < tail; ++i, i%=max_qty)
            que[i] = other.que[i];
}

            // nukes the code
template<typename T>
void queue<T>::nukem()
{
    for(size_t i = 0; i < max_qty; ++i)
    {
        que[i] = T();
    }

    head = tail = max_qty = 0;
    delete [] que;
}

template<typename Y>
ostream& operator<<(ostream &out, const queue<Y>& q)
{
    // if it's cout, use comma, if not, new line
    string eol(out == cout ? ", " : "\n");

    for(size_t i = q.head; i < q.tail; ++i, i%= q.max_qty)
        out<<q.que[i]<<eol;

    if(out == cout)
        out<<"\b\b ";


    return out;

}

template<typename Y>
istream& operator>>(istream &in, queue<Y>& q)
{

    if(string(typeid(Y).name()) == "Ss" && !q.full())
    {
        string input;
        while(getline(in,input)) // why while?
        {
            try
            {
                q << input;

            }

            catch(...)
            {
                break;
            }

            if (q.full())
            {
                break;
            }


        }
    }
    else
    {

        Y inputOther;


//            in>>inputOther;
            while(in>>inputOther)
            {
                try
                {
                    q << inputOther;
                }
    //            q.enqueue(inputOther);

                catch(...)
                {
                    break;
                }

                if (q.full())
                {
                    break;
                }

            }





//        break;
    }
    return in;

}


#endif // QUEUE_H
