#include<iostream>
#include<string.h>
using namespace std;

void permutations(string str, string pre)
{
    if(str.length()==0)
    {
        cout<<endl<<"pre= "<<pre<<" ";
        return;
    }

    for(int i=0; i<str.length(); i++)
    {
        string rem = str.substr(0,i) + str.substr(i+1);
        cout << "\n"
             << str.substr(0, i) << " " << str.substr(i + 1)<<" "<<rem;
        permutations(rem, pre + str[i]);
    }   
}

void permutations(string str)
{
    permutations(str, "");
}

int main()
{
    string str = "Arsh";
    permutations(str);
    // cout<<str;
    // cout<<str[0];
    // cout<<str.length();
    // string str2 = str.substr(0,1) + str.substr(2);
    // cout<<endl<<str2;
}