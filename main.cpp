#include <iostream>
#include <limits>
#include <ctime>

#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include "PriorityQueue.h"
#include "PrintSequence.h"
#include "PerformanceTest.h"

void RunAllTests();

// Утилиты
Sequence<int> *CreateSequence(int type)
{
    switch (type)
    {
    case 1:
        return new MutableArraySequence<int>();
    case 2:
        return new ImmutableArraySequence<int>();
    case 3:
        return new MutableListSequence<int>();
    case 4:
        return new ImmutableListSequence<int>();
    default:
        return new MutableArraySequence<int>();
    }
}

int ChooseSequenceType()
{
    int t;
    std::cout << "Choose underlying sequence:\n"
              << "1. MutableArray\n2. ImmutableArray\n3. MutableList\n4. ImmutableList\n> ";
    std::cin >> t;
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return 1;
    }
    return t;
}

// Демонстрации
void DemoStack()
{
    int type = ChooseSequenceType();
    Stack<int> stack(CreateSequence(type));

    int choice, val;
    do
    {
        std::cout << "\n--- Stack Menu ---\n"
                  << "1. Push\n2. Pop\n3. Top\n4. Print\n0. Back\n> ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            std::cout << "Value: ";
            std::cin >> val;
            stack.Push(val);
            break;
        case 2:
            if (!stack.IsEmpty())
                std::cout << "Popped: " << stack.Pop() << std::endl;
            else
                std::cout << "Stack is empty\n";
            break;
        case 3:
            if (!stack.IsEmpty())
                std::cout << "Top: " << stack.Top() << std::endl;
            else
                std::cout << "Stack is empty\n";
            break;
        case 4:
            std::cout << "Stack (top to bottom): ";
            PrintSequence(*stack.GetSequence());
            break;
        }
    } while (choice != 0);
}

void DemoQueue()
{
    int type = ChooseSequenceType();
    Queue<int> queue(CreateSequence(type));

    int choice, val;
    do
    {
        std::cout << "\n--- Queue Menu ---\n"
                  << "1. Enqueue\n2. Dequeue\n3. Front\n4. Print\n0. Back\n> ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            std::cout << "Value: ";
            std::cin >> val;
            queue.Enqueue(val);
            break;
        case 2:
            if (!queue.IsEmpty())
                std::cout << "Dequeued: " << queue.Dequeue() << std::endl;
            else
                std::cout << "Queue is empty\n";
            break;
        case 3:
            if (!queue.IsEmpty())
                std::cout << "Front: " << queue.Front() << std::endl;
            else
                std::cout << "Queue is empty\n";
            break;
        case 4:
            std::cout << "Queue (front to back): ";
            PrintSequence(*queue.GetSequence());
            break;
        }
    } while (choice != 0);
}

void DemoDeque()
{
    int type = ChooseSequenceType();
    Deque<int> deq(CreateSequence(type));

    int choice, val;
    do
    {
        std::cout << "\n--- Deque Menu ---\n"
                  << "1. PushFront\n2. PushBack\n"
                  << "3. PopFront\n4. PopBack\n"
                  << "5. Front\n6. Back\n7. Print\n0. Back\n> ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            std::cout << "Value: ";
            std::cin >> val;
            deq.PushFront(val);
            break;
        case 2:
            std::cout << "Value: ";
            std::cin >> val;
            deq.PushBack(val);
            break;
        case 3:
            if (!deq.IsEmpty())
                std::cout << "PopFront: " << deq.PopFront() << std::endl;
            else
                std::cout << "Deque is empty\n";
            break;
        case 4:
            if (!deq.IsEmpty())
                std::cout << "PopBack: " << deq.PopBack() << std::endl;
            else
                std::cout << "Deque is empty\n";
            break;
        case 5:
            if (!deq.IsEmpty())
                std::cout << "Front: " << deq.Front() << std::endl;
            else
                std::cout << "Deque is empty\n";
            break;
        case 6:
            if (!deq.IsEmpty())
                std::cout << "Back: " << deq.Back() << std::endl;
            else
                std::cout << "Deque is empty\n";
            break;
        case 7:
            std::cout << "Deque (front to back): ";
            PrintSequence(*deq.GetSequence());
            break;
        }
    } while (choice != 0);
}

