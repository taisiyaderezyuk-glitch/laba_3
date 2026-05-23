// PrintSequence.h
#ifndef PRINT_SEQUENCE_H
#define PRINT_SEQUENCE_H

#include <iostream>
#include "Sequence.h" // необходимо для Iterator и Sequence

template <class T>
inline void PrintSequence(const Sequence<T> &seq)
{
    Iterator<T> *it = seq.GetIterator();
    while (it->HasNext())
    {
        std::cout << it->Next() << " ";
    }
    std::cout << std::endl;
    delete it;
}

#endif
