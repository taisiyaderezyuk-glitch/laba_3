#ifndef ARRAY_SEQUENCE_H
#define ARRAY_SEQUENCE_H

#include "Sequence.h"
#include "DynamicArray.h"
#include "exceptions.h"

template <class T>
class ArraySequence : public Sequence<T>
{
protected:
    DynamicArray<T> data;
    void AddInternal(T item)
    {
        int size = data.GetSize();
        data.Resize(size + 1);
        data.Set(size, item);
    }

public:
    // Конструкторы
    ArraySequence() : data(0) {}
    ArraySequence(T *items, int count) : data(items, count) {}
    ArraySequence(const DynamicArray<T> &array) : data(array) {}
    ArraySequence(const ArraySequence<T> &other) : data(other.data) {}
    virtual ~ArraySequence() {}

    // Декомпозиция
    int GetLength() const
    {
        return data.GetSize();
    }

    T GetFirst() const
    {
        if (GetLength() == 0)
            throw EmptyCollection();
        return data.Get(0);
    }

    T GetLast() const
    {
        if (GetLength() == 0)
            throw EmptyCollection();
        return data.Get(GetLength() - 1);
    }

    T Get(int index) const
    {
        return data.Get(index);
    }

    // Операции
    Sequence<T> *Append(T item)
    {
        Sequence<T> *result = this->Instance();
        ArraySequence<T> *seq = static_cast<ArraySequence<T> *>(result);

        int size = seq->data.GetSize();
        seq->data.Resize(size + 1);
        seq->data.Set(size, item);

        return result;
    }

    Sequence<T> *Prepend(T item)
    {
        Sequence<T> *result = this->Instance();
        ArraySequence<T> *seq = static_cast<ArraySequence<T> *>(result);

        int size = seq->data.GetSize();
        seq->data.Resize(size + 1);

        for (int i = size; i > 0; i--)
            seq->data.Set(i, seq->data.Get(i - 1));

        seq->data.Set(0, item);

        return result;
    }

    Sequence<T> *InsertAt(T item, int index)
    {
        if (index < 0 || index > GetLength())
            throw IndexOutOfRange();

        Sequence<T> *result = this->Instance();
        ArraySequence<T> *seq = static_cast<ArraySequence<T> *>(result);

        int size = seq->data.GetSize();
        seq->data.Resize(size + 1);

        for (int i = size; i > index; i--)
            seq->data.Set(i, seq->data.Get(i - 1));

        seq->data.Set(index, item);

        return result;
    }

    Sequence<T> *RemoveAt(int index)
    {
        if (index < 0 || index >= GetLength())
            throw IndexOutOfRange();

        Sequence<T> *result = this->Instance();
        ArraySequence<T> *seq = static_cast<ArraySequence<T> *>(result);

        int size = seq->data.GetSize();

        for (int i = index; i < size - 1; i++)
            seq->data.Set(i, seq->data.Get(i + 1));

        seq->data.Resize(size - 1);

        return result;
    }

    Sequence<T> *GetSubsequence(int start, int end)
    {
        DynamicArray<T> *sub = data.GetSubarray(start, end);

        Sequence<T> *result = this->Instance();
        ArraySequence<T> *seq = static_cast<ArraySequence<T> *>(result);

        seq->data = *sub;

        delete sub;
        return result;
    }

    Sequence<T> *Concat(const Sequence<T> &other)
    {
        Sequence<T> *result = this->Instance();
        ArraySequence<T> *seq = static_cast<ArraySequence<T> *>(result);

        int originalSize = seq->data.GetSize();
        int otherSize = other.GetLength();
        seq->data.Resize(originalSize + otherSize);

        Iterator<T> *it = other.GetIterator();
        for (int i = 0; it->HasNext(); i++)
            seq->data.Set(originalSize + i, it->Next());
        delete it;

        return result;
    }

    // Итератор
    Iterator<T> *GetIterator() const
    {
        return data.GetIterator();
    }

    // Абстрактные методы
    virtual Sequence<T> *Instance() = 0;
    virtual Sequence<T> *Clone() const = 0;
};

#endif
