// Given 'a' and 'm', find the Modulo Multiplicative Inverse of a
// such that, ax =~ 1 (mod m)
// Naive Algorithm

#include<iostream>
using namespace std;

int mmi(int a, int m)
{
    for(int i=1; i<m; i++)
    {
        if((a*i) % m==1)
            return i;
    }
    return -1;
}

int main()
{
    int a = 7;
    int m = 11;
    cout<<"\nThe Modulo Multiplicative Inverse of a (mod m) is= "<<mmi(a,m);
}