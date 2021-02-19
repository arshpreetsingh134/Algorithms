// Given a string, replace all occurences of the white space with the string '%20'
// The "true" value of the string (excluding the extra white spaces) is provided
// Input: "Mr John Smith    " , 13
// Output: "Mr%20John%20Smith"
#include<iostream>
using namespace std;

void Replace(string &str, int tru)
{
    int num_spaces = 0;

    // Count no. of spaces
    for(int i=0; i<tru; i++)
        if(str[i]==' ')
            num_spaces++;

    // Start adding characters from the end
    int index = tru + (num_spaces*2);

    // Ending array prematurely in case of excess white spaces
    if(tru<str.size())
        str[tru] = '\0';

    for(int i=tru-1; i>=0; i--)
    {
        if(str[i]==' ')
        {
            str[index-1] = '0';
            str[index-2] = '2';
            str[index-3] = '%';
            index = index-3;
        }
        else
        {
            str[index-1] = str[i];
            index--;
        }
    }
}

int main()
{
    string str = "Mr John Smith    ";
    int tru = 13;       // True Length of the above string

    Replace(str, tru);

    cout<<"New String after replacements is: "<<str;
}