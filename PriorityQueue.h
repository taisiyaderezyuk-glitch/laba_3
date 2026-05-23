#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Sequence.h"
#include "ArraySequence.h" // для dynamic_cast
#include "MutableArraySequence.h"
#include "exceptions.h"

template <class T>
class PriorityQueue
{
private:
    Sequence<T> *seq;

    // Поиск позиции вставки (по убыванию)
    int FindInsertPos(const T &item) const
    {
        // Пытаемся привести к ArraySequence для бинарного поиска
        ArraySequence<T> *arrSeq = dynamic_cast<ArraySequence<T> *>(seq);
        if (arrSeq)
        {
            // Бинарный поиск первого элемента, меньшего item
            int low = 0, high = seq->GetLength(); // high == length (вставка в конец допустима)
            while (low < high)
            {
                int mid = (low + high) / 2;
                if (item > arrSeq->Get(mid)) // убывающий порядок: ищем первый меньший
                    high = mid;
                else
                    low = mid + 1;
            }
            return low;
        }
        else
        {
            // Линейный поиск для списка или других реализаций
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

#endif // PRIORITY_QUEUE_H
