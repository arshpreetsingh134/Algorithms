// ********* NOT WORKING ********** //

// Greedy algorithm for minimizing the weighted sum of completion times.
// Objective functiin is the difference between weight and length for each Process, i.e., (w-l)
// or the ratio of weight and length, i.e., (w/l)

// Also known as the "Job Sequencing Problem"

// Given the lengths and weights for a Process, we device a greedy algorithm that outputs the optimized
// completion time at the end of execution of all Processes
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Process
{
    long length;
    long weight;

    Process(){}

    Process(long weight, long length)
    {
        this->length = length;
        this->weight = weight;
    }
};

// Objective Function used as a metric for comparison between two Processes
long objectiveFunction1(long a, long b)
{
    return a - b; // Not so effective
}

float objectiveFunction2(long a, long b)
{
    return a * b; // 100% effective
}

// Comparator used in std::sort()
bool compareTwo(Process a, Process b)
{
    long obj1 = objectiveFunction2(a.weight, b.length);
    long obj2 = objectiveFunction2(b.weight, a.length);

    // long obj1 = objectiveFunction1(a.weight, a.length);
    // long obj2 = objectiveFunction1(b.weight, b.length);

    if (obj1 == obj2)
        return a.weight > b.weight;

    return (obj1 > obj2);
}

// Processes are first sorted in decreasing order of objectiveFunction()
// and then weighted sum of completion times is calculated
long totalCompletionTime(vector<Process> &a, int n)
{
    long sum = 0;
    long completionTime=0;

    stable_sort(a.begin(), a.end(), compareTwo);

    // for (long i = 0; i < n; i++)
    //     cout << a[i].weight << " " << a[i].length << endl;

    for (long i = 0; i < n; i++)
    {
        sum += a[i].length; // Completion Time of the current Process i
        completionTime+= a[i].weight * sum;
    }

    return completionTime;
}

int main()
{
    vector<Process> a(20, Process());

    // Reading text from file
    fstream file;
    file.open("C:/Users/ARSHPREET SINGH/Desktop/Algorithms/processes3.txt", ios::in);

    string ss;
    int count = 0;

    while (getline(file, ss))
    {
        string temp = "";

        long splitStr[2];

        int i = 0;

        stringstream s1(ss);

        while (getline(s1, temp, ' '))
        {
            long num;
            stringstream geek(temp);
            geek >> num;
            splitStr[i] = num;
            temp = "";
            i++;
        }

        a[count] = Process(splitStr[0], splitStr[1]);
    
        count++;
    }

    file.close();

    // a[0] = Process(5, 3);
    // a[1] = Process(2, 1);
    // a[2] = Process(8, 10);
    // a[3] = Process(2, 8);
    // a[4] = Process(3, 6);

    cout << "\nTotal Completion Time: " << totalCompletionTime(a, count-1);

    
}