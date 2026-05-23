#include <iostream>
#include <cassert>

#include "DynamicArray.h"
#include "LinkedList.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include "PriorityQueue.h"
#include "PrintSequence.h"

// Вспомогательные функции для функциональных тестов
int square(int x) { return x * x; }
bool isEven(int x) { return x % 2 == 0; }
int sum(int a, int b) { return a + b; }

void TestDynamicArray()
{
    int arr[] = {1, 2, 3};
    DynamicArray<int> da(arr, 3);
    assert(da.GetSize() == 3);
    assert(da.Get(0) == 1);
    assert(da.Get(2) == 3);

    da.Resize(5);
    assert(da.GetSize() == 5);
    da.Set(3, 10);
    assert(da.Get(3) == 10);

    std::cout << "DynamicArray tests passed\n";
}

void TestLinkedList()
{
    int arr[] = {1, 2, 3};
    LinkedList<int> list(arr, 3);
    assert(list.GetLength() == 3);
    assert(list.GetFirst() == 1);
    assert(list.GetLast() == 3);

    list.Append(4);
    assert(list.GetLast() == 4);
    list.Prepend(0);
    assert(list.GetFirst() == 0);

    std::cout << "LinkedList tests passed\n";
}

void TestMutableArraySequence()
{
    int arr[] = {1, 2, 3};
    MutableArraySequence<int> seq(arr, 3);
    Sequence<int> *result = seq.Append(4);
    assert(seq.GetLength() == 4);
    assert(seq.GetLast() == 4);
    assert(result == &seq);
    std::cout << "MutableArraySequence tests passed\n";
}

void TestImmutableArraySequence()
{
    int arr[] = {1, 2, 3};
    ImmutableArraySequence<int> seq(arr, 3);
    Sequence<int> *result = seq.Append(4);
    assert(seq.GetLength() == 3);
    assert(result->GetLength() == 4);
    assert(result->GetLast() == 4);
    delete result;
    std::cout << "ImmutableArraySequence tests passed\n";
}

void TestMutableListSequence()
{
    int arr[] = {1, 2, 3};
    MutableListSequence<int> seq(arr, 3);
    Sequence<int> *result = seq.Append(4);
    assert(seq.GetLength() == 4);
    assert(seq.GetLast() == 4);
    assert(result == &seq);
    std::cout << "MutableListSequence tests passed\n";
}

void TestImmutableListSequence()
{
    int arr[] = {1, 2, 3};
    ImmutableListSequence<int> seq(arr, 3);
    Sequence<int> *result = seq.Append(4);
    assert(seq.GetLength() == 3);
    assert(result->GetLength() == 4);
    assert(result->GetLast() == 4);
    delete result;
    std::cout << "ImmutableListSequence tests passed\n";
}

void TestNegativeCases()
{
    try
    {
        int arr[] = {1, 2, 3};
        MutableArraySequence<int> seq(arr, 3);
        seq.Get(5);
        assert(false && "Get(5) should throw IndexOutOfRange");
    }
    catch (const IndexOutOfRange &)
    {
    }

    try
    {
        MutableListSequence<int> emptySeq;
        emptySeq.GetFirst();
        assert(false && "GetFirst on empty should throw EmptyCollection");
    }
    catch (const EmptyCollection &)
    {
    }

    try
    {
        int arr[] = {1, 2};
        ImmutableArraySequence<int> seq(arr, 2);
        seq.InsertAt(10, 5);
        assert(false && "InsertAt with bad index should throw");
    }
    catch (const IndexOutOfRange &)
    {
    }

    try
    {
        ImmutableListSequence<int> seq;
        seq.RemoveAt(0);
        assert(false && "RemoveAt on empty should throw");
    }
    catch (const IndexOutOfRange &)
    {
    }

    std::cout << "Negative tests passed\n";
}

void TestPolymorphism()
{
    int arr[] = {1, 2, 3};
    MutableArraySequence<int> arrSeq(arr, 3);
    PrintSequence(arrSeq); // ссылка

    ImmutableListSequence<int> listSeq(arr, 3);
    PrintSequence(listSeq); // ссылка

    std::cout << "Polymorphism tests passed\n";
}

void TestStack()
{
    Stack<int> s(new MutableArraySequence<int>());
    assert(s.IsEmpty());
    s.Push(10);
    s.Push(20);
    assert(s.Top() == 20);
    assert(s.Pop() == 20);
    assert(s.Pop() == 10);
    assert(s.IsEmpty());

    try
    {
        s.Pop();
        assert(false);
    }
    catch (const EmptyCollection &)
    {
    }

    Stack<int> s2(new ImmutableArraySequence<int>());
    s2.Push(5);
    assert(s2.Top() == 5);

    std::cout << "Stack tests passed\n";
}

void TestQueue()
{
    Queue<int> q(new MutableListSequence<int>());
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    assert(q.Front() == 1);
    assert(q.Dequeue() == 1);
    assert(q.Dequeue() == 2);
    assert(q.Front() == 3);
    assert(q.Dequeue() == 3);
    assert(q.IsEmpty());

    try
    {
        q.Dequeue();
        assert(false);
    }
    catch (const EmptyCollection &)
    {
    }

    std::cout << "Queue tests passed\n";
}

void TestDeque()
{
    Deque<int> d(new MutableArraySequence<int>());
    d.PushBack(1);
    d.PushFront(2);
    assert(d.Front() == 2);
    assert(d.Back() == 1);
    assert(d.PopFront() == 2);
    assert(d.PopBack() == 1);
    assert(d.IsEmpty());

    std::cout << "Deque tests passed\n";
}

void TestPriorityQueue()
{
    PriorityQueue<int> pq;
    pq.Enqueue(5);
    pq.Enqueue(10);
    pq.Enqueue(3);
    assert(pq.Dequeue() == 10);
    assert(pq.Dequeue() == 5);
    assert(pq.Dequeue() == 3);
    assert(pq.IsEmpty());

    pq.Enqueue(4);
    pq.Enqueue(4);
    int first = pq.Dequeue();
    int second = pq.Dequeue();
    assert((first == 4 && second == 4));

    std::cout << "PriorityQueue tests passed\n";
}

void TestFunctional()
{
    int arr[] = {1, 2, 3, 4, 5};
    ImmutableArraySequence<int> seq(arr, 5);

    Sequence<int> *mapped = seq.Map(square);
    assert(mapped->GetLength() == 5);
    assert(mapped->Get(0) == 1);
    assert(mapped->Get(3) == 16);
    delete mapped;

    Sequence<int> *filtered = seq.Where(isEven);
    assert(filtered->GetLength() == 2);
    assert(filtered->Get(0) == 2);
    assert(filtered->Get(1) == 4);
    delete filtered;

    int result = seq.Reduce(sum, 0);
    assert(result == 15);

    std::cout << "Functional tests passed\n";
}

void RunAllTests()
{
    TestDynamicArray();
    TestLinkedList();
    TestMutableArraySequence();
    TestImmutableArraySequence();
    TestMutableListSequence();
    TestImmutableListSequence();
    TestNegativeCases();
    TestPolymorphism();
    TestStack();
    TestQueue();
    TestDeque();
    TestPriorityQueue();
    TestFunctional();
    std::cout << "\nALL TESTS PASSED\n";
}
