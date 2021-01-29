// Returns all unique characters of a given string
#include <iostream>
#include <bitset>
#include <unordered_set>
#define M 128
using namespace std;

// Using a Bit Vector of length 128 (ASCII Character Set)- O(1) Space & O(n) time 
int countUnique1(string str)
{
    int count=0;

    bitset<M> strSet;
    
    for(auto s:str)
    {
        if(strSet[(int)s])      // Check if character already exists
            count++;
        else
            strSet[(int)s] = 1; // If not, flag it as 1
    }
    return count;
}

// Using a Hash Map- O(n) Space & O(n) time
int countUnique2(string str)
{
    // Here we use a set for the lookup() operation
    unordered_set<char> strSet;
    for (auto s : str)
        strSet.insert(s);

    // Returns the total no. of unique characters
    return strSet.size();
}

int main()
{
    string str = "ABBBCCDDDEEE";
    cout << "\nNo. of unique characters in the string " << str << " are: " << countUnique2(str);

    cout << "\nNo. of unique characters in the string " << str << " are: " << str.size()-countUnique1(str);
}