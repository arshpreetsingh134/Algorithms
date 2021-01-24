// Check if a given string has all unique characters
#include <iostream>
#include <unordered_set>
using namespace std;

int countUnique(string str)
{
    // Here we use a set for the lookup operation
    unordered_set<char> strSet;
    for (auto s : str)
        strSet.insert(s);

    return strSet.size();
}

int main()
{
    string str = "ABCCDDDDE";
    cout << "\nNo. of unique characters in the string " << str << " are: " << countUnique(str);
}