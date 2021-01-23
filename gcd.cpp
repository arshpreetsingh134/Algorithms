// To find the GCD of two numbers

#include<iostream>
using namespace std;

int gcd(int a, int b){
    //16, 24
    if(b==0)
        return a;

    gcd(b, a%b);

}

int main(){
    int a=16;
    int b=24;
    cout<<"GCD of "<<a<<" and "<<b<<" is: "<<gcd(a,b);
}