void DemoPriorityQueue()
{
    PriorityQueue<int> pq;
    int choice, val;
    do
    {
        std::cout << "\n--- PriorityQueue Menu ---\n"
                  << "1. Enqueue\n2. Dequeue\n3. Peek\n4. Print\n0. Back\n> ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            std::cout << "Value: ";
            std::cin >> val;
            pq.Enqueue(val);
            break;
        case 2:
            if (!pq.IsEmpty())
                std::cout << "Dequeued: " << pq.Dequeue() << std::endl;
            else
                std::cout << "PriorityQueue is empty\n";
            break;
        case 3:
            if (!pq.IsEmpty())
                std::cout << "Peek: " << pq.Peek() << std::endl;
            else
                std::cout << "PriorityQueue is empty\n";
            break;
        case 4:
            std::cout << "PriorityQueue (ordered by priority): ";
            PrintSequence(*pq.GetSequence());
            break;
        }
    } while (choice != 0);
}

static int SquareFunc(int x) { return x * x; }
static bool IsEvenFunc(int x) { return x % 2 == 0; }
static int SumFunc(int a, int b) { return a + b; }

void DemoFunctional()
{
    int arr[] = {1, 2, 3, 4, 5};
    ImmutableArraySequence<int> seq(arr, 5);
    std::cout << "Original: ";
    PrintSequence(seq);

    Sequence<int> *mapped = seq.Map(SquareFunc);
    std::cout << "map(x^2): ";
    PrintSequence(*mapped);
    delete mapped;

    Sequence<int> *filtered = seq.Where(IsEvenFunc);
    std::cout << "where(even): ";
    PrintSequence(*filtered);
    delete filtered;

    int total = seq.Reduce(SumFunc, 0);
    std::cout << "reduce(sum, 0): " << total << std::endl;
}

void DemoPerformance()
{
    const int N = 10000;
    std::cout << "Performance comparison for Concat of two sequences of length " << N << ":\n";

    MutableArraySequence<int> arrSeq;
    MutableListSequence<int> listSeq;
    for (int i = 0; i < N; ++i)
    {
        arrSeq.Append(i);
        listSeq.Append(i);
    }

    clock_t start = std::clock();
    Sequence<int> *concatArr = arrSeq.Concat(arrSeq);
    clock_t end = std::clock();
    double arrTime = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "ArraySequence concat: " << arrTime << " s\n";
    delete concatArr;

    start = std::clock();
    Sequence<int> *concatList = listSeq.Concat(listSeq);
    end = std::clock();
    double listTime = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "ListSequence concat: " << listTime << " s\n";
    delete concatList;
}

void Menu()
{
    std::cout << "\n========== MAIN MENU ==========\n"
              << "1. Stack\n"
              << "2. Queue\n"
              << "3. Deque\n"
              << "4. PriorityQueue\n"
              << "5. Functional (Map/Where/Reduce)\n"
              << "6. Performance comparison\n"
              << "7. Run all tests\n"
              << "0. Exit\n";
}

int main()
{
    int choice;
    do
    {
        Menu();
        std::cout << "Choose: ";
        std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            DemoStack();
            break;
        case 2:
            DemoQueue();
            break;
        case 3:
            DemoDeque();
            break;
        case 4:
            DemoPriorityQueue();
            break;
        case 5:
            DemoFunctional();
            break;
        case 6:
            RunPerformanceComparison();
            break;
        case 7:
            RunAllTests();
            break;
        case 0:
            std::cout << "Exiting.\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
