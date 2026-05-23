#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>

#include "Sequence.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"
#include "Stack.h"
#include "Queue.h"
#include "Deque.h"
#include "PriorityQueue.h"

// ---------- Фабрики ----------
Sequence<int> *MakeMutableArray() { return new MutableArraySequence<int>(); }
Sequence<int> *MakeImmutableArray() { return new ImmutableArraySequence<int>(); }
Sequence<int> *MakeMutableList() { return new MutableListSequence<int>(); }
Sequence<int> *MakeImmutableList() { return new ImmutableListSequence<int>(); }

typedef Sequence<int> *(*Factory)();
typedef double (*TestFunc)(Factory, int);

// ---------- Тесты для каждого АТД (без лямбд) ----------

double TestStack(Factory factory, int n)
{
    Stack<int> s(factory());
    clock_t start = clock();
    for (int i = 0; i < n; ++i)
        s.Push(i);
    for (int i = 0; i < n; ++i)
        s.Pop();
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

double TestQueue(Factory factory, int n)
{
    Queue<int> q(factory());
    clock_t start = clock();
    for (int i = 0; i < n; ++i)
        q.Enqueue(i);
    for (int i = 0; i < n; ++i)
        q.Dequeue();
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

double TestDeque(Factory factory, int n)
{
    Deque<int> d(factory());
    clock_t start = clock();
    for (int i = 0; i < n; ++i)
        d.PushBack(i);
    for (int i = 0; i < n; ++i)
        d.PopFront();
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

double TestPriorityQueue(Factory factory, int n)
{
    PriorityQueue<int> pq(factory());
    clock_t start = clock();
    for (int i = 0; i < n; ++i)
        pq.Enqueue(i);
    for (int i = 0; i < n; ++i)
        pq.Dequeue();
    clock_t end = clock();
    return double(end - start) / CLOCKS_PER_SEC;
}

// ---------- Главная функция вывода таблиц ----------
void RunPerformanceComparison()
{
    const int sizes[] = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    const int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    Factory factories[4] = {MakeMutableArray, MakeImmutableArray, MakeMutableList, MakeImmutableList};
    const char *names[4] = {"MutableArray", "ImmutableArray", "MutableList", "ImmutableList"};
    const char *adtNames[4] = {"Stack", "Queue", "Deque", "PriorityQueue"};
    TestFunc tests[4] = {TestStack, TestQueue, TestDeque, TestPriorityQueue};

    std::cout << std::fixed << std::setprecision(6);

    std::ofstream csv("performance.csv");
    if (!csv)
    {
        std::cerr << "Error: cannot create performance.csv\n";
        return;
    }

    csv << std::fixed << std::setprecision(6);
    csv << "ADT,Size,MutableArray,ImmutableArray,MutableList,ImmutableList\n";

    for (int a = 0; a < 4; ++a)
    {
        std::cout << "\n===== " << adtNames[a] << " =====\n";
        std::cout << "Size\t\t";
        for (int f = 0; f < 4; ++f)
            std::cout << names[f] << "\t";
        std::cout << std::endl;

        for (int s = 0; s < numSizes; ++s)
        {
            std::cout << sizes[s] << "\t\t";
            csv << adtNames[a] << "," << sizes[s] << ",";

            for (int f = 0; f < 4; ++f)
            {
                double time = tests[a](factories[f], sizes[s]);
                std::cout << time << "\t";
                csv << time;
                if (f < 3)
                    csv << ",";
            }

            std::cout << std::endl;
            csv << "\n";
        }
    }
    csv.close();

    std::cout << "\nSaved performance.csv\n";
}
