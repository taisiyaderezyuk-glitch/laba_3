#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include "exceptions.h"
#include "Sequence.h"

template <class T>
class DynamicArray
{
private:
    T *data;
    int size;

    // Конструктор, забирающий владение массивом
    DynamicArray(T *array, int size, bool)
    {
        this->data = array;
        this->size = size;
    }

public:
    class ArrayIterator : public Iterator<T>
    {
        const DynamicArray<T> &arr;
        int index;

    public:
        ArrayIterator(const DynamicArray<T> &a) : arr(a), index(0) {}
        bool HasNext() const { return index < arr.size; }
        T Next() { return arr.data[index++]; }
    };

    // Конструкторы
    DynamicArray(int size)
    {
        if (size < 0)
            throw IndexOutOfRange();
        this->size = size;
        data = new T[size];
    }

    DynamicArray(T *items, int count)
    {
        if (count < 0)
            throw IndexOutOfRange();
        size = count;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = items[i];
    }

    DynamicArray(const DynamicArray<T> &other)
    {
        size = other.size;
        data = new T[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
    }

    // Оператор присваивания
    DynamicArray<T> &operator=(const DynamicArray<T> &other)
    {
        if (this == &other)
            return *this;

        delete[] data;

        size = other.size;
        data = new T[size];

        for (int i = 0; i < size; i++)
            data[i] = other.data[i];

        return *this;
    }

    // Деструктор
    ~DynamicArray()
    {
        delete[] data;
    }

    // Методы доступа
    int GetSize() const
    {
        return size;
    }

    T Get(int index) const
    {
        if (index < 0 || index >= size)
            throw IndexOutOfRange();
        return data[index];
    }

    void Set(int index, T value)
    {
        if (index < 0 || index >= size)
            throw IndexOutOfRange();
        data[index] = value;
    }

    void Resize(int newSize)
    {
        if (newSize < 0)
            throw IndexOutOfRange();

        T *newData = new T[newSize];
        int minSize = (newSize < size) ? newSize : size;

        for (int i = 0; i < minSize; i++)
            newData[i] = data[i];

        delete[] data;
        data = newData;
        size = newSize;
    }

    DynamicArray<T> *GetSubarray(int start, int end) const
    {
        if (start < 0 || end >= size || start > end)
            throw IndexOutOfRange();

        int newSize = end - start + 1;
        T *newData = new T[newSize];

        for (int i = 0; i < newSize; i++)
            newData[i] = data[start + i];

        return new DynamicArray<T>(newData, newSize, true);
    }

    Iterator<T> *GetIterator() const
    {
        return new ArrayIterator(*this);
    }
};

#endif
