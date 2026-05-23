#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "exceptions.h"
#include "Sequence.h" // для базового класса Iterator<T>

template <class T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node *prev;

        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node *head;
    Node *tail;
    int size;

    // Вспомогательный метод поиска узла по индексу (с оптимизацией обхода)
    Node *GetNode(int index) const
    {
        if (index < 0 || index >= size)
            throw IndexOutOfRange();

        Node *current;
        if (index < size / 2) // ближе к голове
        {
            current = head;
            for (int i = 0; i < index; i++)
                current = current->next;
        }
        else // ближе к хвосту
        {
            current = tail;
            for (int i = size - 1; i > index; i--)
                current = current->prev;
        }
        return current;
    }

public:
    // ----- Вложенный итератор -----
    class ListIterator : public Iterator<T>
    {
        const LinkedList<T> &list;
        Node *current;

    public:
        ListIterator(const LinkedList<T> &l) : list(l), current(l.head) {}
        bool HasNext() const { return current != nullptr; }
        T Next()
        {
            T val = current->data;
            current = current->next;
            return val;
        }
    };

    // ----- Конструкторы -----
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    LinkedList(T *items, int count) : head(nullptr), tail(nullptr), size(0)
    {
        for (int i = 0; i < count; i++)
            Append(items[i]);
    }

    LinkedList(const LinkedList<T> &other) : head(nullptr), tail(nullptr), size(0)
    {
        Node *current = other.head;
        while (current)
        {
            Append(current->data);
            current = current->next;
        }
    }

    // ----- Оператор присваивания -----
    LinkedList<T> &operator=(const LinkedList<T> &other)
    {
        if (this == &other)
            return *this;

        // очистка
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }

        head = tail = nullptr;
        size = 0;

        // копирование
        Node *current = other.head;
        while (current)
        {
            Append(current->data);
            current = current->next;
        }

        return *this;
    }

    // ----- Деструктор -----
    ~LinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // ----- Методы доступа -----
    int GetLength() const
    {
        return size;
    }

    T GetFirst() const
    {
        if (!head)
            throw EmptyCollection();
        return head->data;
    }

    T GetLast() const
    {
        if (!tail)
            throw EmptyCollection();
        return tail->data;
    }

    T Get(int index) const
    {
        return GetNode(index)->data; // использует общий метод поиска
    }

    // ----- Модификация -----
    void Append(T item)
    {
        Node *node = new Node(item);

        if (!tail)
        {
            head = tail = node;
        }
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }

        size++;
    }

    void Prepend(T item)
    {
        Node *node = new Node(item);

        if (!head)
        {
            head = tail = node;
        }
        else
        {
            node->next = head;
            head->prev = node;
            head = node;
        }

        size++;
    }

    void InsertAt(T item, int index)
    {
        if (index < 0 || index > size)
            throw IndexOutOfRange();

        if (index == 0)
        {
            Prepend(item);
            return;
        }

        if (index == size)
        {
            Append(item);
            return;
        }

        Node *current = GetNode(index); // используем общий метод

        Node *node = new Node(item);

        node->prev = current->prev;
        node->next = current;

        current->prev->next = node;
        current->prev = node;

        size++;
    }

    void RemoveAt(int index)
    {
        Node *node = GetNode(index); // используем общий метод поиска

        if (node->prev)
            node->prev->next = node->next;
        else
            head = node->next; // удаляется голова

        if (node->next)
            node->next->prev = node->prev;
        else
            tail = node->prev; // удаляется хвост

        delete node;
        size--;
    }

    LinkedList<T> *GetSublist(int start, int end) const
    {
        if (start < 0 || end >= size || start > end)
            throw IndexOutOfRange();

        LinkedList<T> *result = new LinkedList<T>();

        Node *current = GetNode(start); // начинаем с нужного узла
        for (int i = start; i <= end; i++)
        {
            result->Append(current->data);
            current = current->next;
        }

        return result;
    }

    // ----- Фабрика итератора -----
    Iterator<T> *GetIterator() const
    {
        return new ListIterator(*this);
    }
};

#endif // LINKED_LIST_H
