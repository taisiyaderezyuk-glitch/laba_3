#ifndef MUTABLE_LIST_SEQUENCE_H
#define MUTABLE_LIST_SEQUENCE_H

#include "ListSequence.h"

template <class T>
class MutableListSequence : public ListSequence<T>
{
public:
    // Конструкторы
    MutableListSequence() : ListSequence<T>() {}

    MutableListSequence(T *items, int count)
        : ListSequence<T>(items, count) {}

    MutableListSequence(const LinkedList<T> &list)
        : ListSequence<T>(list) {}

    MutableListSequence(const MutableListSequence<T> &other)
        : ListSequence<T>(other) {}

    // Ключевой метод
    Sequence<T> *Instance()
    {
        return this;
    }

    // Клонирование
    Sequence<T> *Clone() const
    {
        return new MutableListSequence<T>(*this);
    }

    Sequence<T> *NewEmpty() const
    {
        return new MutableListSequence<T>();
    }
};

#endif
