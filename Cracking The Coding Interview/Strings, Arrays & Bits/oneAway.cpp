// Check all possible strings that are one edit away by testing the REMOVAL of each character,
// testing the REPLACEMENT of each character and testing the INSERTION of each possible character
// E.g.: pale, ple --> true
// pale, bale --> true
// pale, bae --> false

#include <iostream>
#include <cmath>
using namespace std;

// Function that handles both insert & delete
// Here, len(first) < len(second)
bool oneEditInsert(string first, string second)
{
    int i1 = 0;
    int i2 = 0;
    while (i1 < first.size() && i2 < second.size())
    {
        if (first[i1] != second[i2])
        {
            if (i1 != i2)
                return false;
            i2++; // To match the shorter string's index
        }

        else
        {
            i1++;
            i2++;
        }
    }
    return true;
}

// Function that handles replace
bool oneEditReplace(string first, string second)
{
    bool foundDiff = false;
    int i = 0;
    while (i < first.size())
    {
        if (first[i] != second[i])
        {
            if (foundDiff)
                return false;

            foundDiff = true;
        }
        i++;
    }
    return true;
}

bool oneEditAway1(string first, string second)
{
    if (first.size() == second.size())
        return oneEditReplace(first, second); // Replace Case
    else if (first.size() > second.size())
        return oneEditInsert(second, first); // Delete Case
    else
        return oneEditInsert(first, second); // Insert Case
}

// Method 2: Merging all the operations into one method
bool oneEditAway2(string first, string second)
{

    if (abs((int)(first.size() - second.size())) > 1)
        return false; // Because at max, one diff is allowed

    // Differentiate the shorter and longer strings
    string s1 = first.size() > second.size() ? first : second; // Longer String
    string s2 = first.size() > second.size() ? second : first; // Shorter String

    bool foundDiff = false;
    int i1 = 0;
    int i2 = 0;

    while (i2 < s2.size() && i1<s1.size())
    {
        if (s1[i1] != s2[i2])
        {
            // Ensure that this is the first difference found
            if (foundDiff)
                return false;
            foundDiff = true;

            if (s1.size() == s2.size()) // On replace, for strings having same length, move the shorter pointer
                i2++;
        }
        else
            i2++; // If characters matching, move shorter pointer

        i1++; // Always move the longer pointer
    }
    return true;
}

int main()
{
    string first = "pale", second = "pals";

    if (oneEditAway1(first, second))
        cout << first << " and " << second << " are one edit away.";
    else
        cout << first << " and " << second << " are more than one edits away.";
}