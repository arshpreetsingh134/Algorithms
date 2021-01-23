// A binomial coefficient C(n, k) can be defined as the coefficient of X^k in the expansion of (1 + X)^n.
//C(n,k) = C(n-1,k-1) + C(n-1,k)
//Base Case -> C(n,0) = 1

#include<iostream>
using namespace std;


int binomial(int n, int k){
    if(k==0 || k==n)
        return 1;

    return binomial(n-1,k-1) + binomial(n-1,k);
}

int main(){
    int n = 4;
    int k = 2;
    cout<<"C("<<n<<","<<k<<") is: "<<binomial(n,k);
}