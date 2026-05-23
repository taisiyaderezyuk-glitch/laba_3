#ifndef LIST_SEQUENCE_H
#define LIST_SEQUENCE_H

#include "Sequence.h"
#include "LinkedList.h"
#include "exceptions.h"

template <class T>
class ListSequence : public Sequence<T>
{
protected:
    LinkedList<T> data;
    void AddInternal(T item)
    {
        data.Append(item);
    }

public:
    // Конструкторы
    ListSequence() : data() {}

    ListSequence(T *items, int count) : data(items, count) {}

    ListSequence(const LinkedList<T> &list) : data(list) {}

    ListSequence(const ListSequence<T> &other) : data(other.data) {}

    virtual ~ListSequence() {}

    // ----- Декомпозиция -----
    int GetLength() const
    {
        return data.GetLength();
    }

    T GetFirst() const
    {
        return data.GetFirst();
    }

    T GetLast() const
    {
        return data.GetLast();
    }

    T Get(int index) const
    {
        return data.Get(index);
    }

    // ----- Операции -----
    Sequence<T> *Append(T item)
    {
        Sequence<T> *result = this->Instance();
        ListSequence<T> *seq = static_cast<ListSequence<T> *>(result);
        seq->data.Append(item);
        return result;
    }

    Sequence<T> *Prepend(T item)
    {
        Sequence<T> *result = this->Instance();
        ListSequence<T> *seq = static_cast<ListSequence<T> *>(result);
        seq->data.Prepend(item);
        return result;
    }

    Sequence<T> *InsertAt(T item, int index)
    {
        Sequence<T> *result = this->Instance();
        ListSequence<T> *seq = static_cast<ListSequence<T> *>(result);
        seq->data.InsertAt(item, index);
        return result;
    }

    Sequence<T> *RemoveAt(int index)
    {
        if (index < 0 || index >= GetLength())
            throw IndexOutOfRange();

        Sequence<T> *result = this->Instance();
        ListSequence<T> *seq = static_cast<ListSequence<T> *>(result);
        seq->data.RemoveAt(index); // вызов оптимизированного метода LinkedList
        return result;
    }

    Sequence<T> *GetSubsequence(int start, int end)
    {
        LinkedList<T> *sub = data.GetSublist(start, end);

        Sequence<T> *result = this->Instance();
        ListSequence<T> *seq = static_cast<ListSequence<T> *>(result);

        seq->data = *sub;

        delete sub;
        return result;
    }

    Sequence<T> *Concat(const Sequence<T> &other)
    {
        Sequence<T> *result = this->Instance();
        ListSequence<T> *seq = static_cast<ListSequence<T> *>(result);

        Iterator<T> *it = other.GetIterator();
        while (it->HasNext())
            seq->data.Append(it->Next());
        delete it;

        return result;
    }

    // ----- Итератор -----
    Iterator<T> *GetIterator() const
    {
        return data.GetIterator(); // делегируем LinkedList
    }

    // ----- Абстрактные методы -----
    virtual Sequence<T> *Instance() = 0;
    virtual Sequence<T> *Clone() const = 0;
};

#endif // LIST_SEQUENCE_H
