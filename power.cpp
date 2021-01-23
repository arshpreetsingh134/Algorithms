#include<iostream>
using namespace std;

int powset(int a, unsigned int b){
    if(b==0)
        return 1;

    if(b%2==0)
        return powset(a, b/2) * powset(a, b/2);
    else{
        return a * powset(a,b/2) * powset(a,b/2);
    }   
}

int main(){
    int a = 4;
    unsigned int b = 3;
    cout<<a<<" raised to the power "<<b<<" is: "<<powset(a,b);
}