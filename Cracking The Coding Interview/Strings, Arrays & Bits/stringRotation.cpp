// Check if one string is the rotation of the other.
// E.g.: "waterbottle" can be rotated to "erbottlewat"

#include <iostream>
#include <string.h>
using namespace std;

// xy = "waterbottle"
// x = "wat"
// y = "erbottle"
// yx = "erbottlewat"
// xyxy = "wat(erbottlewat)erbottle"
// O(A) time
bool isSubstring1(string s1, string s2)
{
    string temp = s1+s1;

    if(s1.size()!=s2.size())
        return false;

    if(temp.find(s2)==string::npos)
        return false;
    return true;
}

int main()
{
    string s1 = "ABACDA";
    string s2 = "CDAABA";

    if(isSubstring(s1, s2))
        cout<<"Yes! "<<s2<<" is a rotation of "<<s1;
    else
        cout<<"No! "<<s2<<" is not a rotation of "<<s1;
}