// Displaying permutations of a string in a lexicographical order using STL

#include <iostream>
#include <algorithm>        // for std::next_permutation and std::sort
using namespace std;

// First Method - using std::rotate()
void permute_using_rotate(string str, string out)
{
    // When size of str becomes 0, out has a
    // permutation (length of out is n)
    if (str.size() == 0)
    {
        cout << out << " ";
        return;
    }

    // One be one move all characters at
    // the beginning of out (or result)
    for (int i = 0; i < str.size(); i++)
    {
        // Remove first character from str and
        // add it to out
        permute_using_rotate(str.substr(1), out + str[0]);

        // Rotate string in a way second character
        // moves to the beginning.
        rotate(str.begin(), str.begin() + 1, str.end());
    }
}

// Second Method - using std::next_permutation()
void permute(string str)
{
    // First sort, to display the lexicographical order
    sort(str.begin(), str.end());

    do
    {
        cout<<str<<" ";
    }while (next_permutation(str.begin(), str.end()));
}

int main()
{
    string s = "BAC";
    cout << "\nSorted Permutations of string ***" << s << "*** using std::next_permutation() are: ";
    permute(s);

    cout << "\nPermutations of string ***" << s << "*** using std::rotate() are: ";
    permute_using_rotate(s, "");
}