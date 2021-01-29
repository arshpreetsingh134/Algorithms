// Program to check whether the given string is a permutation of a palindrome- O(n) time, O(n) space
// Input: "Tact coa"  ---> Palindromes: "taco cat", "atco cta"
// Output: Yes

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <bitset>
#define MAX 128
using namespace std;

// Solution 1 (Hash Table- O(n) time & O(n) space)
bool PalindromePermutation1(string str)
{
    // 1. Convert to lowercase
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    // 2. Remove White Spaces
    str.erase(remove(str.begin(), str.end(), ' '), str.end());

    unordered_map<char, int> ch_map;
    int countOdd = 0;

    cout << str << endl;

    // Populate the Hash Table with frequencies of each character
    for (auto ch : str)
        ch_map[ch]++;

    int flag = 0; // To check if there are no more than one odd frequencies
    for (auto i : ch_map)
    {
        if (i.second % 2 != 0)
        {
            flag++;
            // Check if there are more than one odd frequencies in the table
            // If yes, that means palindrome is not possible
            if (flag > 1)
                return false;
        }
    }

    // If flag remains 1, return true
    return true;
}

// Solution 2 (Slightly more optimized: utilizing a single loop instead of 3)
// Still O(n) time & O(n) space
bool PalindromePermutation2(string str)
{
    // 1. Convert to lowercase
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    // 2. Remove White Spaces
    // str.erase(remove(str.begin(), str.end(), ' '), str.end());

    unordered_map<char, int> ch_map;
    int countOdd = 0;

    cout << str << endl;

    // Populate the Hash Table with frequencies of each character
    for (auto ch : str)
    {
        if (ch != ' ') // Ignore white spaces
        // (notice how we used the if-condition instead of std::remove())
        {
            ch_map[ch]++;

            // (COMMENT FROM HERE)
            if (ch_map[ch] % 2 == 1)
                countOdd++;
            else
                countOdd--;
        }
    }
    return countOdd <= 1;
}

// Solution 3 (Space Optimized- constant space- O(1))
// Using Bitmasking (max space consumed = 32 bits for int)
bool PalindromePermutation3(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    // Define a Bitmask
    int counter = 0;
    for (auto ch : str)
    {
        if (ch == ' ')
            continue;
        int val = ch - 'a';
        counter ^= 1 << val; // For toggling b/w 0 & 1
    }

    // 00010000 - 1 = 00001111
    // 00010000 & 00001111 = 0
    // If this amounts to 0, it means no more than 1 odd frequencies exist
    if (!((counter - 1) & counter))
        return true;
    return false;
}

int main()
{
    string str = "cato catoo";
    if (PalindromePermutation3(str))
        cout << "Yes! " << str << " is a permutation of a palindrome";
    else
        cout << "No! " << str << " is not a permutation of a palindrome";
}