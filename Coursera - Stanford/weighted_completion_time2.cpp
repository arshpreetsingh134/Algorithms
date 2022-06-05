// Greedy algorithm for minimizing the weighted sum of completion times.
// Objective functiin is the difference between weight and length for each Process, i.e., (w-l)
// or the ratio of weight and length, i.e., (w/l)

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#define arr(i) i.begin(), i.end()

using namespace std;

typedef pair<long, pair<long, long>> job;      // (Job Index, Weight, Length)

bool cmpFunc(job j1, job j2)
{
    long w1, l1, w2, l2;

    w1 = j1.second.first;
    l1 = j1.second.second;
    w2 = j2.second.first;
    l2 = j2.second.second;

    // if ((w1 - l1) == (w2 - l2))
    //     return w1 > w2;
    // return (w1 - l1) > (w2 - l2);

    if((w1*l2)==(w2*l1))
        return w1>w2;
    return (w1*l2) > (w2*l1);
}

long printOptimal(long W[], long L[], long N)
{
    long sum = 0;
    long completionTime = 0;

    vector<job> jobs;

    for(long i=0; i<N; i++)
    {
        long l = L[i];
        long w = W[i];

        jobs.push_back(make_pair(i+1, make_pair(w,l)));
    }

    stable_sort(arr(jobs), cmpFunc);

    // for(auto i:jobs)
    // {
    //     cout<<i.second.first<<" "<<i.second.second<<endl;
    // }

    for (long i = 0; i < N; i++)
    {
        sum += jobs[i].second.second; // Completion Time of the current Process i
        completionTime += jobs[i].second.first * sum;
    }

    return completionTime;
}

int main()
{
    // long Length[] = {5,2};
    // long Weight[] = {3,1};

    // long N = sizeof(Length) / sizeof(Length[0]);
    // cout<<"\nCompletion Time: "<<prlongOptimal(Length, Weight, N);

    long N = 20;
    long Length[N];
    long Weight[N];

    // Reading text from file
    fstream file;
    file.open("C:/Users/ARSHPREET SINGH/Desktop/Algorithms/processes3.txt", ios::in);

    string ss;
    long count = 0;

    while (getline(file, ss))
    {
        string temp = "";

        long splitStr[2];

        long i = 0;

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

        Weight[count] = splitStr[0];
        Length[count] = splitStr[1];

        count++;
    }

    file.close();

    cout << "\nCompletion Time: " << printOptimal(Weight, Length, N);
}