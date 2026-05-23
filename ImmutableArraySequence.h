#ifndef IMMUTABLE_ARRAY_SEQUENCE_H
#define IMMUTABLE_ARRAY_SEQUENCE_H

#include "ArraySequence.h"

template <class T>
class ImmutableArraySequence : public ArraySequence<T>
{
public:
    // Конструкторы
    ImmutableArraySequence() : ArraySequence<T>() {}

    ImmutableArraySequence(T *items, int count)
        : ArraySequence<T>(items, count) {}

    ImmutableArraySequence(const DynamicArray<T> &array)
        : ArraySequence<T>(array) {}

    ImmutableArraySequence(const ImmutableArraySequence<T> &other)
        : ArraySequence<T>(other) {}

    // Ключевой метод
    Sequence<T> *Instance()
    {
        return new ImmutableArraySequence<T>(*this);
    }

    // Клонирование
    Sequence<T> *Clone() const
    {
        return new ImmutableArraySequence<T>(*this);
    }

    Sequence<T> *NewEmpty() const
    {
        return new ImmutableArraySequence<T>();
    }
};

#endif
