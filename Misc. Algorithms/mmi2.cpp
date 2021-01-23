// Given 'a' and 'm', find the Modulo Multiplicative Inverse of a
// such that, ax =~ 1 (mod m)
// Extended Euclidian Algorithm

#include<iostream>
using namespace std;

int gcdExtended(int a, int b, int *x, int *y){
 
    if(a==0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;
    int gcd = gcdExtended(b%a, a, &x1, &y1);

    *x = y1 - (b/a) * x1;
    *y = x1;
    return gcd;
}

int mmi(int a, int m)
{
    int x, y;
    int g = gcdExtended(a, m, &x, &y);
    if(g!=1)
        return -1;

    int res = (x%m +m)%m;
    return res;
}

int main()
{
    int a = 7;
    int m = 11;
    cout<<"\nThe Modulo Multiplicative Inverse of a (mod m) is= "<<mmi(a,m);
}