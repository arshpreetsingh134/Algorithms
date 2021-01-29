#include <iostream>
#include <algorithm>
#define SET_LEN 128
using namespace std;

// Using Sorting- O(n log n) time
bool checkPermute1(string s1, string s2)
{
    if (s1.size() != s2.size())
        return false;

    sort(s1.begin(), s1.end());
    sort(s2.begin(), s2.end());

    for (int i = 0; i < s1.size(); i++)
        if (s1[i] != s2[i])
            return false;

    return true;
}

// Using Hash Table (or array)- O(n) time and O(1) space
// Assuming there are only 128 characters in the set
bool checkPermute2(string s1, string s2)
{
    int count1[SET_LEN] = {0};
    int count2[SET_LEN] = {0};

    int i;

    // For each character in input strings,
    // increment count in the corresponding
    // count array
    for (i = 0; s1[i] && s2[i]; i++)
    {
        count1[s1[i]]++;
        count2[s2[i]]++;
    }

    // If both strings are of different length.
    // Removing this condition will make the
    // program fail for strings like "aaca"
    // and "aca"
    if (s1[i] || s2[i])
        return false;

    for (int i = 0; i < SET_LEN; i++)
        if (count1[i] != count2[i])
            return false;

    return true;
}

int main()
{
    string s1 = "ABCD";
    string s2 = "BCAD";

    if (checkPermute1(s1, s2))
        cout << "YES!";
    else
        cout << "NOPE!";

    //**************************//

    if (checkPermute2(s1, s2))
        cout << " YES!";
    else
        cout << " NOPE!";
}