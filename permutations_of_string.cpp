// Calculate all possible permutations of a given string

#include <iostream>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <vector>
using namespace std;

// Method 1: Isolate each element to the side and permute the remaining (n-1) elements
// then append them all (O(n^2 * n!) time)
void permutations(string str, string pre)
{
    if (str.length() == 0)
    {
        cout << pre << " ";
        return;
    }

    for (int i = 0; i < str.length(); i++)
    {
        string rem = str.substr(0, i) + str.substr(i + 1);
        // cout << "\n"
        //      << str.substr(0, i) << " " << str.substr(i + 1)<<" "<<rem;
        permutations(rem, pre + str[i]);
    }
}

void permutations1(string str)
{
    permutations(str, "");
}

// Method 2: Decrease & Conquer: Remove each element from the n elements one at a time,
// then append it to the (n-1)! remaining permutations (O(n!))
void permutations2(string str, int n)
{
    if (n == 1)
    {
        cout << str << " ";
        return;
    }

    for (int i = 0; i < n; i++)
    {
        swap(str[i], str[n - 1]); // remove the i-th element
        permutations2(str, n - 1);
        swap(str[i], str[n - 1]); // restore for the next round
    }
}

// Method 3: Using std::rotate()
void permutations3(string str, int i, int n)
{
    int j = i;
    if (i > n)
    {
        cout << str << " ";
        return;
    }

    string temp = str;

    while (j < str.length())
    {
        str = temp;
        rotate(str.begin() + i, str.begin() + j, str.end());
        permutations3(str, i + 1, n - 1);
        j++;
    }
}

// Method 4: Insert the nth element at all possible locations of the (n-1)! remaining permutations.
// A simple algorithm to use permutations of n-1 elements to generate permutations of n elements recursively.
// For example:
//                     A
//         BA                     AB
//    CBA BCA BAC            CAB ACB ABC
vector<string> permutations4(string str, int n)
{
    vector<string> gen;
    if (n == 1)
    {
        string new_permutation;
        new_permutation.push_back(str[n - 1]);
        gen.push_back(new_permutation);
    }
    else
    {
        vector<string> temp = permutations4(str, n - 1);
        vector<string>::iterator itr = temp.begin();
        while (itr != temp.end())
        {
            string permutation = *itr;

            // create a new permutation with this element in every position)
            for (int i = 0; i <= permutation.length(); i++)
            {
                string new_permutation = permutation;
                string s2(1, str[n - 1]);
                new_permutation.insert(i, s2);
                gen.push_back(new_permutation);
            }
            itr++;
        }
    }
    return gen;
}

// Method 5: Using std::next_permutation()- Lexicographic Ordering
void permutations5(string str)
{
    sort(str.begin(), str.end());

    do
    {
        cout << str << " ";
    } while (next_permutation(str.begin(), str.end()));
}

// Method 6: Using std::rotate()
void permutations6(string str, int i, int n)
{
    int j = i;
    if (i > n)
    {
        cout << str << " ";
        return;
    }

    string temp = str;

    while (j < str.length())
    {
        str = temp;
        rotate(str.begin() + i, str.begin() + j, str.end());
        permutations6(str, i + 1, n - 1);
        j++;
    }
}

int main()
{
    string str = "ABC";
    cout << "First Method: ";
    permutations1(str);

    cout << endl
         << "\nSecond Method: ";
    permutations2(str, str.length());

    cout << endl
         << "\nThird Method: ";
    permutations3(str, 0, str.length());

    cout << endl
         << "\nFourth Method: ";
    vector<string> A = permutations4(str, str.length());
    for (auto i : A)
        cout << i << " ";

    cout << endl
         << "\nFifth Method: ";
    permutations5(str);

    cout << endl
         << "\nSixth Method: ";
    permutations6(str, 0, str.length() - 1);
}