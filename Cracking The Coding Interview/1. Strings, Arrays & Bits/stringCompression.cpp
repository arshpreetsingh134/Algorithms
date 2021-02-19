// String Compression using counts of repeated characters
// E.g.: aabcccccaaa should become a2b1c5a3
#include <iostream>
#include <unordered_map>
#include <sstream>
using namespace std;

// Inefficient Approach: using hashtable (takes O(n+k) space and O(n+k) time, where
// k is the no. of character sequences and O(k) time (O(k^2) time in case of Java)
// is taken for concatenation of the string)
string Compress1(string aa)
{
    string new_str = "";

    unordered_map<char, int> repMap;

    int i;
    for (i = 0; i < aa.size(); i++)
    {
        if (i - 1 >= 0 && aa[i - 1] != aa[i])
        {
            new_str += aa[i - 1] + to_string(repMap[aa[i - 1]]);
            repMap[aa[i - 1]] = 0;
        }

        repMap[aa[i]]++;
    }
    new_str += aa[i - 1] + to_string(repMap[aa[i - 1]]);

    if (new_str.size() > aa.size())
        return aa;

    return new_str;
}

// Efficient Approach: using Output Stream and a variable (takes O(n+k) space 
// [still less because we are NOT using hashtable now] and O(n+k) time)
string Compress2(string name)
{
    ostringstream oss;
    int maxSeq = 0;

    for (int i = 0; i < name.size(); i++)
    {
        maxSeq++;

        // If next character is different than the current
        if (i + 1 >= name.size() || name[i] != name[i + 1])
        {
            oss << name[i];
            oss << maxSeq;
            maxSeq = 0;
        }
    }
    return oss.str().size() < name.size() ? oss.str() : name;
}

// Third Approach in Java

int main()
{
    string str = "aabcccccaaa";
    cout << Compress2(str);
}