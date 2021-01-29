// Check if a given string is a substring of the other
#include <iostream>
#include <string> // std::find()
using namespace std;

// O(M*N) time and O(1) space
int isSubstring1(string s1, string s2)
{
    int N = s1.size();
    int M = s2.size();

    for (int i = 0; i <= N - M; i++)
    {
        int j;

        for (j = 0; j < M; j++)
        {
            if (s1[i + j] != s2[j])
                break;
        }

        if (j == M)
            return i;
    }
    return -1;
}

// An efficient solution would need only one traversal i.e. O(n) on
// the longer string s1. Here we will start traversing the string s1
// and maintain a pointer for string s2 from 0th index. For each
// iteration we compare the current character in s1 and check it with
// the pointer at s2. If they match we increment the pointer on s2 by 1.
// And for every mismatch we set the pointer back to 0. We also keep a
// check when the s2 pointer value is equal to the length of string s2,
// if true we break and return the value (pointer of string s1 – pointer
// of string s2)
// O(N) time and O(1) space
int isSubstring2(string str, string target)
{
    int t = 0;
    int i;
    for (i = 0; i < str.size(); i++)
    {
        if(t==target.size())
            break;

        if (str[i] == target[t])
            t++;
        else
            t = 0;
    }

    return t < target.size() ? -1 : i-t;
}

int main()
{
    string s1 = "Arshpreet";
    string s2 = "pre";

    cout << "String " << s2 << " is present at index " << isSubstring1(s1, s2) << " in " << s1;
    cout << "\nString " << s2 << " is present at index " << isSubstring2(s1, s2) << " in " << s1;
}