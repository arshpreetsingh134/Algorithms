//  Greedy algorithm for minimizing the weighted sum of completion times.
// Objective functiin is the difference between weight and length for each process, i.e., (w-l)
// or the ratio of weight and length, i.e., (w/l)
// Given the lengths and weights for a process, we device a greedy algorithm that outputs the optimized
// completion time at the end of execution of all processes

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Process
{
    long length;
    long weight;
};

// Objective Function used as a metric for comparison between two processes
float objectiveFunction(long a, long b)
{
    // return a-b;       // Not so effective   

    return a/b;          // 100% effective
}

// Comparator used in std::sort()
bool compareTwo(Process a, Process b)
{
    return (objectiveFunction(a.weight, a.length) > objectiveFunction(b.weight, b.length));
}

// Processes are first sorted in decreasing order of objectiveFunction()
// and then weighted sum of completion times is calculated
long totalCompletionTime(Process a[], int n)
{
    long sum = 0;
    long completionTime = 0;

    sort(a, a + n, compareTwo);

    for (long i = 0; i < n; i++)
    {
        sum += a[i].length;         // Completion Time of the current process i
        completionTime += a[i].weight * sum;
    }

    return completionTime;
}

int main()
{
    int n = 2;      // No. of processes to be evaluated

    Process a[n];

    a[0].length = 5;
    a[0].weight = 3;

    a[1].length = 2;
    a[1].weight = 1;


    for (int i = 0; i < n; i++)
    {
        cout << a[i].length << " " << a[i].weight;
        cout << "\n";
    }

    cout << "\nTotal Completion Time: " << totalCompletionTime(a, n);

    return 0;
}