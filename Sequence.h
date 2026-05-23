#ifndef SEQUENCE_H
#define SEQUENCE_H

// Абстрактный итератор
template <class T>
class Iterator
{
public:
    virtual ~Iterator() {}
    virtual bool HasNext() const = 0;
    virtual T Next() = 0;
};

// Абстрактная последовательность
template <class T>
class Sequence
{
protected:
    virtual void AddInternal(T item) = 0;

public:
    virtual ~Sequence() {}

    virtual int GetLength() const = 0;
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;

    virtual Sequence<T> *Append(T item) = 0;
    virtual Sequence<T> *Prepend(T item) = 0;
    virtual Sequence<T> *InsertAt(T item, int index) = 0;
    virtual Sequence<T> *RemoveAt(int index) = 0;
    virtual Sequence<T> *Concat(const Sequence<T> &other) = 0;
    virtual Sequence<T> *GetSubsequence(int start, int end) = 0;

    virtual Sequence<T> *Instance() = 0;
    virtual Sequence<T> *Clone() const = 0;
    virtual Sequence<T> *NewEmpty() const = 0;

    virtual Iterator<T> *GetIterator() const = 0;

    // Map, Where, Reduce остаются без изменений
    template <typename Func>
    Sequence<T> *Map(Func f) const
    {
        Sequence<T> *result = this->NewEmpty();
        Iterator<T> *it = this->GetIterator();
        while (it->HasNext())
            result->AddInternal(f(it->Next()));
        delete it;
        return result;
    }

    template <typename Predicate>
    Sequence<T> *Where(Predicate pred) const
    {
        Sequence<T> *result = this->NewEmpty();
        Iterator<T> *it = this->GetIterator();
        while (it->HasNext())
        {
            T val = it->Next();
            if (pred(val))
                result->AddInternal(val);
        }
        delete it;
        return result;
    }

    template <typename Func>
    T Reduce(Func f, T init) const
    {
        T accumulator = init;
        Iterator<T> *it = this->GetIterator();
        while (it->HasNext())
        {
            accumulator = f(accumulator, it->Next());
        }
        delete it;
        return accumulator;
    }
};

#endif
