// Check if a given string has unique characters or not (using Bitmasking)
// Constant space- O(1)
#include<iostream>
#include<algorithm>
using namespace std;

bool checkUnique(string str)
{
    // Convert all to lowercase
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    // An integer to store presence/absence
    // of 26 characters using its 32 bits.
    int checker = 0;

    for(int i=0; i<str.size(); i++)
    {
        int val = str[i] - 'a';

        // If bit corresponding to current
        // character is already set
        if((checker & (1<<val))>0)
            return false;

        // set bit in checker
        checker |= (1<<val);
    }
    return true;
}

int main()
{
    string str = "abcDA";

    cout<<"Are characters in the string "<<str<<" unique? ";
    if(checkUnique(str))
        cout<<"YES!";
    else
        cout<<"NO!";
}