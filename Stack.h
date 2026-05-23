#ifndef STACK_H
#define STACK_H

#include "Sequence.h"
#include "exceptions.h"

template <class T>
class Stack
{
private:
    Sequence<T> *seq;

public:
    // Принимает любую последовательность
    Stack(Sequence<T> *implementation) : seq(implementation) {}

    ~Stack() { delete seq; }

    void Push(const T &item)
    {
        Sequence<T> *newSeq = seq->Append(item);
        if (newSeq != seq)
        {
            delete seq;
            seq = newSeq;
        }
    }

    T Pop()
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

    T Top() const
    {
        if (seq->GetLength() == 0)
            throw EmptyCollection();
        return seq->GetLast();
    }

    bool IsEmpty() const { return seq->GetLength() == 0; }
    int Size() const { return seq->GetLength(); }

    // Для демонстрации и тестов
    const Sequence<T> *GetSequence() const { return seq; }
};

#endif
