#ifndef DEQUE_H
#define DEQUE_H

#include "Sequence.h"
#include "exceptions.h"

template <class T>
class Deque
{
private:
    Sequence<T> *seq;

public:
    Deque(Sequence<T> *implementation) : seq(implementation) {}

    ~Deque() { delete seq; }

    void PushFront(const T &item)
    {
        Sequence<T> *newSeq = seq->Prepend(item);
        if (newSeq != seq)
        {
            delete seq;
            seq = newSeq;
        }
    }

    void PushBack(const T &item)
    {
        Sequence<T> *newSeq = seq->Append(item);
        if (newSeq != seq)
        {
            delete seq;
            seq = newSeq;
        }
    }

    T PopFront()
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

    T PopBack()
    {
        if (seq->GetLength() == 0)
            throw EmptyCollection();
        T item = seq->GetLast();
        Sequence<T> *newSeq = seq->RemoveAt(seq->GetLength() - 1);
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

    T Back() const
    {
        if (seq->GetLength() == 0)
            throw EmptyCollection();
        return seq->GetLast();
    }

    bool IsEmpty() const { return seq->GetLength() == 0; }
    int Size() const { return seq->GetLength(); }

    const Sequence<T> *GetSequence() const { return seq; }
};

#endif
