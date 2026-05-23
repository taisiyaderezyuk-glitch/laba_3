#ifndef MUTABLE_ARRAY_SEQUENCE_H
#define MUTABLE_ARRAY_SEQUENCE_H

#include "ArraySequence.h"

template <class T>
class MutableArraySequence : public ArraySequence<T>
{
public:
    // Конструкторы
    MutableArraySequence() : ArraySequence<T>() {}

    MutableArraySequence(T *items, int count)
        : ArraySequence<T>(items, count) {}

    MutableArraySequence(const DynamicArray<T> &array)
        : ArraySequence<T>(array) {}

    MutableArraySequence(const MutableArraySequence<T> &other)
        : ArraySequence<T>(other) {}

    // Ключевой метод
    Sequence<T> *Instance()
    {
        return this;
    }

    // Клонирование
    Sequence<T> *Clone() const
    {
        return new MutableArraySequence<T>(*this);
    }

    Sequence<T> *NewEmpty() const
    {
        return new MutableArraySequence<T>();
    }
};

#endif
