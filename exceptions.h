#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>

class IndexOutOfRange : public std::exception
{
public:
    const char *what() const _NOEXCEPT
    {
        return "Index out of range";
    }
};

class EmptyCollection : public std::exception
{
public:
    const char *what() const _NOEXCEPT
    {
        return "Collection is empty";
    }
};

#endif
