// To find the GCD of two numbers (O(log(min(a,b))))

#include<iostream>
using namespace std;

int gcd(int a, int b){
    //16, 24
    if(a==0)
        return b;

    return gcd(b%a, a);
}

// Extended GCD Algorithm: This algorithm also calculates the values of x and y such that
// a(x) + b(y) = GCD(a,b)

// The values of x and y are calculated using the following 2 equations :-
// x = y1 - floor(b/a) * x1
// y = x1

// Here, x is the modular multiplicative inverse of “a modulo b”, and y is the modular multiplicative inverse of “b modulo a”.

int extendedGCD(int a, int b, int *x, int *y)
{
    // base case
    if(a==0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1;

    int gcd = extendedGCD(b%a, a, &x1, &y1);

    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}

int main(){
    int a=16;
    int b=31;

    // GCD
    cout<<"GCD of "<<a<<" and "<<b<<" is: "<<gcd(a,b)<< endl;

    // Extended GCD
    int x, y;
    cout << "GCD of " << a << " and " << b << " is: " << extendedGCD(a, b, &x, &y) << endl;
    cout << "x = " << x << " and y = " << y << endl;
}

