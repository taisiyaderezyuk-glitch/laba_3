#ifndef IMMUTABLE_LIST_SEQUENCE_H
#define IMMUTABLE_LIST_SEQUENCE_H

#include "ListSequence.h"

template <class T>
class ImmutableListSequence : public ListSequence<T>
{
public:
    // Конструкторы
    ImmutableListSequence() : ListSequence<T>() {}

    ImmutableListSequence(T *items, int count)
        : ListSequence<T>(items, count) {}

    ImmutableListSequence(const LinkedList<T> &list)
        : ListSequence<T>(list) {}

    ImmutableListSequence(const ImmutableListSequence<T> &other)
        : ListSequence<T>(other) {}

    // Ключевой метод
    Sequence<T> *Instance()
    {
        return new ImmutableListSequence<T>(*this);
    }

    // Клонирование
    Sequence<T> *Clone() const
    {
        return new ImmutableListSequence<T>(*this);
    }

    Sequence<T> *NewEmpty() const
    {
        return new ImmutableListSequence<T>();
    }
};

#endif
