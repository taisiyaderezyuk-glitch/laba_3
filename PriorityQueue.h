#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Sequence.h"
#include "ArraySequence.h"
#include "MutableArraySequence.h"
#include "exceptions.h"

template <class T>
class PriorityQueue
{
private:
    Sequence<T> *seq;

    // Поиск позиции вставки
    int FindInsertPos(const T &item) const
    {
        ArraySequence<T> *arrSeq = dynamic_cast<ArraySequence<T> *>(seq);
        if (arrSeq)
        {
            int low = 0, high = seq->GetLength();
            while (low < high)
            {
                int mid = (low + high) / 2;
                if (item > arrSeq->Get(mid))
                    high = mid;
                else
                    low = mid + 1;
            }
            return low;
        }
        else
        {
            int len = seq->GetLength();
            int i = 0;
            while (i < len && !(item > seq->Get(i)))
                i++;
            return i;
        }
    }

public:
    PriorityQueue() : seq(new MutableArraySequence<T>()) {}
    PriorityQueue(Sequence<T> *implementation) : seq(implementation) {}
    ~PriorityQueue() { delete seq; }

    void Enqueue(const T &item)
    {
        int pos = FindInsertPos(item);
        Sequence<T> *newSeq = seq->InsertAt(item, pos);
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

    T Peek() const
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
