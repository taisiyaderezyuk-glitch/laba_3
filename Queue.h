#ifndef QUEUE_H
#define QUEUE_H

#include "Sequence.h"
#include "exceptions.h"

template <class T>
class Queue
{
private:
    Sequence<T> *seq;

public:
    Queue(Sequence<T> *implementation) : seq(implementation) {}

    ~Queue() { delete seq; }

    void Enqueue(const T &item)
    {
        Sequence<T> *newSeq = seq->Append(item);
        if (newSeq != seq)
        {
            delete seq;
            seq = newSeq;
        }
    }

    T Dequeue()
    {
        if (seq->GetLength() == 0)
            throw EmptyCollection();
        T item = seq->GetFirst();
        Sequence<T> *newSeq = seq->RemoveAt(0);
        if (newSeq != seq)
        {
            delete seq;
            seq = newSeq;
        }
        return item;
    }

    T Front() const
    {
        if (seq->GetLength() == 0)
            throw EmptyCollection();
        return seq->GetFirst();
    }

    bool IsEmpty() const { return seq->GetLength() == 0; }
    int Size() const { return seq->GetLength(); }

    const Sequence<T> *GetSequence() const { return seq; }
};

#endif
