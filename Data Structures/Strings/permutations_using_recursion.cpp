// Naive Recursive Algorithm to find all the permutations of a given string. Time Complexity- O(n * n!)

// In this algorithm, we generate all the permutations of a string s0,s1,....sn by chopping of the first
// character s0, and recursively generating all the permutations of the substring s1,s2...,sn. Then once
// we have the permutations of s1,s2,...,sn, we iterate through this list to place the chopped element
// at each possible position inside each permutation of the substring.

// Disadvantage- also prints the duplicate permutations if a character occurs more than once in the
// given string.

#include <iostream>
#include <string.h> // For std::substr()
#include <vector>
using namespace std;

vector<string> permute(string str)
{
    vector<string> temp;    // Stores all possible permutations of str

    // Base Cases
    if (str.size() == 0)
    {
        temp.push_back("");
        return temp;
    }

    if (str.size() == 1)
    {
        temp.push_back(str);
        return temp;
    }

    char ch;

    ch = str[0];

    // Cutting off the first character and recursively computing permutations for the
    // remaining string
    vector<string> substr_set = permute(str.substr(1));

    for (auto s : substr_set)
    {
        // Handling first of the many permutations (in which 'ch' belongs to first position)
        temp.push_back(ch + s);

        // Handling remaining permutations
        for (int j = 1; j <= s.size(); j++)
        {
            temp.push_back(s.substr(0, j) + ch + s.substr(j));
        }
    }

    return temp;
}

int main()
{
    string str = "ABC";
    vector<string> A = permute(str);
    cout << "Permutations of string " << str << " are: ";

    for (auto i : A)
        cout << i << " ";

    cout << "\nTotal no. of permutations: " << A.size();
}