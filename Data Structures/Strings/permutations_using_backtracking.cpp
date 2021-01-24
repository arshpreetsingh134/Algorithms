// Backtracking Algorithm to find all the permutations (including duplicates) of a given string.
// Time Complexity - still O(n * n!), but at the expanse of no extra space! (in-place)

#include <iostream>
#include <algorithm>
using namespace std;

void permute(string &s, int l, int r)
{
    // Base Case (when there are no more characters left to swap)
    if (l == r)
    {
        cout << s << " ";
        return;
    }

    for (int i = l; i <= r; i++)
    {
        // Swapping
        swap(s[l], s[i]);

        // Recursing
        permute(s, l + 1, r);

        // Backtracking (to retain original order)
        swap(s[l], s[i]);
    }
}

int main()
{
    string s = "ABC";
    cout << "Permutations of string " << s << " are: ";
    permute(s, 0, s.size() - 1);

    cout << "\nOriginal String: " << s;
    // For printing the permutations in lexicographical order, make sure the
    // string itself is sorted initially.
}